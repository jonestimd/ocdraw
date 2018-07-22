#include "roundedrect.h"

RoundedRect::RoundedRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent) :
    QGraphicsRectItem(x, y, width, height, parent)
{
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
        update(rect());
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
        update(rect());
    }
}
