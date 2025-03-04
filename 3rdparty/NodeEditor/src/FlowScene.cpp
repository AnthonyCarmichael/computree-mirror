#include "FlowScene.hpp"

#include <stdexcept>
#include <utility>

#include <QtWidgets/QGraphicsSceneMoveEvent>
#include <QtWidgets/QFileDialog>
#include <QtCore/QByteArray>
#include <QtCore/QBuffer>
#include <QtCore/QDataStream>
#include <QtCore/QFile>

#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QtGlobal>
#include <QtCore/QDebug>

#include "Node.hpp"
#include "NodeGraphicsObject.hpp"

#include "NodeGraphicsObject.hpp"
#include "ConnectionGraphicsObject.hpp"

#include "Connection.hpp"

#include "FlowView.hpp"
#include "DataModelRegistry.hpp"

using QtNodes::FlowScene;
using QtNodes::Node;
using QtNodes::NodeGraphicsObject;
using QtNodes::Connection;
using QtNodes::DataModelRegistry;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::TypeConverter;


FlowScene::
FlowScene(std::shared_ptr<DataModelRegistry> registry,
          QObject * parent)
  : QGraphicsScene(parent)
  , _registry(std::move(registry))
  , _readOnly(false)
{
  setItemIndexMethod(QGraphicsScene::NoIndex);

  // This connection should come first
  connect(this, &FlowScene::connectionCreated, this, &FlowScene::setupConnectionSignals);
  connect(this, &FlowScene::connectionCreated, this, &FlowScene::sendConnectionCreatedToNodes);
  connect(this, &FlowScene::connectionDeleted, this, &FlowScene::sendConnectionDeletedToNodes);
}


FlowScene::
FlowScene(QObject * parent)
  : FlowScene(std::make_shared<DataModelRegistry>(),
              parent)
{}


FlowScene::
~FlowScene()
{
  clearScene();
}


//------------------------------------------------------------------------------

std::shared_ptr<Connection>
FlowScene::
createConnection(PortType connectedPort,
                 Node& node,
                 PortIndex portIndex,
                 bool isAPreview,
                 void* data)
{
  auto connection = std::make_shared<Connection>(connectedPort, node, portIndex, data);
  connection->connectionState().setIsAPreview(isAPreview);

  auto cgo = detail::make_unique<ConnectionGraphicsObject>(*this, *connection);

  // after this function connection points are set to node port
  connection->setGraphicsObject(std::move(cgo));

  _connections[connection->id()] = connection;

  // Note: this connection isn't truly created yet. It's only partially created.
  // Thus, don't send the connectionCreated(...) signal.

  connect(connection.get(),
          &Connection::connectionCompleted,
          this,
          [this](Connection const& c) {
            connectionCreated(c);
          });

  return connection;
}


std::shared_ptr<Connection>
FlowScene::
createConnection(Node& nodeIn,
                 PortIndex portIndexIn,
                 Node& nodeOut,
                 PortIndex portIndexOut,
                 TypeConverter const &converter,
                 bool isAPreview,
                 void* data)
{
  auto connection =
    std::make_shared<Connection>(nodeIn,
                                 portIndexIn,
                                 nodeOut,
                                 portIndexOut,
                                 converter,
                                 data);

  connection->connectionState().setIsAPreview(isAPreview);

  auto cgo = detail::make_unique<ConnectionGraphicsObject>(*this, *connection);

  nodeIn.nodeState().setConnection(PortType::In, portIndexIn, *connection);
  nodeOut.nodeState().setConnection(PortType::Out, portIndexOut, *connection);

  // after this function connection points are set to node port
  connection->setGraphicsObject(std::move(cgo));

  // trigger data propagation
  //nodeOut.onDataUpdated(portIndexOut);
  // MK : replaced by :
  if(!isAPreview)
  {
      auto nodeData = nodeOut.nodeDataModel()->outData(portIndexOut);
      connection->propagateData(nodeData);
  }

  _connections[connection->id()] = connection;

  connectionCreated(*connection);

  return connection;
}


