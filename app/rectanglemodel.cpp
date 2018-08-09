#include "rectanglemodel.h"

RectangleModel::RectangleModel()
{
    anchor = ShapeAnchor::TopLeft;
    x = y = width = height = 0;
    cornerRadiusX = cornerRadiusY = 0;
    rotation = 0;
    fill = false;
    stroke = true;
    fillColor = strokeColor = Qt::black;
    strokeWidth = 1;
}
