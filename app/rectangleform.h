#ifndef RECTANGLEFORM_H
#define RECTANGLEFORM_H

#include "ocdglobals.h"
#include "shapeanchor.h"
#include "diagramscene.h"
#include "shapeform.h"
#include "shapeedit.h"
#include "roundedrect.h"
#include <QLineEdit>
#include <QToolButton>

namespace Ui {
class RectangleForm;
}

/**
 * @brief The RectangleForm class provides the input controls for modifying the parameters of a rectangle.
 */
class RectangleForm : public ShapeForm
{
    Q_OBJECT

public:
    explicit RectangleForm(QWidget* parent, DiagramScene* diagram);
    ~RectangleForm() override;

    virtual void initialize() override;
    virtual void uninitialize(bool closing) override;

    void editShape(RoundedRect* shape);
    void editShape(RoundedRect* shape, QPointF scenePos, ShapeAction action);

signals:
    void addShape(RoundedRect *shape);
    void deleteShape(RoundedRect *shape);
    void shapeChanged(RoundedRect *shape);

protected:

private slots:
    void on_anchorX_textEdited(const QString &arg1);
    void on_anchorY_textEdited(const QString &arg1);
    void on_width_textEdited(const QString &arg1);
    void on_height_textEdited(const QString &arg1);
    void on_radiusX_textEdited(const QString &arg1);
    void on_radiusY_textEdited(const QString &arg1);
    void on_rotation_textEdited(const QString &arg1);
    void on_name_textEdited(const QString &arg1);

    void on_fill_toggled(bool checked);
    void on_fillColor_clicked();

    void on_stroke_toggled(bool checked);
    void on_strokeColor_clicked();
    void on_strokeWidth_textEdited(const QString &arg1);

    void on_anchorButtons_buttonToggled(int id, bool checked);

    void on_newButton_clicked();
    void on_deleteButton_clicked();

    void on_changeShape(QPointF delta, bool complete);
    void on_beginDraw(QPointF scenePos);

private:
    Ui::RectangleForm *ui;
    RoundedRect* rect;
    QColor fillColor;
    QColor strokeColor;
    DiagramScene* diagram;
    long nextId;

    ShapeEdit* edit;

    void validate(qreal width, qreal height);
    void createRect(ShapeAnchor::Point anchor, qreal width, qreal height);
    void watchEvents();
    void unwatchEvents();
    void reset();

    struct MoveRectangle : public ShapeEdit
    {
        MoveRectangle(RectangleForm* form, QPointF scenePos);
        virtual void adjust(QPointF scenePos) override;
    private:
        RectangleForm* form;
        QPointF lastPos;
    };

    struct ResizeRectangle : public ShapeEdit
    {
        ResizeRectangle(RectangleForm* form, QPointF scenePos);
        virtual void adjust(QPointF scenePos) override;
    private:
        RectangleForm* form;
        ShapeAnchor::Point resizeHandle;
    };

    struct DrawRectangle : public ShapeEdit
    {
        DrawRectangle(RectangleForm* form, QPointF scenePos);
        virtual void adjust(QPointF scenePos) override;
    private:
        RectangleForm* form;
        QPointF startPos;
    };
};

#endif // RECTANGLEFORM_H
