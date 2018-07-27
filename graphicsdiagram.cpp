#include "graphicsdiagram.h"
#include "highlighter.h"
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QList>
#include <QDebug>

GraphicsDiagram::GraphicsDiagram(QGraphicsItem* parent) :
    QObject(),
    QGraphicsItemGroup(parent),
    highlight()
{
    showHighlight = false;
    setAcceptHoverEvents(true);

    QRadialGradient gradient = QRadialGradient(0.5, 0.5, 1);
    gradient.setColorAt(0.0, Qt::yellow);
    gradient.setColorAt(1.0, Qt::black);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    highlightBrush = QBrush(gradient);
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
    if (showHighlight) {
        painter->setBrush(highlightBrush);
        painter->drawEllipse(highlight, HIGHLIGHT_RADIUS, HIGHLIGHT_RADIUS);
    }
}

void GraphicsDiagram::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    hoverMoveEvent(event);
}

void GraphicsDiagram::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    QPointF cursor = event->pos() - OcDraw::CursorOffset;
    QList<QGraphicsItem*> items = scene()->items(cursor.x(), cursor.y(), HIGHLIGHT_DIAMETER, HIGHLIGHT_DIAMETER, Qt::IntersectsItemShape, Qt::AscendingOrder);
    for (int i = 0; i < items.length(); i++) {
        Highlighter* highligher = qvariant_cast<Highlighter*>(items[i]->data(int(DataKey::highlighter)));
        if (highligher != nullptr) {
            QPointF localCursor = items[i]->mapFromScene(event->pos());
            if (highligher->isInRange(localCursor)) {
                const QPointF oldHighlight = highlight;
                highlight = items[i]->mapToScene(highligher->selectPoint(localCursor));
                if (!showHighlight || oldHighlight != highlight) {
                    update(oldHighlight.x()-HIGHLIGHT_RADIUS, oldHighlight.y()-HIGHLIGHT_RADIUS, HIGHLIGHT_DIAMETER, HIGHLIGHT_DIAMETER);
                    update(highlight.x()-HIGHLIGHT_RADIUS, highlight.y()-HIGHLIGHT_RADIUS, HIGHLIGHT_DIAMETER, HIGHLIGHT_DIAMETER);
                }
                showHighlight = true;
                return;
            }
        }
    }
    if (showHighlight) update(highlight.x()-HIGHLIGHT_RADIUS, highlight.y()-HIGHLIGHT_RADIUS, HIGHLIGHT_DIAMETER, HIGHLIGHT_DIAMETER);
    showHighlight = false;
}

void GraphicsDiagram::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    hoverMoveEvent(event);
}
