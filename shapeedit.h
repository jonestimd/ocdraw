#ifndef SHAPEEDIT_H
#define SHAPEEDIT_H

#include <QPointF>

/**
 * @brief The ShapeEdit class defines the interface for classes that update a shape based on mouse events.
 */
class ShapeEdit
{
public:
    ShapeEdit();
    virtual ~ShapeEdit() = 0;

    virtual void adjust(QPointF delta) = 0;
};

#endif // SHAPEEDIT_H
