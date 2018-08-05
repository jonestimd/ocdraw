#include "roundedrect.h"
#include "ocdglobals.h"
#include "QVariant"
#include "math.h"

RoundedRect::RoundedRect(QRectF rect, QGraphicsItem* parent) :
    QGraphicsRectItem(rect, parent),
    SelectableShape()
{
    this->m_anchor = ShapeAnchor::TopLeft;
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

ShapeAnchor::Point RoundedRect::anchor() const
{
    return this->m_anchor;
}

void RoundedRect::setAnchor(ShapeAnchor::Point anchor)
{
    this->m_anchor = anchor;
    setRect(ShapeAnchor::getRect(anchor, rect().width(), rect().height()));
}

ShapeAnchor::Point RoundedRect::moveTo(QPointF scenePos, ShapeAnchor::Point edges)
{
    const qreal angle = rotation()*M_PI/180;
    const qreal cos = std::cos(angle), sin = std::sin(angle);
    const QPointF local = mapFromScene(scenePos);
    qreal rx, ry, width, height;
    rect().getRect(&rx, &ry, &width, &height);

    if (ShapeAnchor::horizontal(edges)) {
        const qreal dx = edges & LEFT ? local.x()-rx : rx+width-local.x();
        if (ShapeAnchor::isCenter(anchor(), ShapeAnchor::Horizontal)) {
            width -= 2*dx;
            rx = -width/2;
        }
        else {
            const qreal dx2 = edges & LEFT ? dx : -dx;
            if (anchor() & ShapeAnchor::horizontal(edges)) setPos(x()+dx2*cos, y()+dx2*sin);
            if ((anchor() & LEFT) == 0) rx += dx;
            width -= dx;
        }
        if (width < 0) {
            width = -width;
            setAnchor(ShapeAnchor::swapX(anchor()));
            edges = ShapeAnchor::swapX(edges);
        }
    }

    if (ShapeAnchor::vertical(edges))  {
        const qreal dy = edges & TOP ? local.y()-ry : ry+height-local.y();
        if (ShapeAnchor::isCenter(anchor(), ShapeAnchor::Vertical)) {
            height -= 2*dy;
            ry = -height/2;
        }
        else {
            const qreal dy2 = edges & TOP ? dy : -dy;
            if (anchor() & ShapeAnchor::vertical(edges)) setPos(x()-dy2*sin, y()+dy2*cos);
            if ((anchor() & TOP) == 0) ry += dy;
            height -= dy;
        }
        if (height < 0) {
            height = -height;
            setAnchor(ShapeAnchor::swapY(anchor()));
            edges = ShapeAnchor::swapY(edges);
        }
    }

    setRect(rx, ry, width, height);
    return edges;
}

qreal RoundedRect::cornerWidth() const
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

qreal RoundedRect::cornerHeight() const
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
