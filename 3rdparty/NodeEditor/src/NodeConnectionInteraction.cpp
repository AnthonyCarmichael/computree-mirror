#include <QQueue>

#include "NodeConnectionInteraction.hpp"

#include "ConnectionGraphicsObject.hpp"
#include "NodeGraphicsObject.hpp"
#include "NodeDataModel.hpp"
#include "DataModelRegistry.hpp"
#include "FlowScene.hpp"

using QtNodes::NodeConnectionInteraction;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::FlowScene;
using QtNodes::Node;
using QtNodes::Connection;
using QtNodes::NodeDataModel;
using QtNodes::TypeConverter;


NodeConnectionInteraction::
NodeConnectionInteraction(Node& node, Connection& connection, FlowScene& scene)
  : _node(&node)
  , _connection(&connection)
  , _scene(&scene)
{}


bool
NodeConnectionInteraction::
canConnect(PortIndex &portIndex, TypeConverter & converter) const
{
  // 1) Connection requires a port

  PortType requiredPort = connectionRequiredPort();

  if (requiredPort == PortType::None)
  {
    return false;
  }

  // 1.5) Forbid connecting the node to itself
  Node* node = _connection->getNode(oppositePort(requiredPort));

  if (node == _node)
    return false;

  // 1.6) Check for Cyclic Connection
  // Fix #198
  if (node) {
    auto isConnected = [](Node* a, Node* b) {
     QQueue<Connection*> cons;
     QQueue<Node*> nodes;
     nodes.enqueue(a);
     while (!nodes.isEmpty()) {
      auto curNode = nodes.dequeue();
      auto& curNodeState = curNode->nodeState();
      auto curNodeCons = curNodeState.getEntries(PortType::Out);

      for (auto& nodeCons : curNodeCons) {
       for (auto& nodeCon : nodeCons) {
        cons.enqueue(nodeCon.second);
       }
         }
         while (!cons.isEmpty()) {
          auto curCon = cons.dequeue();
          if (auto conNode = curCon->getNode(PortType::In)) {
             if (conNode == b) return true;
             
               nodes.enqueue(conNode);
            }
         }
      }
      return false;
    };
    if (requiredPort == PortType::Out) {
      if (isConnected(node, _node)) {
         return false;
      }
    } else if (isConnected(_node, node)) {
       return false;
    }
  }

  // 2) connection point is on top of the node port

  QPointF connectionPoint = connectionEndScenePosition(requiredPort);

  portIndex = nodePortIndexUnderScenePoint(requiredPort,
                                           connectionPoint);

  if (portIndex == INVALID)
  {
    return false;
  }

  // 3) Node port is vacant

  // MK : modification to enable in port accept multiple connection
  // port should be empty
  /*if (!nodePortIsEmpty(requiredPort, portIndex))
    return false;*/

  // 4) connection doesn't exist

  const int myStartPortIndex = _connection->getPortIndex(oppositePort(requiredPort));

  if(_node->nodeState().getEntries(requiredPort).size() > static_cast<size_t>(portIndex))
  {
      auto existingConnections = _node->nodeState().connections(requiredPort, portIndex);

      auto begin = existingConnections.begin();
      auto end = existingConnections.end();

      while(begin != end)
      {
          if(!(*begin).second->connectionState().isAPreview())
          {
              Node* currentNode = (*begin).second->getNode(requiredPort);

              if(currentNode == _node) {
                  const int startPortIndex = (*begin).second->getPortIndex(oppositePort(requiredPort));

                  if(startPortIndex == myStartPortIndex)
                      return false;
              }
          }

          ++begin;
      }
  }

  // 5) Connection type equals node port type, or there is a registered type conversion that can translate between the two

  auto connectionDataType =
    _connection->dataType(oppositePort(requiredPort));

  auto const   &modelTarget = _node->nodeDataModel();
  NodeDataType candidateNodeDataType = modelTarget->dataType(requiredPort, portIndex);

  if (connectionDataType.id != candidateNodeDataType.id)
  {
    if (requiredPort == PortType::In)
    {
      converter = _scene->registry().getTypeConverter(connectionDataType, candidateNodeDataType);
    }
    else if (requiredPort == PortType::Out)
    {
      converter = _scene->registry().getTypeConverter(candidateNodeDataType , connectionDataType);
    }

    if(converter == nullptr)
        return false;

    if(requiredPort == PortType::In)
      return modelTarget->acceptInData(converter(node->nodeDataModel()->outData(myStartPortIndex)), portIndex);

    return node->nodeDataModel()->acceptInData(converter(modelTarget->outData(portIndex)), myStartPortIndex);
  }

  // 6) node data model accept it
  if(requiredPort == PortType::In)
    return modelTarget->acceptInData(node->nodeDataModel()->outData(myStartPortIndex), portIndex);

  return node->nodeDataModel()->acceptInData(modelTarget->outData(portIndex), myStartPortIndex);
}


