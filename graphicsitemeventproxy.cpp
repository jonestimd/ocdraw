#include "graphicsitemeventproxy.h"

GraphicsItemEventProxy::GraphicsItemEventProxy(QGraphicsItem *parent) : QGraphicsObject(parent)
{
}

bool GraphicsItemEventProxy::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneMouseMove) {
        emit shapeMoved(watched);
    }
    return false;
}

QRectF GraphicsItemEventProxy::boundingRect() const
{
    return QRectF();
}

void GraphicsItemEventProxy::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
}
