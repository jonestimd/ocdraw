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
    moving = false;
    highlighted = nullptr;

    QRadialGradient gradient = QRadialGradient(0.5, 0.5, 1);
    gradient.setColorAt(0.0, Qt::yellow);
    gradient.setColorAt(1.0, Qt::black);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    highlightBrush = QBrush(gradient);
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
    if (highlighted != nullptr && ! moving) {
        painter->setBrush(highlightBrush);
        painter->drawEllipse(highlight);
    }
}

// TODO draw shape using mouse
// TODO resize using ctrl+mouse
void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (highlighted != nullptr && event->button() == Qt::LeftButton) {
        moving = true;
        update(highlight);
        emit selectShape(highlighted, event->scenePos());
    }
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (moving) {
        QPointF delta = event->scenePos() - event->lastScenePos();
        highlighted->moveBy(delta.x(), delta.y());
        highlight.translate(delta);
        emit shapeMoved(highlighted);
    }
    else {
        search.moveCenter(event->scenePos());
        QList<QGraphicsItem*> items = this->items(search, Qt::IntersectsItemShape, Qt::AscendingOrder);
        for (int i = 0; i < items.length(); i++) {
            SelectableShape* highligher = dynamic_cast<SelectableShape*>(items[i]);
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
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (moving) {
        QPointF delta = event->scenePos() - event->lastScenePos();
        highlighted->moveBy(delta.x(), delta.y());
        highlight.translate(delta);
        emit shapeMoved(highlighted);
        moving = false;
        update(highlight);
    }
}
