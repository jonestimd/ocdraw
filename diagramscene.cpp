#include "diagramscene.h"
#include "selectableshape.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

DiagramScene::DiagramScene(QObject* parent) :
    QGraphicsScene(parent),
    axisPen(QBrush(QColor(255, 128, 128)), 0, Qt::SolidLine),
    search(0, 0, HIGHLIGHT_DIAMETER, HIGHLIGHT_DIAMETER),
    highlight(0, 0, HIGHLIGHT_DIAMETER, HIGHLIGHT_DIAMETER)
{
    dragging = false;
    highlighted = nullptr;

    QRadialGradient gradient = QRadialGradient(0.5, 0.5, 1);
    gradient.setColorAt(0.0, Qt::yellow);
    gradient.setColorAt(1.0, Qt::black);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    highlightBrush = QBrush(gradient);
}

void DiagramScene::removeItem(QGraphicsItem *item)
{
    QGraphicsScene::removeItem(item);
    if (item == highlighted) {
        highlighted = nullptr;
        update(highlight);
    }
}

void DiagramScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);
    painter->setPen(axisPen);
    if (rect.left() < 0 && rect.right() > 0) painter->drawLine(0, int(rect.top()), 0, int(rect.bottom()));
    if (rect.top() < 0 && rect.bottom() > 0) painter->drawLine(int(rect.left()), 0, int(rect.right()), 0);
}

void DiagramScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawForeground(painter, rect);
    if (highlighted != nullptr && ! dragging) {
        painter->setBrush(highlightBrush);
        painter->drawEllipse(highlight);
    }
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        if (highlighted != nullptr) {
            update(highlight);
            emit selectShape(highlighted, event->scenePos(), event->modifiers() & Qt::ControlModifier ? ShapeAction::Edit : ShapeAction::Move);
        }
        else emit beginDraw(event->scenePos());
    }
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (dragging) emit changeShape(event->scenePos(), false);
    else if (event->buttons() == Qt::NoButton) {
        search.moveCenter(event->scenePos());
        QList<QGraphicsItem*> items = this->items(search, Qt::IntersectsItemShape, Qt::AscendingOrder);
        for (int i = 0; i < items.length(); i++) {
            if (updateHighlight(items[i], event->scenePos())) return;
        }
        if (highlighted != nullptr) update(highlight);
        highlighted = nullptr;
    }
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (dragging) {
        emit changeShape(event->scenePos(), true);
        dragging = false;
        if (highlighted != nullptr) updateHighlight(highlighted, event->scenePos());
    }
}

bool DiagramScene::updateHighlight(QGraphicsItem* item, QPointF scenePos)
{
    SelectableShape* highligher = dynamic_cast<SelectableShape*>(item);
    QPointF localCursor = item->mapFromScene(scenePos);
    if (highligher->isInRange(localCursor)) {
        const QRectF oldHighlight = highlight;
        highlight.moveCenter(item->mapToScene(highligher->selectPoint(localCursor)));
        if (item != highlighted || oldHighlight != highlight) {
            update(oldHighlight);
            update(highlight);
        }
        highlighted = item;
        return true;
    }
    return false;
}
