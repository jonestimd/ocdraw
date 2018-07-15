#include "rectangledialog.h"
#include "ui_rectangledialog.h"
#include <QDoubleValidator>
#include <QIcon>
#include <QPixmap>
#include <QColor>
#include <QColorDialog>
#include <QDebug>

RectangleDialog::RectangleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RectangleDialog)
{
    ui->setupUi(this);
    ui->anchorX->setValidator(new QDoubleValidator());
    ui->anchorY->setValidator(new QDoubleValidator());
    ui->width->setValidator(new QDoubleValidator());
    ui->height->setValidator(new QDoubleValidator());
    ui->rotation->setValidator(new QDoubleValidator());

    setFillColor(Qt::black);
    setStrokeColor(Qt::black);
}

RectangleDialog::~RectangleDialog()
{
    delete ui;
}

void RectangleDialog::on_anchorX_textChanged(const QString &arg1)
{
    qDebug() << arg1;
}

void RectangleDialog::on_fillColor_clicked()
{
    const QColor color = QColorDialog::getColor(fillColor, this, "Select Fill Color", QColorDialog::ShowAlphaChannel | QColorDialog::DontUseNativeDialog);

    if (color.isValid()) {
        setFillColor(color);
    }
}

void RectangleDialog::on_strokeColor_clicked()
{
    const QColor color = QColorDialog::getColor(strokeColor, this, "Select Stroke Color", QColorDialog::ShowAlphaChannel | QColorDialog::DontUseNativeDialog);

    if (color.isValid()) {
        setStrokeColor(color);
    }
}

void RectangleDialog::setFillColor(const QColor fillColor)
{
    this->fillColor = fillColor;
    QPixmap pixmap(16, 16);
    pixmap.fill(fillColor);
    ui->fillColor->setIcon(QIcon(pixmap));
}

void RectangleDialog::setStrokeColor(const QColor StrokeColor)
{
    this->strokeColor = StrokeColor;
    QPixmap pixmap(16, 16);
    pixmap.fill(StrokeColor);
    ui->strokeColor->setIcon(QIcon(pixmap));
}
