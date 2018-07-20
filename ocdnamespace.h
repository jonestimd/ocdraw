#ifndef OCDNAMESPACE_H
#define OCDNAMESPACE_H
#include <qobjectdefs.h>
#include <qmetaobject.h>

namespace OcDraw
{
    Q_NAMESPACE

    enum Anchor {
        topLeft,
        top,
        topRight,
        left,
        center,
        right,
        bottomLeft,
        bottom,
        bottomRight
    };
    Q_ENUM_NS(Anchor)

    enum ModelChange {
        position,
        size,
        rotation,
        anchor,
        fill,
        stroke,
        other
    };
    Q_ENUM_NS(ModelChange)

    QMetaEnum anchorEnum();
}
#endif // OCDNAMESPACE_H