std::shared_ptr<Connection>
FlowScene::
restoreConnection(QJsonObject const &connectionJson)
{
  QUuid nodeInId  = QUuid(connectionJson["in_id"].toString());
  QUuid nodeOutId = QUuid(connectionJson["out_id"].toString());

  PortIndex portIndexIn  = connectionJson["in_index"].toInt();
  PortIndex portIndexOut = connectionJson["out_index"].toInt();

  auto nodeIn  = _nodes[nodeInId].get();
  auto nodeOut = _nodes[nodeOutId].get();

  auto getConverter = [&]()
  {
    QJsonValue converterVal = connectionJson["converter"];

    if (!converterVal.isUndefined())
    {
      QJsonObject converterJson = converterVal.toObject();

      NodeDataType inType { converterJson["in"].toObject()["id"].toString(),
                            converterJson["in"].toObject()["name"].toString() };

      NodeDataType outType { converterJson["out"].toObject()["id"].toString(),
                             converterJson["out"].toObject()["name"].toString() };

      auto converter =
        registry().getTypeConverter(outType, inType);

      if (converter)
        return converter;
    }

    return TypeConverter{};
  };

  std::shared_ptr<Connection> connection;
  int const inSize = static_cast<int>(nodeIn->nodeState().getEntries(PortType::In).size());
  int const outSize = static_cast<int>(nodeOut->nodeState().getEntries(PortType::Out).size());
  if ((portIndexIn < inSize) && (portIndexOut < outSize))
  {
     connection =
        createConnection(*nodeIn, portIndexIn,
                         *nodeOut, portIndexOut,
                         getConverter());
  }

  // Note: the connectionCreated(...) signal has already been sent
  // by createConnection(...)

  return connection;
}


void
FlowScene::
deleteConnection(Connection& connection)
{ 
  connection.removeFromNodes();
  Q_EMIT connectionDeleted(connection);
  _connections.erase(connection.id());
}


Node&
FlowScene::
createNode(std::unique_ptr<NodeDataModel> && dataModel)
{
  auto node = detail::make_unique<Node>(std::move(dataModel));
  auto ngo  = detail::make_unique<NodeGraphicsObject>(*this, *node);

  node->setGraphicsObject(std::move(ngo));

  auto nodePtr = node.get();
  _nodes[node->id()] = std::move(node);

  connect(nodePtr, &Node::connectionRemoved, this, &FlowScene::deleteConnection);

  Q_EMIT nodeCreated(*nodePtr);
  return *nodePtr;
}


Node&
FlowScene::
restoreNode(QJsonObject const& nodeJson)
{
  QString modelName = nodeJson["model"].toObject()["name"].toString();

  auto dataModel = registry().create(modelName);

  if (!dataModel)
    throw std::logic_error(std::string("No registered model with name ") +
                           modelName.toLocal8Bit().data());

  // restore data model before the node, to be able to restore dynamic ports.
  dataModel->restore(nodeJson["model"].toObject());

  // create a node with uuid taken from json
  auto node = detail::make_unique<Node>(std::move(dataModel), QUuid(nodeJson["id"].toString()));

  // create node graphics object
  auto ngo  = detail::make_unique<NodeGraphicsObject>(*this, *node);
  QJsonObject positionJson = nodeJson["position"].toObject();
  QPointF point(positionJson["x"].toDouble(), positionJson["y"].toDouble());
  ngo->setPos(point);

  node->setGraphicsObject(std::move(ngo));

  auto nodePtr = node.get();
  _nodes[node->id()] = std::move(node);

  connect(nodePtr, &Node::connectionRemoved, this, &FlowScene::deleteConnection);

  Q_EMIT nodePlaced(*nodePtr);
  Q_EMIT nodeCreated(*nodePtr);
  return *nodePtr;
}


void
FlowScene::
removeNode(Node& node)
{
  Q_EMIT nodeDeleted(node);

  for (auto portType: {PortType::In, PortType::Out})
  {
    auto nodeState = node.nodeState();
    auto const & nodeEntries = nodeState.getEntries(portType);

    for (auto &connections : nodeEntries)
    {
      for (auto const &pair : connections)
        deleteConnection(*pair.second);
    }
  }

  disconnect(&node, &Node::connectionRemoved, this, &FlowScene::deleteConnection);

  _nodes.erase(node.id());
}


DataModelRegistry&
FlowScene::
registry() const
{
  return *_registry;
}


void
FlowScene::
setRegistry(std::shared_ptr<DataModelRegistry> registry)
{
  _registry = std::move(registry);
}


