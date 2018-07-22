#ifndef ROUNDEDRECT_H
#define ROUNDEDRECT_H

#include <QGraphicsRectItem>
#include <QPainter>

class RoundedRect : public QGraphicsRectItem
{
public:
    RoundedRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    qreal cornerWidth();
    void setCornerWidth(qreal width);

    qreal cornerHeight();
    void setCornerHeight(qreal height);

private:
    qreal m_cornerWidth;
    qreal m_cornerHeight;
};

#endif // ROUNDEDRECT_H
