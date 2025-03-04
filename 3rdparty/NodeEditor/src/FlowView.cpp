#include "FlowView.hpp"

#include <QtWidgets/QGraphicsScene>

#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtWidgets/QMenu>

#include <QtCore/QRectF>
#include <QtCore/QPointF>

#include <QtWidgets>

#include <QDebug>
#include <iostream>
#include <cmath>

#include "FlowScene.hpp"
#include "DataModelRegistry.hpp"
#include "Node.hpp"
#include "NodeGraphicsObject.hpp"
#include "ConnectionGraphicsObject.hpp"
#include "StyleCollection.hpp"

using QtNodes::FlowView;
using QtNodes::FlowScene;

FlowView::
FlowView(QWidget *parent)
  : QGraphicsView(parent)
  , _clearSelectionAction(Q_NULLPTR)
  , _deleteSelectionAction(Q_NULLPTR)
  , _scene(Q_NULLPTR)
{
  setDragMode(QGraphicsView::ScrollHandDrag);
  setRenderHint(QPainter::Antialiasing);

  auto const &flowViewStyle = StyleCollection::flowViewStyle();

  setBackgroundBrush(flowViewStyle.BackgroundColor);

  //setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  //setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  setCacheMode(QGraphicsView::CacheBackground);

  //setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
}


FlowView::
FlowView(FlowScene *scene, QWidget *parent)
  : FlowView(parent)
{
  setScene(scene);
}


QAction*
FlowView::
clearSelectionAction() const
{
  return _clearSelectionAction;
}


QAction*
FlowView::
deleteSelectionAction() const
{
  return _deleteSelectionAction;
}


void
FlowView::setScene(FlowScene *scene)
{
  _scene = scene;
  QGraphicsView::setScene(_scene);

  // setup actions
  delete _clearSelectionAction;
  _clearSelectionAction = new QAction(QStringLiteral("Clear Selection"), this);
  _clearSelectionAction->setShortcut(Qt::Key_Escape);
  connect(_clearSelectionAction, &QAction::triggered, _scene, &QGraphicsScene::clearSelection);
  addAction(_clearSelectionAction);

  delete _deleteSelectionAction;
  _deleteSelectionAction = new QAction(QStringLiteral("Delete Selection"), this);
  _deleteSelectionAction->setShortcut(Qt::Key_Delete);
  connect(_deleteSelectionAction, &QAction::triggered, this, &FlowView::deleteSelectedNodes);
  addAction(_deleteSelectionAction);
}

void FlowView::setReadOnly(bool ro)
{
    _deleteSelectionAction->setDisabled(ro);
    _scene->setReadOnly(ro);
}

bool FlowView::isReadOnly() const
{
    return _scene->isReadOnly();
}

void
FlowView::
contextMenuEvent(QContextMenuEvent *event)
{
    // MK : remove context menu to create new nodes
    QGraphicsView::contextMenuEvent(event);
  /*
  if (itemAt(event->pos()))
  {
    QGraphicsView::contextMenuEvent(event);
    return;
  }

  QMenu modelMenu;

  auto skipText = QStringLiteral("skip me");

  //Add filterbox to the context menu
  auto *txtBox = new QLineEdit(&modelMenu);

  txtBox->setPlaceholderText(QStringLiteral("Search"));
  txtBox->setClearButtonEnabled(true);

  auto *txtBoxAction = new QWidgetAction(&modelMenu);
  txtBoxAction->setDefaultWidget(txtBox);

  modelMenu.addAction(txtBoxAction);

  //Add result treeview to the context menu
  auto *treeView = new QTreeWidget(&modelMenu);
  treeView->header()->close();

  auto *treeViewAction = new QWidgetAction(&modelMenu);
  treeViewAction->setDefaultWidget(treeView);

  modelMenu.addAction(treeViewAction);

  QMap<QString, QTreeWidgetItem*> topLevelItems;
  for (auto const &cat : _scene->registry().categories())
  {
    // Allows subcategories if separeted by "//"
    QStringList splittedCategories = cat.split("//");

    if (splittedCategories.count() == 1) {
       auto item = new QTreeWidgetItem(treeView);
       item->setText(0, cat);
       item->setData(0, Qt::UserRole, skipText);
       topLevelItems[cat] = item;
    }
    else {
       QString partialCategory = splittedCategories.at(0);
       QTreeWidgetItem* parent = nullptr;

       if (!topLevelItems.contains(partialCategory)) {
          auto item = new QTreeWidgetItem(treeView);
          item->setText(0, partialCategory);
          item->setData(0, Qt::UserRole, partialCategory);
          topLevelItems[partialCategory] = item;
          parent = item;
       }
       else {
          parent = topLevelItems[partialCategory];
       }

       for (int i=1; i<splittedCategories.count(); ++i) {
          partialCategory += "//" + splittedCategories.at(i);

          auto childItem = new QTreeWidgetItem(parent);
          childItem->setText(0, splittedCategories.at(i));
          childItem->setData(0, Qt::UserRole, splittedCategories.at(i));
          topLevelItems[partialCategory] = childItem;

          parent = childItem;
       }
    }
  }

  for (auto const &assoc : _scene->registry().registeredModelsCategoryAssociation())
  {
    auto parent = topLevelItems[assoc.second];
    auto item   = new QTreeWidgetItem(parent);
    item->setText(0, assoc.first);
    item->setData(0, Qt::UserRole, assoc.first);
  }

  treeView->expandAll();

  connect(treeView, &QTreeWidget::itemClicked, [&](QTreeWidgetItem *item, int)
  {
    QString modelName = item->data(0, Qt::UserRole).toString();

    if (modelName == skipText)
    {
      return;
    }

    auto type = _scene->registry().create(modelName);

    if (type)
    {
      auto& node = _scene->createNode(std::move(type));

      QPoint pos = event->pos();

      QPointF posView = this->mapToScene(pos);

      node.nodeGraphicsObject().setPos(posView);

      _scene->nodePlaced(node);
    }
    else
    {
      qDebug() << "Model not found";
    }

    modelMenu.close();
  });

  auto depthSearch = [] (QTreeWidgetItem* item, const QString& text) -> void {
     auto search = [](QTreeWidgetItem* item, const QString& text, const auto& func) -> bool {
        if(item->childCount() == 0){
           const auto modelName = item->data(0, Qt::UserRole).toString();
           const bool match = modelName.contains(text, Qt::CaseInsensitive);
           item->setHidden(!match);
           return match;
        }
        else {
           bool matchAtLeastOneChild = false;
           for(int i = 0; i<item->childCount(); ++i){
              matchAtLeastOneChild |= func(item->child(i), text, func);
           }
           item->setHidden(!matchAtLeastOneChild);
           return matchAtLeastOneChild;
        }
     };

     search(item, text, search);
  };

  //Setup filtering
  connect(txtBox, &QLineEdit::textChanged, this, [topLevelItems, depthSearch](const QString &text)
  {
    for(auto& topLvlItem : topLevelItems)
    {
       depthSearch(topLvlItem, text);
    }
  });

  // make sure the text box gets focus so the user doesn't have to click on it
  txtBox->setFocus();

  modelMenu.exec(event->globalPos());*/
}


