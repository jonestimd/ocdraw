#include "shapeanchor.h"
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
    int flags = int(anchor);

    qreal x = -width/2;
    if (flags & LEFT) x = 0;
    else if (flags & RIGHT) x = -width;

    qreal y = -height/2;
    if (flags & TOP) y = 0;
    else if (flags & BOTTOM) y = -height;

    return QRectF(x, y, width, height);
}

ShapeAnchor::Point ShapeAnchor::getAnchor(QRectF rect, QPointF anchor)
{
    int point = 0;

    if (anchor.x() == rect.right()) point += RIGHT;
    else if (anchor.x() == rect.left()) point += LEFT;

    if (anchor.y() == rect.top()) point += TOP;
    else if (anchor.y() == rect.bottom()) point += BOTTOM;

    return Point(point);
}
