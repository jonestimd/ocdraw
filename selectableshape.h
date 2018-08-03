#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QPointF>

/**
 * @brief The Highlighter class defines the interface for selecting the shape to highlight and the point to highlight on the shape.
 * A highlighter is associated to a shape as a data element with the \c OcDraw::highlighter key.
 */
class SelectableShape
{
public:
    SelectableShape();
    virtual ~SelectableShape();

    /**
     * @brief Check if the cursor is within the selection range of the shape.
     * @param cursor position of the mouse in the shape's coordinates
     * @return true if the shape is in range
     */
    virtual bool isInRange(QPointF cursor) const = 0;

    /**
     * @brief Select a point on the shape to highlight.
     * @param cursor position of the mouse in the shape's coordinates
     * @return the point to hightlight
     */
    virtual QPointF selectPoint(QPointF cursor) const = 0;
};

#endif // HIGHLIGHTER_H
