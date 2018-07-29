#ifndef RECTANGLEMODEL_H
#define RECTANGLEMODEL_H

#include <QtCore>
#include <QColor>
#include "shapeanchor.h"

class RectangleModel
{

public:
    RectangleModel();

    ShapeAnchor::Point anchor;
    qreal x, y, width, height;
    qreal cornerRadiusX, cornerRadiusY;
    qreal rotation;
    bool fill, stroke;
    QColor fillColor, strokeColor;
    qreal strokeWidth;
};

#endif // RECTANGLEMODEL_H
