#ifndef HIGHLIGHTITEMPROXY_H
#define HIGHLIGHTITEMPROXY_H

#include "ocdglobals.h"
#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneEvent>
#include <QPainter>

/**
 * @brief The GraphicsDiagram class is the root container for shapes in a diagram.
 * It handles displaying the highlight cursor on shapes in the diagram and editing shapes using the mouse.
 */
class GraphicsDiagram : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    explicit GraphicsDiagram(QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

signals:
    void selectShape(QGraphicsItem *shape, QPointF pos);

public slots:

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
    QGraphicsItem *highlighted;
    bool hideHighlight;
};

#endif // HIGHLIGHTITEMPROXY_H