bool
NodeConnectionInteraction::
tryConnect() const
{
  // 1) Check conditions from 'canConnect'
  PortIndex portIndex = INVALID;

  TypeConverter converter;

  if (!canConnect(portIndex, converter))
  {
    return false;
  }

  // 1.5) If the connection is possible but a type conversion is needed,
  //      assign a convertor to connection
  if (converter)
  {
    _connection->setTypeConverter(converter);
  }

  // 2) Assign node to required port in Connection
  PortType requiredPort = connectionRequiredPort();
  _node->nodeState().setConnection(requiredPort,
                                   portIndex,
                                   *_connection);

  // 3) Assign Connection to empty port in NodeState
  // The port is not longer required after this function
  _connection->setNodeToPort(*_node, requiredPort, portIndex);

  // 4) Adjust Connection geometry

  _node->nodeGraphicsObject().moveConnections();

  // 5) Poke model to intiate data transfer

  auto outNode = _connection->getNode(PortType::Out);
  if (outNode)
  {
    PortIndex outPortIndex = _connection->getPortIndex(PortType::Out);
    outNode->onDataUpdated(outPortIndex);
  }

  return true;
}


/// 1) Node and Connection should be already connected
/// 2) If so, clear Connection entry in the NodeState
/// 3) Set Connection end to 'requiring a port'
bool
NodeConnectionInteraction::
disconnect(PortType portToDisconnect) const
{
  PortIndex portIndex =
    _connection->getPortIndex(portToDisconnect);

  NodeState &state = _node->nodeState();

  // clear pointer to Connection in the NodeState
  state.getEntries(portToDisconnect)[portIndex].erase(_connection->id());

  // 4) Propagate invalid data to IN node
  _connection->propagateEmptyData();

  // clear Connection side
  _connection->clearNode(portToDisconnect);

  _connection->setRequiredPort(portToDisconnect);

  _connection->getConnectionGraphicsObject().grabMouse();

  return true;
}


// ------------------ util functions below

PortType
NodeConnectionInteraction::
connectionRequiredPort() const
{
  auto const &state = _connection->connectionState();

  return state.requiredPort();
}


QPointF
NodeConnectionInteraction::
connectionEndScenePosition(PortType portType) const
{
  auto &go =
    _connection->getConnectionGraphicsObject();

  ConnectionGeometry& geometry = _connection->connectionGeometry();

  QPointF endPoint = geometry.getEndPoint(portType);

  return go.mapToScene(endPoint);
}


QPointF
NodeConnectionInteraction::
nodePortScenePosition(PortType portType, PortIndex portIndex) const
{
  NodeGeometry const &geom = _node->nodeGeometry();

  QPointF p = geom.portScenePosition(portIndex, portType);

  NodeGraphicsObject& ngo = _node->nodeGraphicsObject();

  return ngo.sceneTransform().map(p);
}


PortIndex
NodeConnectionInteraction::
nodePortIndexUnderScenePoint(PortType portType,
                             QPointF const & scenePoint) const
{
  NodeGeometry const &nodeGeom = _node->nodeGeometry();

  QTransform sceneTransform =
    _node->nodeGraphicsObject().sceneTransform();

  PortIndex portIndex = nodeGeom.checkHitScenePoint(portType,
                                                    scenePoint,
                                                    sceneTransform);

  return portIndex;
}


bool
NodeConnectionInteraction::
nodePortIsEmpty(PortType portType, PortIndex portIndex) const
{
  if (portType == PortType::None)
  {
    return false;
  }

  NodeState const & nodeState = _node->nodeState();

  auto const & entries = nodeState.getEntries(portType);

  if (entries[portIndex].empty())
    return true;

  if (portType == PortType::In)
    return _node->nodeDataModel()->portInConnectionPolicy(portIndex) == NodeDataModel::ConnectionPolicy::Many;

  return _node->nodeDataModel()->portOutConnectionPolicy(portIndex) == NodeDataModel::ConnectionPolicy::Many;
}
