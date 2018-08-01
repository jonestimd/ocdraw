#ifndef SHAPELISTENER_H
#define SHAPELISTENER_H

#include <QGraphicsItem>

class ShapeListener
{
public:
    ShapeListener();
    virtual ~ShapeListener() = 0;

    virtual void onShapeMoved(QGraphicsItem* shape) = 0;
};

#endif // SHAPELISTENER_H
