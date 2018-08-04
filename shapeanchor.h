#ifndef SHAPEANCHOR_H
#define SHAPEANCHOR_H

#include <qobjectdefs.h>
#include <qmetaobject.h>
#include <QButtonGroup>

#define LEFT 0x20
#define RIGHT 0x10
#define TOP 0x02
#define BOTTOM 0x01

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

    void setButtonIds(QButtonGroup* anchorButtonGroup);

    QRectF getRect(Point anchor, qreal width, qreal height);

    Point getAnchor(QRectF rect, QPointF anchor);
};

#endif // SHAPEANCHOR_H
