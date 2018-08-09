#include "shapeanchor.h"
#include "ocdglobals.h"
#include <QAbstractButton>

void ShapeAnchor::setButtonIds(QButtonGroup *anchorButtonGroup)
{
    QMetaEnum enumMeta = staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Point"));
    for (auto button : anchorButtonGroup->buttons()) {
        int id = enumMeta.keyToValue(button->objectName().toLatin1().data());
        anchorButtonGroup->setId(button, id);
    }
}

QRectF ShapeAnchor::getRect(ShapeAnchor::Point anchor, qreal width, qreal height)
{
    qreal x = -width/2;
    if (anchor & LEFT) x = 0;
    else if (anchor & RIGHT) x = -width;

    qreal y = -height/2;
    if (anchor & TOP) y = 0;
    else if (anchor & BOTTOM) y = -height;

    return QRectF(x, y, width, height);
}

ShapeAnchor::Point ShapeAnchor::getAnchor(QRectF rect, QPointF anchor)
{
    int point = 0;

    if (std::abs(anchor.x() - rect.right()) <= HIGHLIGHT_RADIUS) point += RIGHT;
    else if (std::abs(anchor.x() - rect.left()) <= HIGHLIGHT_RADIUS) point += LEFT;

    if (std::abs(anchor.y() - rect.top()) <= HIGHLIGHT_RADIUS) point += TOP;
    else if (std::abs(anchor.y() - rect.bottom()) <= HIGHLIGHT_RADIUS) point += BOTTOM;

    return Point(point);
}

int ShapeAnchor::horizontal(ShapeAnchor::Point value)
{
    return value & Horizontal;
}

int ShapeAnchor::vertical(ShapeAnchor::Point value)
{
    return value & Vertical;
}

bool ShapeAnchor::isCenter(Point value, Mask mask) {
    return (value & mask) == 0;
}

ShapeAnchor::Point ShapeAnchor::swapX(ShapeAnchor::Point value)
{
    return (value & Horizontal) == 0 ? value : Point(value ^ Horizontal);
}

ShapeAnchor::Point ShapeAnchor::swapY(ShapeAnchor::Point value)
{
    return (value & Vertical) == 0 ? value : Point(value ^ Vertical);
}

ShapeAnchor::Point ShapeAnchor::setX(ShapeAnchor::Point value, int xAnchor)
{
    return Point((value & Vertical) + xAnchor);
}

ShapeAnchor::Point ShapeAnchor::setY(ShapeAnchor::Point value, int yAnchor)
{
    return Point((value & Horizontal) + yAnchor);
}
