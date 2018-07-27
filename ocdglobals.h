#ifndef OCDNAMESPACE_H
#define OCDNAMESPACE_H
#include <qobjectdefs.h>
#include <qmetaobject.h>
#include <QPointF>

#define HIGHLIGHT_RADIUS 5
#define HIGHLIGHT_DIAMETER HIGHLIGHT_RADIUS*2

namespace OcDraw
{
    Q_NAMESPACE

    /**
     * @brief Enum for shape anchor point.
     */
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

    const static QPointF CursorOffset(HIGHLIGHT_RADIUS, HIGHLIGHT_RADIUS);
}

/**
 * @brief Enum for QGraphicsItem data value keys.
 */
enum class DataKey {
    anchor,
    highlighter
};

#endif // OCDNAMESPACE_H
