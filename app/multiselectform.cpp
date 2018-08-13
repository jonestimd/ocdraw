#include "multiselectform.h"
#include "ui_multiselectform.h"
#include "math.h"

MultiSelectForm::MultiSelectForm(QWidget *parent, DiagramScene* diagram) :
    ShapeForm(parent),
    ui(new Ui::MultiSelectForm)
{
    this->diagram = diagram;
    ui->setupUi(this);
    ui->posX->setValidator(new QDoubleValidator());
    ui->posY->setValidator(new QDoubleValidator());
    ui->rotation->setValidator(new QDoubleValidator());
    ui->strokeWidth->setValidator(new QDoubleValidator(0, HUGE_VAL, 6));

    ShapeAnchor::setButtonIds(ui->anchorButtons);

    fillColor = Qt::black;
    strokeColor = Qt::black;
    setColorIcon(fillColor, ui->fillColor);
    setColorIcon(strokeColor, ui->strokeColor);
}

MultiSelectForm::~MultiSelectForm()
{
    delete ui;
}

void MultiSelectForm::initialize()
{
    window()->setWindowTitle(tr("Modify Shapes", "dialog title"));
    reset();
}

void MultiSelectForm::uninitialize(bool closing)
{
    if (closing) diagram->clearSelection();
}

void MultiSelectForm::reset()
{
    on_relativePosition_toggled(ui->relativePosition->isChecked());
    ui->rotation->clear();
    ui->fill->setCheckState(Qt::PartiallyChecked);
    ui->fillColor->setDisabled(true);
    ui->stroke->setCheckState(Qt::PartiallyChecked);
    ui->strokeWidth->setDisabled(true);
    ui->strokeColor->setDisabled(true);
    ui->posX->setFocus();
}

void MultiSelectForm::on_relativePosition_toggled(bool checked)
{
    if (checked) {
        ui->posX->clear();
        ui->posY->clear();
    }
    else {
        QRectF bounds = getSelectedBounds();
        setText(ui->posX, bounds.x());
        setText(ui->posY, bounds.y());
    }
}

void MultiSelectForm::on_fill_clicked()
{
    bool checked = ui->fill->checkState() == Qt::Checked;
    ui->fillColor->setEnabled(checked);
}

void MultiSelectForm::on_stroke_clicked()
{
    bool checked = ui->stroke->checkState() == Qt::Checked;
    ui->strokeWidth->setEnabled(checked);
    ui->strokeColor->setEnabled(checked);
}

void MultiSelectForm::on_applyButton_clicked()
{
    bool setX, setY, setRotation;
    qreal x = ui->posX->text().toDouble(&setX);
    qreal y = ui->posY->text().toDouble(&setY);
    qreal rotation = ui->rotation->text().toDouble(&setRotation);

    QRectF bounds = getSelectedBounds();
    if (setRotation) {
        if (ui->rotationPoint->isChecked()) {
            const qreal angle = rotation*M_PI/180;
            const QPointF origin = ShapeAnchor::getPos(bounds, ui->anchorButtons->checkedId());
            for (QGraphicsItem* shape : diagram->selectedItems()) {
                shape->setRotation(shape->rotation() + rotation);
                qreal dx = shape->x() - origin.x();
                qreal dy = shape->y() - origin.y();
                qreal x2 = std::cos(angle)*dx - std::sin(angle)*dy;
                qreal y2 = std::sin(angle)*dx + std::cos(angle)*dy;
                shape->setX(origin.x() + x2);
                shape->setY(origin.y() + y2);
            }
        }
        else {
            for (QGraphicsItem* shape : diagram->selectedItems()) {
                shape->setRotation(shape->rotation()+rotation);
            }
        }
    }
    if (setX || setY) {
        if (ui->relativePosition->isChecked()) {
            for (QGraphicsItem* shape : diagram->selectedItems()) {
                if (setX) shape->setX(shape->x() + x);
                if (setY) shape->setY(shape->y() + y);
            }
        }
        else {
            for (QGraphicsItem* shape : diagram->selectedItems()) {
                if (setX) shape->setX(shape->x() + x - bounds.x());
                if (setY) shape->setY(shape->y() + y - bounds.y());
            }
        }
    }
    if (ui->fill->checkState() != Qt::PartiallyChecked) {
        for (QGraphicsItem* item : diagram->selectedItems()) {
            QAbstractGraphicsShapeItem* shape = qgraphicsitem_cast<QAbstractGraphicsShapeItem*>(item);
            if (shape != nullptr) {
                shape->setBrush(QBrush(ui->fill->isChecked() ? fillColor : Qt::transparent));
            }
        }
    }
    if (ui->stroke->checkState() != Qt::PartiallyChecked) {
        for (QGraphicsItem* item : diagram->selectedItems()) {
            QAbstractGraphicsShapeItem* shape = qgraphicsitem_cast<QAbstractGraphicsShapeItem*>(item);
            if (shape != nullptr) {
                if (ui->stroke->isChecked()) {
                    shape->setPen(QPen(QBrush(strokeColor), ui->strokeWidth->text().toDouble(), Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                }
                else {
                    shape->setPen(QPen(Qt::transparent));
                }
            }
        }
    }
    reset();
}

QRectF MultiSelectForm::getSelectedBounds()
{
    QRectF bounds;
    for (const QGraphicsItem* shape : diagram->selectedItems()) {
        bounds |= shape->mapRectToScene(shape->boundingRect());
    }
    return bounds;
}

void MultiSelectForm::on_fillColor_clicked()
{
    const QColor color = QColorDialog::getColor(fillColor, this, tr("Select Fill Color", "dialog title"), QColorDialog::ShowAlphaChannel | QColorDialog::DontUseNativeDialog);
    if (color.isValid()) {
        fillColor = color;
        setColorIcon(fillColor, ui->fillColor);
    }
}

void MultiSelectForm::on_strokeColor_clicked()
{
    const QColor color = QColorDialog::getColor(strokeColor, this, tr("Select Stroke Color", "dialog title"), QColorDialog::ShowAlphaChannel | QColorDialog::DontUseNativeDialog);
    if (color.isValid()) {
        strokeColor = color;
        setColorIcon(strokeColor, ui->strokeColor);
    }
}
