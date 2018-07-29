#include "roundedrect.h"
#include "ocdglobals.h"
#include "recthighlighter.h"
#include "QVariant"

RoundedRect::RoundedRect(QRectF rect, QGraphicsItem* parent) :
    QGraphicsRectItem(rect, parent)
{
    m_cornerWidth = 0;
    m_cornerHeight = 0;
    setAcceptHoverEvents(true);
    Highlighter* highlighter = new RectHighlighter(this);
    setData(int(DataKey::Highlighter), QVariant::fromValue(highlighter));
}

RoundedRect::~RoundedRect()
{
    delete qvariant_cast<Highlighter*>(data(int(DataKey::Highlighter)));
}

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
