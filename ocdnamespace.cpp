#include "ocdnamespace.h"

namespace OcDraw
{
    QMetaEnum anchorEnum()
    {
        return OcDraw::staticMetaObject.enumerator(OcDraw::staticMetaObject.indexOfEnumerator("Anchor"));
    }
}
