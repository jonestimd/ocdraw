#ifndef ROUNDEDRECT_H
#define ROUNDEDRECT_H

#include "selectableshape.h"
#include "shapeanchor.h"
#include <QGraphicsRectItem>
#include <QPainter>

/**
 * @brief The RoundedRect class extends \c QGraphicsRectItem to display rounded corners.
 */
class RoundedRect : public QGraphicsRectItem, public SelectableShape
{
public:
    enum { Type = UserType + 1 };
    RoundedRect(QRectF rect, QGraphicsItem* parent = nullptr);
    virtual ~RoundedRect() override;

    int type() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    ShapeAnchor::Point anchor() const;
    void setAnchor(ShapeAnchor::Point anchor);

    ShapeAnchor::Point moveTo(QPointF scenePos, ShapeAnchor::Point edges);

    qreal cornerWidth() const;
    void setCornerWidth(qreal width);

    qreal cornerHeight() const;
    void setCornerHeight(qreal height);

    virtual bool isInRange(QPointF cursor) const override;
    virtual QPointF selectPoint(QPointF cursor) const override;

private:
    ShapeAnchor::Point m_anchor;
    qreal m_cornerWidth;
    qreal m_cornerHeight;

    static bool isInside(qreal value, qreal min, qreal size);
    static bool isOutside(qreal value, qreal min, qreal size);
};

#endif // ROUNDEDRECT_H
