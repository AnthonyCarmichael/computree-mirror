#pragma once


#include <QtCore/QObject>
#include <QtCore/QUuid>

#include <QtCore/QJsonObject>

#include "PortType.hpp"

#include "Export.hpp"
#include "NodeState.hpp"
#include "NodeGeometry.hpp"
#include "NodeData.hpp"
#include "NodeGraphicsObject.hpp"
#include "ConnectionGraphicsObject.hpp"
#include "Serializable.hpp"
#include "memory.hpp"

namespace QtNodes
{

class Connection;
class ConnectionState;
class NodeGraphicsObject;
class NodeDataModel;

class NODE_EDITOR_PUBLIC Node
  : public QObject
  , public Serializable
{
  Q_OBJECT

public:

  /// NodeDataModel should be an rvalue and is moved into the Node
  Node(std::unique_ptr<NodeDataModel> && dataModel);

  Node(std::unique_ptr<NodeDataModel> && dataModel, QUuid&& uuid);

  virtual
  ~Node();

public:

  QJsonObject
  save() const override;

  void
  restore(QJsonObject const &json) override;

public:

  QUuid
  id() const;

  void reactToPossibleConnection(PortType,
                                 NodeDataType const &,
                                 QPointF const & scenePoint);

  void
  resetReactionToConnection();

public:

  NodeGraphicsObject const &
  nodeGraphicsObject() const;

  NodeGraphicsObject &
  nodeGraphicsObject();

  void
  setGraphicsObject(std::unique_ptr<NodeGraphicsObject>&& graphics);

  NodeGeometry&
  nodeGeometry();

  NodeGeometry const&
  nodeGeometry() const;

  NodeState const &
  nodeState() const;

  NodeState &
  nodeState();

  NodeDataModel*
  nodeDataModel() const;

public Q_SLOTS: // data propagation

  /// Propagates incoming data to the underlying model.
  void
  propagateData(PortIndex inPortIndex) const;
  
  /// RM : propagate data, specific node data, and connections
  void
  propagateData(const QtNodes::Connection *c,
                std::shared_ptr<NodeData> nodeData,
                PortIndex inPortIndex) const;

  /// Fetches data from model's OUT #index port
  /// and propagates it to the connection
  void
  onDataUpdated(PortIndex index);

  /// update the graphic part if the size of the embeddedwidget changes
  void
  onNodeSizeUpdated();

  /// Add the specified port and recalculate position of the connections
  void
  onPortAdded(PortType portType, PortIndex index);

  void
  onPortMoved(PortType portType, PortIndex oldIndex, PortIndex newIndex);

  void
  onPortRemoved(PortType portType, PortIndex index);

Q_SIGNALS:

  void
  connectionRemoved(Connection& connection);

private:

  void
  updateGraphics() const;

  void
  insertEntry(PortType portType, PortIndex index);

  void
  eraseEntry(PortType portType, PortIndex index);

private:

  // addressing

  QUuid _uid;

  // data

  std::unique_ptr<NodeDataModel> _nodeDataModel;

  NodeState _nodeState;

  // painting

  NodeGeometry _nodeGeometry;

  std::unique_ptr<NodeGraphicsObject> _nodeGraphicsObject;
};
}
