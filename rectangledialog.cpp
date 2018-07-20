#include "rectangledialog.h"
#include "ui_rectangledialog.h"
#include <QDoubleValidator>
#include <QIcon>
#include <QPixmap>
#include <QColorDialog>
#include <QDebug>

RectangleDialog::RectangleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RectangleDialog)
{
    ui->setupUi(this);
    ui->anchorX->setValidator(new QDoubleValidator());
    ui->anchorY->setValidator(new QDoubleValidator());
    ui->width->setValidator(new QDoubleValidator(0, INFINITY, 6));
    ui->height->setValidator(new QDoubleValidator(0, INFINITY, 6));
    ui->rotation->setValidator(new QDoubleValidator());
    ui->radiusX->setValidator(new QDoubleValidator(0, INFINITY, 6));
    ui->radiusY->setValidator(new QDoubleValidator(0, INFINITY, 6));

    QMetaEnum anchorEnum = OcDraw::anchorEnum();
    QList<QAbstractButton*> buttons = ui->anchorButtons->buttons();
    foreach (QAbstractButton* button, buttons) {
        int id = anchorEnum.keyToValue(button->objectName().toLatin1().data());
        ui->anchorButtons->setId(button, id);
    }

    setColorIcon(model.fillColor, ui->fillColor);
    setColorIcon(model.strokeColor, ui->strokeColor);

    editing = false;
}

RectangleDialog::~RectangleDialog()
{
    delete ui;
}

void RectangleDialog::editShape(RectangleModel *const model)
{
    this->model.x = model->x;
    ui->anchorX->setText(QString::number(model->x, 'f'));

    this->model.y = model->y;
    ui->anchorY->setText(QString::number(model->y, 'f'));

    this->model.width = model->width;
    ui->width->setText(QString::number(model->width, 'f'));

    this->model.height = model->height;
    ui->height->setText(QString::number(model->height, 'f'));

    this->model.cornerRadiusX = model->cornerRadiusX;
    ui->radiusX->setText(QString::number(model->cornerRadiusX, 'f'));

    this->model.cornerRadiusY = model->cornerRadiusY;
    ui->radiusY->setText(QString::number(model->cornerRadiusY, 'f'));

    this->model.rotation = model->rotation;
    ui->rotation->setText(QString::number(model->rotation, 'f'));

    this->model.fill = model->fill;
    ui->fill->setChecked(model->fill);
    setColorIcon(model->fillColor, ui->fillColor);

    this->model.stroke = model->stroke;
    ui->stroke->setChecked(model->stroke);
    setColorIcon(model->strokeColor, ui->strokeColor);
    this->model.strokeWidth = model->strokeWidth;
    ui->strokeWidth->setText(QString::number(model->strokeWidth, 'f'));

    this->model.anchor = model->anchor;
    ui->anchorButtons->button(model->anchor)->setChecked(true);

    editing = true;
}

void RectangleDialog::on_anchorX_textChanged(const QString &arg1)
{
    model.x = arg1.toDouble();
    if (editing) emit shapeChanged(&model, OcDraw::position);
}

void RectangleDialog::on_anchorY_textChanged(const QString &arg1)
{
    model.y = arg1.toDouble();
    if (editing) emit shapeChanged(&model, OcDraw::position);
}

void RectangleDialog::on_width_textChanged(const QString &arg1)
{
    model.width = arg1.toDouble();
    validate();
}

void RectangleDialog::on_height_textChanged(const QString &arg1)
{
    model.height = arg1.toDouble();
    validate();
}

void RectangleDialog::validate()
{
    if (model.width > 0 && model.height > 0) {
        if (editing) emit shapeChanged(&model, OcDraw::size);
        else {
            editing = true;
            emit addShape(&model);
        }
    }
    else if (editing) {
        editing = false;
        emit deleteShape(&model);
    }
}

void RectangleDialog::on_radiusX_textChanged(const QString &arg1)
{
    model.cornerRadiusX = arg1.toDouble();
    emit shapeChanged(&model, OcDraw::other);
}

void RectangleDialog::on_radiusY_textChanged(const QString &arg1)
{
    model.cornerRadiusY = arg1.toDouble();
    emit shapeChanged(&model, OcDraw::other);
}

void RectangleDialog::on_rotation_textChanged(const QString &arg1)
{
    model.rotation = arg1.toDouble();
    emit shapeChanged(&model, OcDraw::rotation);
}

void RectangleDialog::on_fillColor_clicked()
{
    const QColor color = QColorDialog::getColor(model.fillColor, this, "Select Fill Color", QColorDialog::ShowAlphaChannel | QColorDialog::DontUseNativeDialog);

    if (color.isValid()) {
        setFillColor(color);
    }
}

void RectangleDialog::on_strokeColor_clicked()
{
    const QColor color = QColorDialog::getColor(model.strokeColor, this, "Select Stroke Color", QColorDialog::ShowAlphaChannel | QColorDialog::DontUseNativeDialog);

    if (color.isValid()) {
        setStrokeColor(color);
    }
}

void RectangleDialog::on_fill_toggled(bool checked)
{
   model.fill = checked;
   emit shapeChanged(&model, OcDraw::fill);
}

void RectangleDialog::setFillColor(const QColor fillColor)
{
    if (fillColor != model.fillColor) {
        model.fillColor = fillColor;
        setColorIcon(fillColor, ui->fillColor);
        emit shapeChanged(&model, OcDraw::fill);
    }
}

void RectangleDialog::on_stroke_toggled(bool checked)
{
   model.stroke = checked;
   emit shapeChanged(&model, OcDraw::stroke);
}

void RectangleDialog::setStrokeColor(const QColor strokeColor)
{
    if (model.strokeColor != strokeColor) {
        model.strokeColor = strokeColor;
        setColorIcon(strokeColor, ui->strokeColor);
        emit shapeChanged(&model, OcDraw::stroke);
    }
}

void RectangleDialog::setColorIcon(const QColor color, QToolButton *button)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(color);
    button->setIcon(QIcon(pixmap));
}

void RectangleDialog::on_strokeWidth_textChanged(const QString &arg1)
{
    model.strokeWidth = arg1.toDouble();
    emit shapeChanged(&model, OcDraw::stroke);
}

void RectangleDialog::on_anchorButtons_buttonToggled(int id, bool checked)
{
    if (checked) {
        model.anchor = (OcDraw::Anchor) id;
        emit shapeChanged(&model, OcDraw::other);
    }
}
