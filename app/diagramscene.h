#ifndef SCENE_H
#define SCENE_H

#include "ocdglobals.h"
#include <QGraphicsScene>

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    DiagramScene(QObject* parent = nullptr);

    /**
     * @brief Overrides \c QGraphicsScene to handle removal of the highlighted shape.
     */
    void removeItem(QGraphicsItem* item);

signals:
    /**
     * @brief The selectShape signal is emitted when the user clicks on a shape.
     * @param shape
     * @param scenePos location of the selected control point on the shape
     * @param action
     */
    void selectShape(QGraphicsItem* shape, QPointF scenePos, ShapeAction action);
    /**
     * @brief The changeShape signal is emitted when the user is moving/editing a shape using the mouse.
     * @param delta the amount to move the shape or control point
     * @param complete true if this is the end of the edit
     */
    void changeShape(QPointF delta, bool complete);
    /**
     * @brief The beginDraw signla is emitted for a mouse press that doesn't select a shape.
     * @param scenePos
     */
    void beginDraw(QPointF scenePos);

protected:
    virtual void drawBackground(QPainter* painter, const QRectF& rect) override;
    virtual void drawForeground(QPainter* painter, const QRectF& rect) override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QPen axisPen;
    QRectF search;
    QRectF highlight;
    QBrush highlightBrush;
    QGraphicsItem* highlighted;

    bool dragging;

    bool updateHighlight(QGraphicsItem* item, QPointF scenePos);
};

#endif // SCENE_H