void
FlowView::
wheelEvent(QWheelEvent *event)
{
  QPoint delta = event->angleDelta();

  if (delta.y() == 0)
  {
    event->ignore();
    return;
  }

  /*double const d = delta.y() / std::abs(delta.y());

  if (d > 0.0)
    scaleUp();
  else
    scaleDown();*/

  // RM : move scene/nodes only vertically
  setSceneRect(sceneRect().translated(0.0, -delta.y()));
  QGraphicsView::wheelEvent(event);
  limitNodeToRect();
}


void
FlowView::
limitNodeToRect()
{
    Node* rightNode = scene()->allNodes().at(0);
    if(scene()->allNodes().at(1)->nodeGraphicsObject().ref())
        rightNode = scene()->allNodes().at(1);
    QPointF rightNodePos = rightNode->nodeGraphicsObject().pos();
    QRectF rightNodeRect = rightNode->nodeGraphicsObject().boundingRect();

    QRectF sceneRectArea = mapToScene(scene()->views().first()->viewport()->geometry()).boundingRect();

    if(rightNodePos.y() < sceneRectArea.top() + 15)
        rightNodePos.setY(sceneRectArea.top() + 15);
    if(rightNodePos.y() + rightNodeRect.height() > sceneRectArea.bottom())
        rightNodePos.setY(sceneRectArea.bottom() - rightNodeRect.height());

    scene()->setNodePosition(*rightNode,rightNodePos);
}


void
FlowView::
scaleUp()
{
  double const step   = 1.2;
  double const factor = std::pow(step, 1.0);

  QTransform t = transform();

  if (t.m11() > 2.0)
    return;

  scale(factor, factor);
}


void
FlowView::
scaleDown()
{
  double const step   = 1.2;
  double const factor = std::pow(step, -1.0);

  scale(factor, factor);
}


void
FlowView::
deleteSelectedNodes()
{
  // Delete the selected connections first, ensuring that they won't be
  // automatically deleted when selected nodes are deleted (deleting a node
  // deletes some connections as well)
  /*for (QGraphicsItem * item : _scene->selectedItems())
  {
    if (auto c = qgraphicsitem_cast<ConnectionGraphicsObject*>(item))
      _scene->deleteConnection(c->connection());
  }*/

  // MK : disable delete of preview
  int i = 0;
  while(i < _scene->selectedItems().size())
  {
      QGraphicsItem* item = _scene->selectedItems().at(i);
      if (auto c = qgraphicsitem_cast<ConnectionGraphicsObject*>(item))
      {
          // MK : disable delete of preview
          if(!c->connection().connectionState().isAPreview())
          {
              _scene->deleteConnection(c->connection());
              i = 0;
          }
      }
      else
      {
          ++i;
      }
  }

  // Delete the nodes; this will delete many of the connections.
  // Selected connections were already deleted prior to this loop, otherwise
  // qgraphicsitem_cast<NodeGraphicsObject*>(item) could be a use-after-free
  // when a selected connection is deleted by deleting the node.
  // MK : disable delete nodes !
  /*for (QGraphicsItem * item : _scene->selectedItems())
  {
    if (auto n = qgraphicsitem_cast<NodeGraphicsObject*>(item))
      _scene->removeNode(n->node());
  }*/
}


