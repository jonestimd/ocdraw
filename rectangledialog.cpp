#include "rectangledialog.h"
#include "ui_rectangledialog.h"
#include <QDoubleValidator>
#include <QIcon>
#include <QPixmap>
#include <QColorDialog>

RectangleDialog::RectangleDialog(QWidget *parent) :
    ToolDialog(parent),
    ui(new Ui::RectangleDialog)
{
    ui->setupUi(this);
    ui->anchorX->setValidator(new QDoubleValidator());
    ui->anchorY->setValidator(new QDoubleValidator());
    ui->width->setValidator(new QDoubleValidator(0, HUGE_VAL, 6));
    ui->height->setValidator(new QDoubleValidator(0, HUGE_VAL, 6));
    ui->rotation->setValidator(new QDoubleValidator());
    ui->radiusX->setValidator(new QDoubleValidator(0, HUGE_VAL, 6));
    ui->radiusY->setValidator(new QDoubleValidator(0, HUGE_VAL, 6));
    ui->strokeWidth->setValidator(new QDoubleValidator(0, HUGE_VAL, 6));

    QMetaEnum anchorEnum = OcDraw::anchorEnum();
    for (auto button : ui->anchorButtons->buttons()) {
        int id = anchorEnum.keyToValue(button->objectName().toLatin1().data());
        ui->anchorButtons->setId(button, id);
    }

    fillColor = Qt::black;
    strokeColor = Qt::black;
    setColorIcon(fillColor, ui->fillColor);
    setColorIcon(strokeColor, ui->strokeColor);

    rect = nullptr;
}

RectangleDialog::~RectangleDialog()
{
    delete ui;
}

void RectangleDialog::editShape(RoundedRect *const shape)
{
    this->rect = shape;
    ui->anchorX->setText(QString::number(rect->x(), 'f'));
    ui->anchorY->setText(QString::number(rect->y(), 'f'));
    ui->width->setText(QString::number(rect->rect().width(), 'f'));
    ui->height->setText(QString::number(rect->rect().height(), 'f'));
    ui->radiusX->setText(QString::number(rect->cornerWidth(), 'f'));
    ui->radiusY->setText(QString::number(rect->cornerHeight(), 'f'));
    ui->rotation->setText(QString::number(rect->rotation(), 'f'));

    ui->fill->setChecked(rect->brush().color() != Qt::transparent);
    setColorIcon(rect->brush().color(), ui->fillColor);

    ui->stroke->setChecked(rect->pen().color() != Qt::transparent);
    setColorIcon(rect->pen().color(), ui->strokeColor);
    ui->strokeWidth->setText(QString::number(rect->pen().widthF(), 'f'));

    ui->anchorButtons->button(rect->data(RectangleDialog::Anchor).value<int>())->setChecked(true);
}

void RectangleDialog::on_anchorX_textChanged(const QString &arg1)
{
    if (rect != nullptr) {
	    rect->setX(arg1.toDouble());
	    emit shapeChanged(rect);
    }
}

void RectangleDialog::on_anchorY_textChanged(const QString &arg1)
{
    if (rect != nullptr) {
	    rect->setY(arg1.toDouble());
	    emit shapeChanged(rect);
    }
}

void RectangleDialog::on_width_textChanged(const QString &arg1)
{
    validate(arg1.toDouble(), ui->height->text().toDouble());
}

void RectangleDialog::on_height_textChanged(const QString &arg1)
{
    validate(ui->width->text().toDouble(), arg1.toDouble());
}

void RectangleDialog::validate(qreal width, qreal height)
{
    if (width > 0 && height > 0) {
        if (rect != nullptr) {
            rect->setRect(0, 0, width, height);
            emit shapeChanged(rect);
        }
        else {
            rect = new RoundedRect(0, 0, width, height);
            rect->setPos(ui->anchorX->text().toDouble(), ui->anchorY->text().toDouble());
            rect->setRotation(ui->rotation->text().toDouble());
            rect->setCornerWidth(ui->radiusX->text().toDouble());
            rect->setCornerHeight(ui->radiusY->text().toDouble());
            if (ui->stroke->isChecked()) rect->setPen(QPen(QBrush(strokeColor), ui->strokeWidth->text().toDouble(), Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
            else rect->setPen(QPen(Qt::transparent));
            rect->setBrush(QBrush(ui->fill->isChecked() ? fillColor : Qt::transparent));
            emit addShape(rect);
        }
    }
    else if (rect != nullptr) {
        rect = nullptr;
        emit deleteShape();
    }
}

void RectangleDialog::on_radiusX_textChanged(const QString &arg1)
{
    if (rect != nullptr) {
        rect->setCornerWidth(arg1.toDouble());
        emit shapeChanged(rect);
    }
}

void RectangleDialog::on_radiusY_textChanged(const QString &arg1)
{
    if (rect != nullptr) {
        rect->setCornerHeight(arg1.toDouble());
        emit shapeChanged(rect);
    }
}

void RectangleDialog::on_rotation_textChanged(const QString &arg1)
{
    if (rect != nullptr) {
	    rect->setRotation(arg1.toDouble());
	    emit shapeChanged(rect);
    }
}

void RectangleDialog::on_fillColor_clicked()
{
    const QColor color = QColorDialog::getColor(fillColor, this, "Select Fill Color", QColorDialog::ShowAlphaChannel | QColorDialog::DontUseNativeDialog);

    if (color.isValid() && color != fillColor) {
        fillColor = color;
        if (rect != nullptr && ui->fill->isChecked()) {
            rect->setBrush(QBrush(fillColor));
            setColorIcon(fillColor, ui->fillColor);
		    emit shapeChanged(rect);
        }
    }
}

void RectangleDialog::on_strokeColor_clicked()
{
    const QColor color = QColorDialog::getColor(strokeColor, this, "Select Stroke Color", QColorDialog::ShowAlphaChannel | QColorDialog::DontUseNativeDialog);

    if (color.isValid() && color != strokeColor) {
        strokeColor = color;
        if (rect != nullptr && ui->stroke->isChecked()) {
            rect->setPen(QPen(QBrush(strokeColor), ui->strokeWidth->text().toDouble(), Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
            setColorIcon(strokeColor, ui->strokeColor);
		    emit shapeChanged(rect);
        }
    }
}

void RectangleDialog::on_fill_toggled(bool checked)
{
    if (rect != nullptr) {
	    rect->setBrush(QBrush(checked ? fillColor : Qt::transparent));
        emit shapeChanged(rect);
    }
}

void RectangleDialog::on_stroke_toggled(bool checked)
{
    if (rect != nullptr) {
		rect->pen().setColor(checked ? strokeColor : Qt::transparent);
        emit shapeChanged(rect);
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
    if (rect != nullptr) {
	    rect->setPen(QPen(QBrush(strokeColor), arg1.toDouble(), Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
	    emit shapeChanged(rect);
    }
}

void RectangleDialog::on_anchorButtons_buttonToggled(int id, bool checked)
{
    if (checked && rect != nullptr) {
        rect->setData(Anchor, static_cast<OcDraw::Anchor>(id));
        emit shapeChanged(rect);
    }
}
