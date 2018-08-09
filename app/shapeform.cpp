#include "shapeform.h"

ShapeForm::ShapeForm(QWidget* parent) : QWidget(parent) {}

ShapeForm::~ShapeForm() {}

void ShapeForm::setText(QLineEdit *field, qreal value)
{
    field->setText(QString().sprintf("%.6g", value));
}
