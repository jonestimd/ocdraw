#include "graphicsdiagram.h"
#include "highlighter.h"
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QList>
#include <QDebug>

GraphicsDiagram::GraphicsDiagram(QGraphicsItem* parent) :
    QObject(),
    QGraphicsItemGroup(parent),
    search(0, 0, HIGHLIGHT_DIAMETER, HIGHLIGHT_DIAMETER),
    highlight(0, 0, HIGHLIGHT_DIAMETER, HIGHLIGHT_DIAMETER)
{
    highlighted = nullptr;
    hideHighlight = false;

    QRadialGradient gradient = QRadialGradient(0.5, 0.5, 1);
    gradient.setColorAt(0.0, Qt::yellow);
    gradient.setColorAt(1.0, Qt::black);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    highlightBrush = QBrush(gradient);

    setAcceptHoverEvents(true);
}

QRectF GraphicsDiagram::boundingRect() const
{
    QRectF bounds = QGraphicsItemGroup::boundingRect();
    bounds.adjust(-HIGHLIGHT_RADIUS, -HIGHLIGHT_RADIUS, HIGHLIGHT_RADIUS, HIGHLIGHT_RADIUS);
    return bounds;
}

void GraphicsDiagram::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsItemGroup::paint(painter, option, widget);
    if (highlighted != nullptr && ! hideHighlight) {
        painter->setBrush(highlightBrush);
        painter->drawEllipse(highlight);
    }
}

void GraphicsDiagram::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    hoverMoveEvent(event);
}

void GraphicsDiagram::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    search.moveCenter(event->scenePos());
    QList<QGraphicsItem*> items = scene()->items(search, Qt::IntersectsItemShape, Qt::AscendingOrder);
    for (int i = 0; i < items.length(); i++) {
        Highlighter* highligher = qvariant_cast<Highlighter*>(items[i]->data(int(DataKey::highlighter)));
        if (highligher != nullptr) {
            QPointF localCursor = items[i]->mapFromScene(event->scenePos());
            if (highligher->isInRange(localCursor)) {
                const QRectF oldHighlight = highlight;
                highlight.moveCenter(items[i]->mapToScene(highligher->selectPoint(localCursor)));
                if (items[i] != highlighted || oldHighlight != highlight) {
                    update(oldHighlight);
                    update(highlight);
                }
                highlighted = items[i];
                return;
            }
        }
    }
    if (highlighted != nullptr) update(highlight);
    highlighted = nullptr;
}

void GraphicsDiagram::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    hoverMoveEvent(event);
}

void GraphicsDiagram::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (highlighted == nullptr || event->button() != Qt::LeftButton) event->ignore();
    else {
        hideHighlight = true;
        update(highlight);
    }
}

void GraphicsDiagram::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF delta = event->scenePos() - event->lastScenePos();
    highlighted->moveBy(delta.x(), delta.y());
    hideHighlight = false;
    update(highlight);
}

void GraphicsDiagram::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF delta = event->scenePos() - event->lastScenePos();
    highlighted->moveBy(delta.x(), delta.y());
}
