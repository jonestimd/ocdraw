#ifndef SHAPEANCHOR_H
#define SHAPEANCHOR_H

#include <qobjectdefs.h>
#include <qmetaobject.h>
#include <QButtonGroup>

#define LEFT 0x20
#define RIGHT 0x10
#define TOP 0x02
#define BOTTOM 0x01
#define CENTER 0

namespace ShapeAnchor
{
    Q_NAMESPACE

    /**
     * @brief Enum for shape anchor point.
     */
    enum Point {
        TopLeft = LEFT + TOP,
        Top = TOP,
        TopRight = RIGHT + TOP,
        Left = LEFT,
        Center = 0,
        Right = RIGHT,
        BottomLeft = LEFT + BOTTOM,
        Bottom = BOTTOM,
        BottomRight = RIGHT + BOTTOM
    };
    Q_ENUM_NS(Point)

    /**
     * @brief Enum for selecting components of a shape anchor.
     */
    enum Mask {
        Horizontal = LEFT + RIGHT,
        Vertical = TOP + BOTTOM,
        Both = Horizontal + Vertical
    };

    void setButtonIds(QButtonGroup* anchorButtonGroup);

    /**
     * @brief Create a \c QRectF with the specified width, height and anchor point.
     */
    QRectF getRect(Point anchor, qreal width, qreal height);

    Point getAnchor(QRectF rect, QPointF anchor);

    QPointF getPos(QRectF rect, int anchor);
    QPointF getPos(QRectF rect, Point anchor);

    int horizontal(Point value);
    int vertical(Point value);
    bool isCenter(Point value, Mask mask = Both);

    Point swapX(Point value);
    Point swapY(Point value);

    Point setX(Point value, int xAnchor);
    Point setY(Point value, int yAnchor);
};

#endif // SHAPEANCHOR_H