void
FlowScene::
iterateOverNodes(std::function<void(Node*)> const & visitor)
{
  for (const auto& _node : _nodes)
  {
    visitor(_node.second.get());
  }
}


void
FlowScene::
iterateOverNodeData(std::function<void(NodeDataModel*)> const & visitor)
{
  for (const auto& _node : _nodes)
  {
    visitor(_node.second->nodeDataModel());
  }
}


void
FlowScene::
iterateOverNodeDataDependentOrder(std::function<void(NodeDataModel*)> const & visitor)
{
  std::set<QUuid> visitedNodesSet;

  //A leaf node is a node with no input ports, or all possible input ports empty
  auto isNodeLeaf =
    [](Node const &node, NodeDataModel const &model)
    {
      for (unsigned int i = 0; i < model.nPorts(PortType::In); ++i)
      {
        auto connections = node.nodeState().connections(PortType::In, i);
        if (!connections.empty())
        {
          return false;
        }
      }

      return true;
    };

  //Iterate over "leaf" nodes
  for (auto const &_node : _nodes)
  {
    auto const &node = _node.second;
    auto model       = node->nodeDataModel();

    if (isNodeLeaf(*node, *model))
    {
      visitor(model);
      visitedNodesSet.insert(node->id());
    }
  }

  auto areNodeInputsVisitedBefore =
    [&](Node const &node, NodeDataModel const &model)
    {
      for (size_t i = 0; i < model.nPorts(PortType::In); ++i)
      {
        auto connections = node.nodeState().connections(PortType::In, static_cast<PortIndex>(i));

        for (auto& conn : connections)
        {
          if (visitedNodesSet.find(conn.second->getNode(PortType::Out)->id()) == visitedNodesSet.end())
          {
            return false;
          }
        }
      }

      return true;
    };

  //Iterate over dependent nodes
  while (_nodes.size() != visitedNodesSet.size())
  {
    for (auto const &_node : _nodes)
    {
      auto const &node = _node.second;
      if (visitedNodesSet.find(node->id()) != visitedNodesSet.end())
        continue;

      auto model = node->nodeDataModel();

      if (areNodeInputsVisitedBefore(*node, *model))
      {
        visitor(model);
        visitedNodesSet.insert(node->id());
      }
    }
  }
}


QPointF
FlowScene::
getNodePosition(const Node& node) const
{
  return node.nodeGraphicsObject().pos();
}


void
FlowScene::
setNodePosition(Node& node, const QPointF& pos) const
{
  node.nodeGraphicsObject().setPos(pos);
  node.nodeGraphicsObject().moveConnections();
}


QSizeF
FlowScene::
getNodeSize(const Node& node) const
{
  return QSizeF(node.nodeGeometry().width(), node.nodeGeometry().height());
}

void FlowScene::setReadOnly(bool ro)
{
    _readOnly = ro;
}

bool FlowScene::isReadOnly() const
{
    return _readOnly;
}

std::unordered_map<QUuid, std::unique_ptr<Node> > const &
FlowScene::
nodes() const
{
  return _nodes;
}


std::unordered_map<QUuid, std::shared_ptr<Connection> > const &
FlowScene::
connections() const
{
  return _connections;
}


std::vector<Node*>
FlowScene::
allNodes() const
{
  std::vector<Node*> nodes;

  std::transform(_nodes.begin(),
                 _nodes.end(),
                 std::back_inserter(nodes),
                 [](std::pair<QUuid const, std::unique_ptr<Node>> const & p) { return p.second.get(); });

  return nodes;
}


std::vector<Node*>
FlowScene::
selectedNodes() const
{
  QList<QGraphicsItem*> graphicsItems = selectedItems();

  std::vector<Node*> ret;
  ret.reserve(graphicsItems.size());

  for (QGraphicsItem* item : graphicsItems)
  {
    auto ngo = qgraphicsitem_cast<NodeGraphicsObject*>(item);

    if (ngo != nullptr)
    {
      ret.push_back(&ngo->node());
    }
  }

  return ret;
}


//------------------------------------------------------------------------------

void
FlowScene::
clearScene()
{
  // Manual node cleanup. Simply clearing the holding datastructures doesn't work, the code crashes when
  // there are both nodes and connections in the scene. (The data propagation internal logic tries to propagate
  // data through already freed connections.)
  while (_connections.size() > 0)
  {
    deleteConnection( *_connections.begin()->second );
  }

  while (_nodes.size() > 0)
  {
    removeNode( *_nodes.begin()->second );
  }
}


