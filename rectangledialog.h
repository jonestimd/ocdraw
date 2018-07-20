#ifndef RECTANGLEDIALOG_H
#define RECTANGLEDIALOG_H

#include "rectanglemodel.h"
#include <QDialog>
#include <QColor>
#include <QToolButton>

namespace Ui {
class RectangleDialog;
}

class RectangleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RectangleDialog(QWidget *parent = 0);
    ~RectangleDialog();

public slots:
    void editShape(RectangleModel *const model);

signals:
    void addShape(RectangleModel *const model);
    void deleteShape(RectangleModel *const model);
    void shapeChanged(RectangleModel *const model, OcDraw::ModelChange changeType);

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
    RectangleModel model;
    bool editing;

    void validate();
    void setFillColor(const QColor fillColor);
    void setStrokeColor(const QColor strokeColor);
    void setColorIcon(const QColor color, QToolButton *button);
};

#endif // RECTANGLEDIALOG_H
