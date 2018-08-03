#ifndef SCENE_H
#define SCENE_H

#include "ocdglobals.h"
#include <QGraphicsScene>

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    DiagramScene(QObject* parent = nullptr);

signals:
    void selectShape(QGraphicsItem* shape, QPointF scenePos);
    void shapeMoved(QGraphicsItem* shape);

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

    bool moving;
};

#endif // SCENE_H