void
FlowScene::
save() const
{
  QString fileName =
    QFileDialog::getSaveFileName(nullptr,
                                 tr("Open Flow Scene"),
                                 QDir::homePath(),
                                 tr("Flow Scene Files (*.flow)"));

  if (!fileName.isEmpty())
  {
    if (!fileName.endsWith("flow", Qt::CaseInsensitive))
      fileName += ".flow";

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
      file.write(saveToMemory());
    }
  }
}


void
FlowScene::
load()
{
  QString fileName =
    QFileDialog::getOpenFileName(nullptr,
                                 tr("Open Flow Scene"),
                                 QDir::homePath(),
                                 tr("Flow Scene Files (*.flow)"));

  if (!QFileInfo::exists(fileName))
    return;

  QFile file(fileName);

  if (file.open(QIODevice::ReadOnly)){
     clearScene();
     loadFromMemory(file.readAll());
  }
}

QByteArray
FlowScene::
saveToMemory(QJsonDocument::JsonFormat format) const
{
  return QJsonDocument(saveToObject()).toJson(format);
}

void
FlowScene::
loadFromMemory(const QByteArray& data)
{
  const QJsonObject jsonDocument = QJsonDocument::fromJson(data).object();
  loadFromMemory(jsonDocument);
}

QJsonObject
FlowScene::
saveToObject() const
{
  QJsonObject sceneJson;

  QJsonArray nodesJsonArray;

  for (auto const & pair : _nodes)
  {
    auto const &node = pair.second;

    nodesJsonArray.append(node->save());
  }

  sceneJson["nodes"] = nodesJsonArray;

  QJsonArray connectionJsonArray;
  for (auto const & pair : _connections)
  {
    auto const &connection = pair.second;

    QJsonObject connectionJson = connection->save();

    if (!connectionJson.isEmpty())
      connectionJsonArray.append(connectionJson);
  }

  sceneJson["connections"] = connectionJsonArray;

  return sceneJson;
}

void
FlowScene::
loadFromObject(const QJsonObject& data)
{
   QJsonArray nodesJsonArray = data["nodes"].toArray();

   for (QJsonValueRef node : nodesJsonArray)
   {
      restoreNode(node.toObject());
   }

   QJsonArray connectionJsonArray = data["connections"].toArray();

   for (QJsonValueRef connection : connectionJsonArray)
   {
      restoreConnection(connection.toObject());
   }
}

void FlowScene::loadFromMemory(const QJsonObject& data)
{
  loadFromObject(data);
}

QByteArray
FlowScene::
copyNodes(const std::vector<QtNodes::Node*>& nodes) const
{
   QJsonObject sceneJson;
   QSet<QUuid> nodeIds;
   QJsonArray nodesJsonArray;

   // center of gravity
   std::vector<int> cogX;
   std::vector<int> cogY;

   for (auto const & n : nodes)
   {
      auto nodeJson = n->save();
      nodesJsonArray.append(nodeJson);
      nodeIds.insert(n->id());

      auto nodePosition = nodeJson = nodeJson["position"].toObject();
      cogX.emplace_back(nodePosition["x"].toDouble());
      cogY.emplace_back(nodePosition["y"].toDouble());
   }

   sceneJson["nodes"] = nodesJsonArray;

   QJsonArray connectionJsonArray;
   for (auto const & pair : connections())
   {
      auto const &connection = pair.second;

      auto inNodeId = connection->getNode(PortType::In)->id();
      auto outNodeId = connection->getNode(PortType::Out)->id();
      if (nodeIds.contains(inNodeId) && nodeIds.contains(outNodeId))
      {
         QJsonObject connectionJson = connection->save();
         if (!connectionJson.isEmpty())
            connectionJsonArray.append(connectionJson);
      }
   }

   sceneJson["connections"] = connectionJsonArray;

   // save center of gravity too
   if(cogX.size() > 0){
      QJsonObject jsonCog;
      jsonCog["x"] = std::accumulate(cogX.begin(), cogX.end(), 0) / static_cast<double>(cogX.size());
      jsonCog["y"] = std::accumulate(cogY.begin(), cogY.end(), 0) / static_cast<double>(cogY.size());
      sceneJson["cog"] = jsonCog;
   }

   QJsonDocument document(sceneJson);

   return document.toJson();
}

