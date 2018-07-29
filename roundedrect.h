#ifndef ROUNDEDRECT_H
#define ROUNDEDRECT_H

#include <QGraphicsRectItem>
#include <QPainter>

/**
 * @brief The RoundedRect class extends \c QGraphicsRectItem to display rounded corners.
 */
class RoundedRect : public QGraphicsRectItem
{
public:
    enum { Type = UserType + 1 };
    RoundedRect(QRectF rect, QGraphicsItem* parent = nullptr);
    virtual ~RoundedRect() override;

    int type() const override;

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