void
FlowView::
keyPressEvent(QKeyEvent *event)
{
  // MK : remove rubberBand
  /*switch (event->key())
  {
    case Qt::Key_Shift:
      setDragMode(QGraphicsView::RubberBandDrag);
      break;

    case Qt::Key_C:
       if (event->modifiers() & Qt::ControlModifier) {
          copy();
          return;
       }
       break;

    case Qt::Key_V:
       if (event->modifiers() & Qt::ControlModifier) {
          paste();
          return;
       }
       break;

    default:
      break;
  }*/

  QGraphicsView::keyPressEvent(event);
}


void
FlowView::
keyReleaseEvent(QKeyEvent *event)
{
  // MK : remove rubberBand
  /*switch (event->key())
  {
    case Qt::Key_Shift:
      setDragMode(QGraphicsView::ScrollHandDrag);
      break;

    default:
      break;
  }*/
  QGraphicsView::keyReleaseEvent(event);
}


void
FlowView::
mousePressEvent(QMouseEvent *event)
{
  QGraphicsView::mousePressEvent(event);
  if (event->button() == Qt::LeftButton)
  {
    _clickPos = mapToScene(event->pos());
  }
}


void
FlowView::
mouseMoveEvent(QMouseEvent *event)
{
  QGraphicsView::mouseMoveEvent(event);
  if (scene()->mouseGrabberItem() == nullptr && event->buttons() == Qt::LeftButton)
  {
    // Make sure shift is not being pressed
    if ((event->modifiers() & Qt::ShiftModifier) == 0)
    {
      QPointF difference = _clickPos - mapToScene(event->pos());
      //setSceneRect(sceneRect().translated(difference.x(), difference.y()));
      setSceneRect(sceneRect().translated(0.0, difference.y())); // Vertical move only

      limitNodeToRect();
    }
  }
}


void
FlowView::
drawBackground(QPainter* painter, const QRectF& r)
{
  QGraphicsView::drawBackground(painter, r);

  auto drawGrid =
    [&](double gridStep)
    {
      QRect   windowRect = rect();
      QPointF tl = mapToScene(windowRect.topLeft());
      QPointF br = mapToScene(windowRect.bottomRight());

      double left   = std::floor(tl.x() / gridStep - 0.5);
      double right  = std::floor(br.x() / gridStep + 1.0);
      double bottom = std::floor(tl.y() / gridStep - 0.5);
      double top    = std::floor (br.y() / gridStep + 1.0);

      // vertical lines
      for (int xi = int(left); xi <= int(right); ++xi)
      {
        QLineF line(xi * gridStep, bottom * gridStep,
                    xi * gridStep, top * gridStep );

        painter->drawLine(line);
      }

      // horizontal lines
      for (int yi = int(bottom); yi <= int(top); ++yi)
      {
        QLineF line(left * gridStep, yi * gridStep,
                    right * gridStep, yi * gridStep );
        painter->drawLine(line);
      }
    };

  auto const &flowViewStyle = StyleCollection::flowViewStyle();

  QBrush bBrush = backgroundBrush();

  QPen pfine(flowViewStyle.FineGridColor, 1.0);

  painter->setPen(pfine);
  drawGrid(15);

  QPen p(flowViewStyle.CoarseGridColor, 1.0);

  painter->setPen(p);
  drawGrid(150);
}


void
FlowView::
showEvent(QShowEvent *event)
{
  _scene->setSceneRect(this->rect());
  QGraphicsView::showEvent(event);
}


FlowScene *
FlowView::
scene()
{
   return _scene;
}

QString FlowView::nodeMimeType() const
{
   return "application/x-nodeeditor-nodes";
}

void FlowView::copy()
{
   QClipboard *clipboard = QApplication::clipboard();
   QMimeData *mimeData = new QMimeData();

   QByteArray data = scene()->copyNodes(scene()->selectedNodes());
   mimeData->setData(nodeMimeType(), data);
   mimeData->setText(data);

   clipboard->setMimeData(mimeData);
}

void FlowView::paste()
{
   const QClipboard *clipboard = QApplication::clipboard();
   const QMimeData *mimeData = clipboard->mimeData();

   auto mousePos = mapToScene(mapFromGlobal(QCursor::pos()));
   if (mimeData->hasFormat(nodeMimeType())) {
      scene()->pasteNodes(mimeData->data(nodeMimeType()), mousePos);
   } else if (mimeData->hasText()) {
      scene()->pasteNodes(mimeData->text().toUtf8(), mousePos);
   }
}
