#ifndef HIGHLIGHTITEMPROXY_H
#define HIGHLIGHTITEMPROXY_H

#include "ocdglobals.h"
#include "shapelistener.h"
#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneEvent>
#include <QPainter>

/**
 * @brief The GraphicsDiagram class is the root container for shapes in a diagram.
 * It handles displaying the highlight cursor on shapes in the diagram and editing shapes using the mouse.
 *
 * Overrides \c mousePressEvent, \c mouseMoveEvent, and \c mouseReleaseEvent to handle selecting/editing a shape using the mouse.
 *
 * Overrides \c hoverEnterEvent, \c hoverMoveEvent, and \c hoverLeaveEvent to handle highlighting shapes for selection.
 */
class GraphicsDiagram : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    explicit GraphicsDiagram(QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void setShapeListener(ShapeListener* shapeListener);
    void clearShapeListener();

signals:
    void selectShape(QGraphicsItem* shape, QPointF pos);

public slots:
    void on_shapeChanged(QGraphicsItem* shape);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QRectF search;
    QRectF highlight;
    QBrush highlightBrush;
    QGraphicsItem* highlighted;
    bool hideHighlight;
    ShapeListener* shapeListener;
};

#endif // HIGHLIGHTITEMPROXY_H
