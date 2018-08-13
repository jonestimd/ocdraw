#ifndef MULTISELECTFORM_H
#define MULTISELECTFORM_H

#include "shapeform.h"
#include "shapeanchor.h"
#include "diagramscene.h"
#include <QWidget>

namespace Ui {
class MultiSelectForm;
}

class MultiSelectForm : public ShapeForm
{
    Q_OBJECT

public:
    explicit MultiSelectForm(QWidget *parent, DiagramScene* diagram);
    virtual ~MultiSelectForm() override;

    virtual void initialize() override;
    virtual void uninitialize(bool closing) override;

private slots:
    void on_relativePosition_toggled(bool checked);

    void on_fill_clicked();
    void on_fillColor_clicked();
    void on_stroke_clicked();
    void on_strokeColor_clicked();

    void on_applyButton_clicked();

private:
    Ui::MultiSelectForm *ui;
    DiagramScene* diagram;
    QColor fillColor;
    QColor strokeColor;

    void reset();
    QRectF getSelectedBounds();
};

#endif // MULTISELECTFORM_H
