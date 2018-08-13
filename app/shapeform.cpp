#include "shapeform.h"

ShapeForm::ShapeForm(QWidget* parent) : QWidget(parent) {}

ShapeForm::~ShapeForm() {}

void ShapeForm::setColorIcon(const QColor color, QToolButton *button)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(color);
    button->setIcon(QIcon(pixmap));
}

void ShapeForm::setText(QLineEdit *field, qreal value)
{
    field->setText(QString().sprintf("%.6g", value));
}
