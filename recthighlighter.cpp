#include "recthighlighter.h"

RectHighlighter::RectHighlighter(const RoundedRect* rect) : Highlighter()
{
    this->rect = rect;
}

RectHighlighter::~RectHighlighter() {}

bool RectHighlighter::isInRange(QPointF cursor) const
{
    QRectF bounds = rect->rect();
    return isInside(cursor.x(), bounds.x(), bounds.width()) && isInside(cursor.y(), bounds.y(), bounds.height()) &&
            (isOutside(cursor.x(), bounds.x(), bounds.width()) || isOutside(cursor.y(), bounds.y(), bounds.height()));
}

QPointF RectHighlighter::selectPoint(QPointF cursor) const
{
    qreal x, y;
    QRectF bounds = rect->rect();
    if (cursor.x() <= bounds.x()+HIGHLIGHT_RADIUS) x = bounds.x();
    else if (cursor.x() >= bounds.x()+bounds.width()-HIGHLIGHT_RADIUS) x = bounds.x()+bounds.width();
    else x = bounds.x()+bounds.width()/2;

    if (cursor.y() <= bounds.y()+HIGHLIGHT_RADIUS) y = bounds.y();
    else if (cursor.y() >= bounds.y()+bounds.height()-HIGHLIGHT_RADIUS) y = bounds.y()+bounds.height();
    else y = bounds.y()+bounds.height()/2;

    return QPointF(x, y);
}

bool RectHighlighter::isInside(qreal value, qreal min, qreal size)
{
    return value >= min-HIGHLIGHT_RADIUS && value <= min+size+HIGHLIGHT_RADIUS;
}

bool RectHighlighter::isOutside(qreal value, qreal min, qreal size)
{
    return value <= min+HIGHLIGHT_RADIUS || value >= min+size-HIGHLIGHT_RADIUS;
}