void FlowScene::pasteNodes(const QByteArray& data, const QPointF& pointOffset)
{
   QMap<QUuid,QUuid> newIdsMap;
   QJsonObject jsonDocument = QJsonDocument::fromJson(data).object();

   // if exists a center of gravity, take it
   auto jsonCog = jsonDocument["cog"].toObject();
   double offsetX = pointOffset.x() - jsonCog["x"].toDouble();
   double offsetY = pointOffset.y() - jsonCog["y"].toDouble();

   QJsonArray nodesJsonArray = jsonDocument["nodes"].toArray();
   for (auto node : nodesJsonArray)
   {
      auto nodeJson = node.toObject();

      QString oldId = nodeJson["id"].toString();
      if (!newIdsMap.contains(oldId))
         newIdsMap[oldId] = QUuid::createUuid();

      nodeJson["id"] = newIdsMap[oldId].toString();

      // update position of the copy of the nodes
      auto nodePosition = nodeJson["position"].toObject();
      nodePosition["x"] = nodePosition["x"].toDouble() + offsetX;
      nodePosition["y"] = nodePosition["y"].toDouble() + offsetY;
      nodeJson["position"] = nodePosition;

      node = nodeJson;
   }
   jsonDocument["nodes"] = nodesJsonArray;

   QJsonArray connectionJsonArray = jsonDocument["connections"].toArray();
   for (QJsonValueRef connection : connectionJsonArray)
   {
      auto connectionJson = connection.toObject();

      QString oldId = connectionJson["in_id"].toString();
      if (newIdsMap.contains(oldId))
         connectionJson["in_id"] = newIdsMap[oldId].toString();

      oldId = connectionJson["out_id"].toString();
      if (newIdsMap.contains(oldId))
         connectionJson["out_id"] = newIdsMap[oldId].toString();

      connection = connectionJson;
   }
   jsonDocument["connections"] = connectionJsonArray;

   try {
      loadFromMemory(QJsonDocument(jsonDocument).toJson());
   } catch (const std::logic_error& e) {
      // prevent pasting if receving scene has not registered the source node
      // it can be happens copying and pasting between different scenes

      Q_UNUSED(e);

      qDebug() << "cannot copy selected nodes";
   }
 }


void
FlowScene::
setupConnectionSignals(Connection const& c)
{
  connect(&c,
          &Connection::connectionMadeIncomplete,
          this,
          &FlowScene::connectionDeleted,
          Qt::UniqueConnection);
}


void
FlowScene::
sendConnectionCreatedToNodes(Connection const& c)
{
  Node* from = c.getNode(PortType::Out);
  Node* to   = c.getNode(PortType::In);

  if(from)
    from->nodeDataModel()->outputConnectionCreated(c);

  if(to)
    to->nodeDataModel()->inputConnectionCreated(c);
}


void
FlowScene::
sendConnectionDeletedToNodes(Connection const& c)
{
  Node* from = c.getNode(PortType::Out);
  Node* to   = c.getNode(PortType::In);

  if(from)
    from->nodeDataModel()->outputConnectionDeleted(c);

  if(to)
    to->nodeDataModel()->inputConnectionDeleted(c);
}


//------------------------------------------------------------------------------
namespace QtNodes
{

Node*
locateNodeAt(QPointF scenePoint, FlowScene &scene,
             QTransform const & viewTransform)
{
  // items under cursor
  QList<QGraphicsItem*> items =
    scene.items(scenePoint,
                Qt::IntersectsItemShape,
                Qt::DescendingOrder,
                viewTransform);

  //// items convertable to NodeGraphicsObject
  std::vector<QGraphicsItem*> filteredItems;

  std::copy_if(items.begin(),
               items.end(),
               std::back_inserter(filteredItems),
               [] (QGraphicsItem * item)
    {
      return (dynamic_cast<NodeGraphicsObject*>(item) != nullptr);
    });

  Node* resultNode = nullptr;

  if (!filteredItems.empty())
  {
    QGraphicsItem* graphicsItem = filteredItems.front();
    auto ngo = dynamic_cast<NodeGraphicsObject*>(graphicsItem);

    resultNode = &ngo->node();
  }

  return resultNode;
}
}
