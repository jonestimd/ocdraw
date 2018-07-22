#ifndef RECTANGLEDIALOG_H
#define RECTANGLEDIALOG_H

#include "rectanglemodel.h"
#include "tooldialog.h"
#include "roundedrect.h"
#include <QToolButton>

namespace Ui {
class RectangleDialog;
}

class RectangleDialog : public ToolDialog
{
    Q_OBJECT

public:
    explicit RectangleDialog(QWidget *parent = nullptr);
    ~RectangleDialog();
    enum DataKey { Anchor };

public slots:
    void editShape(RoundedRect *const shape);

signals:
    void addShape(RoundedRect *const shape);
    void deleteShape();
    void shapeChanged(RoundedRect *const shape);

private slots:
    void on_anchorX_textChanged(const QString &arg1);
    void on_anchorY_textChanged(const QString &arg1);
    void on_width_textChanged(const QString &arg1);
    void on_height_textChanged(const QString &arg1);
    void on_radiusX_textChanged(const QString &arg1);
    void on_radiusY_textChanged(const QString &arg1);
    void on_rotation_textChanged(const QString &arg1);

    void on_fill_toggled(bool checked);
    void on_fillColor_clicked();

    void on_stroke_toggled(bool checked);
    void on_strokeColor_clicked();
    void on_strokeWidth_textChanged(const QString &arg1);

    void on_anchorButtons_buttonToggled(int id, bool checked);

private:
    Ui::RectangleDialog *ui;
    RoundedRect* rect;
    QColor fillColor;
    QColor strokeColor;

    void validate(qreal width, qreal height);
    void setColorIcon(const QColor color, QToolButton *button);
};

#endif // RECTANGLEDIALOG_H
