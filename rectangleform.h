#ifndef RECTANGLEFORM_H
#define RECTANGLEFORM_H

#include "ocdglobals.h"
#include "diagramscene.h"
#include "shapeform.h"
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

public slots:
    void editShape(RoundedRect* shape);

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

    void on_ShapeMoved(QGraphicsItem* shape);

private:
    Ui::RectangleForm *ui;
    RoundedRect* rect;
    QColor fillColor;
    QColor strokeColor;
    DiagramScene* diagram;
    long nextId;

    void validate(qreal width, qreal height);
    void setColorIcon(const QColor color, QToolButton *button);
    void setText(QLineEdit* text, qreal value);
    void watchEvents();
    void unwatchEvents();
    void reset();
};

#endif // RECTANGLEFORM_H
