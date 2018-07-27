#ifndef RECTANGLEMODEL_H
#define RECTANGLEMODEL_H

#include <QtCore>
#include <QColor>
#include "ocdglobals.h"

class RectangleModel
{

public:
    RectangleModel();

    OcDraw::Anchor anchor;
    qreal x, y, width, height;
    qreal cornerRadiusX, cornerRadiusY;
    qreal rotation;
    bool fill, stroke;
    QColor fillColor, strokeColor;
    qreal strokeWidth;
};

#endif // RECTANGLEMODEL_H
