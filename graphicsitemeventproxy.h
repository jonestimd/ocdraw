#ifndef GRAPHICSITEMEVENTPROXY_H
#define GRAPHICSITEMEVENTPROXY_H

#include <QGraphicsObject>
#include <QEvent>

class GraphicsItemEventProxy : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit GraphicsItemEventProxy(QGraphicsItem *parent = nullptr);

    bool sceneEventFilter(QGraphicsItem* watched, QEvent* event) override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

signals:
    void shapeMoved(QGraphicsItem* shape);

public slots:
};

#endif // GRAPHICSITEMEVENTPROXY_H
