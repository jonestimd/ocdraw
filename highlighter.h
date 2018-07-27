#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QObject>
#include <QPointF>

/**
 * @brief Helper for selecting a point to highlight on a shape.
 */
class Highlighter
{
public:
    Highlighter();
    virtual ~Highlighter();

    /**
     * @brief Check if the cursor is within the selection range of the shape.
     * @param cursor position of the mouse in the shape's coordinates
     * @return
     */
    virtual bool isInRange(QPointF cursor) const = 0;

    /**
     * @brief Select a point on the shape to highlight.
     * @param cursor position of the mouse in the shape's coordinates
     * @return the point to hightlight
     */
    virtual QPointF selectPoint(QPointF cursor) const = 0;
};
Q_DECLARE_METATYPE(Highlighter*)

#endif // HIGHLIGHTER_H
