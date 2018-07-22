#ifndef OCDNAMESPACE_H
#define OCDNAMESPACE_H
#include <qobjectdefs.h>
#include <qmetaobject.h>

namespace OcDraw
{
    Q_NAMESPACE

    // TODO use enum class
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

    QMetaEnum anchorEnum();
}
#endif // OCDNAMESPACE_H
