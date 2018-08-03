#include "roundedrect.h"
#include "ocdglobals.h"
#include "QVariant"

RoundedRect::RoundedRect(QRectF rect, QGraphicsItem* parent) :
    QGraphicsRectItem(rect, parent),
    SelectableShape()
{
    m_cornerWidth = 0;
    m_cornerHeight = 0;
    setAcceptHoverEvents(true);
}

RoundedRect::~RoundedRect() {}

int RoundedRect::type() const
{
    return Type;
}

void RoundedRect::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (m_cornerWidth > 0 && m_cornerHeight > 0) {
        painter->setPen(pen());
        painter->drawRoundedRect(rect(), m_cornerWidth, m_cornerHeight);
    }
    else QGraphicsRectItem::paint(painter, option, widget);
}

qreal RoundedRect::cornerWidth()
{
    return m_cornerWidth;
}

void RoundedRect::setCornerWidth(qreal width)
{
    if (m_cornerHeight != width) {
        m_cornerWidth = width;
        update();
    }
}

qreal RoundedRect::cornerHeight()
{
    return m_cornerHeight;
}

void RoundedRect::setCornerHeight(qreal height)
{
    if (m_cornerHeight != height) {
        m_cornerHeight = height;
        update();
    }
}

bool RoundedRect::isInRange(QPointF cursor) const
{
    QRectF bounds = rect();
    return isInside(cursor.x(), bounds.x(), bounds.width()) && isInside(cursor.y(), bounds.y(), bounds.height()) &&
            (isOutside(cursor.x(), bounds.x(), bounds.width()) || isOutside(cursor.y(), bounds.y(), bounds.height()));
}

QPointF RoundedRect::selectPoint(QPointF cursor) const
{
    qreal x, y;
    QRectF bounds = rect();
    if (cursor.x() <= bounds.x()+HIGHLIGHT_RADIUS) x = bounds.x();
    else if (cursor.x() >= bounds.x()+bounds.width()-HIGHLIGHT_RADIUS) x = bounds.x()+bounds.width();
    else x = bounds.x()+bounds.width()/2;

    if (cursor.y() <= bounds.y()+HIGHLIGHT_RADIUS) y = bounds.y();
    else if (cursor.y() >= bounds.y()+bounds.height()-HIGHLIGHT_RADIUS) y = bounds.y()+bounds.height();
    else y = bounds.y()+bounds.height()/2;

    return QPointF(x, y);
}

bool RoundedRect::isInside(qreal value, qreal min, qreal size)
{
    return value >= min-HIGHLIGHT_RADIUS && value <= min+size+HIGHLIGHT_RADIUS;
}

bool RoundedRect::isOutside(qreal value, qreal min, qreal size)
{
    return value <= min+HIGHLIGHT_RADIUS || value >= min+size-HIGHLIGHT_RADIUS;
}
