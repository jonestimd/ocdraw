#ifndef GRAPHICSITEMEVENTPROXY_H
#define GRAPHICSITEMEVENTPROXY_H

#include <QGraphicsObject>
#include <QEvent>

/**
 * @brief The GraphicsItemEventProxy class generates signals when a shape is moved using the mouse.
 * It must be added to the scene and installed as the scene event filter on the shape before it will generate any signals.
 * It is used by shape tool dialogs to update the position inputs as the shape is moved.
 */
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
