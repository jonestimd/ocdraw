#include "rectangleform.h"
#include "ui_rectangleform.h"
#include <QDoubleValidator>
#include <QIcon>
#include <QPixmap>
#include <QColorDialog>

RectangleForm::RectangleForm(QWidget *parent, DiagramScene* diagram) :
    ShapeForm(parent),
    ui(new Ui::RectangleForm),
    nextId(1)
{
    this->diagram = diagram;
    ui->setupUi(this);
    ui->anchorX->setValidator(new QDoubleValidator());
    ui->anchorY->setValidator(new QDoubleValidator());
    ui->width->setValidator(new QDoubleValidator(0, HUGE_VAL, 6));
    ui->height->setValidator(new QDoubleValidator(0, HUGE_VAL, 6));
    ui->rotation->setValidator(new QDoubleValidator());
    ui->radiusX->setValidator(new QDoubleValidator(0, HUGE_VAL, 6));
    ui->radiusY->setValidator(new QDoubleValidator(0, HUGE_VAL, 6));
    ui->strokeWidth->setValidator(new QDoubleValidator(0, HUGE_VAL, 6));

    ShapeAnchor::setButtonIds(ui->anchorButtons);

    fillColor = Qt::black;
    strokeColor = Qt::black;
    setColorIcon(fillColor, ui->fillColor);
    setColorIcon(strokeColor, ui->strokeColor);

    rect = nullptr;
    ui->deleteButton->setEnabled(false);

    edit = nullptr;
}

RectangleForm::~RectangleForm()
{
    delete ui;
}

void RectangleForm::initialize()
{
    setWindowTitle("Rectangle");
    reset();
}

void RectangleForm::on_changeShape(QGraphicsItem *shape, QPointF delta, bool complete)
{
    if (shape == rect && edit != nullptr) {
        edit->adjust(delta);
        if (complete) {
            delete edit;
            edit = nullptr;
        }
    }
    else qDebug() << "wrong shape" << shape->type();
}

void RectangleForm::editShape(RoundedRect* shape, QPointF scenePos, ShapeAction action)
{
    if (this->rect != shape) {
        if (this->rect != nullptr) unwatchEvents();
        this->rect = shape;
        setText(ui->anchorX, rect->x());
        setText(ui->anchorY, rect->y());
        setText(ui->width, rect->rect().width());
        setText(ui->height, rect->rect().height());
        setText(ui->radiusX, rect->cornerWidth());
        setText(ui->radiusY, rect->cornerHeight());
        setText(ui->rotation, rect->rotation());
        QVariant name = rect->data(int(DataKey::Name));
        if (name.isValid()) ui->name->setText(qvariant_cast<QString>(name));
        else ui->name->clear();

        ui->fill->setChecked(rect->brush().color() != Qt::transparent);
        setColorIcon(rect->brush().color(), ui->fillColor);

        ui->stroke->setChecked(rect->pen().color() != Qt::transparent);
        setColorIcon(rect->pen().color(), ui->strokeColor);
        setText(ui->strokeWidth, rect->pen().widthF());

        ui->anchorButtons->button(rect->anchor())->setChecked(true);

        ui->deleteButton->setEnabled(true);
        watchEvents();
    }
    switch (action) {
    case ShapeAction::Move : edit = new MoveRectangle(this); break;
    case ShapeAction::Edit : edit = new ResizeRectangle(this, scenePos); break;
    }
}

void RectangleForm::on_anchorX_textEdited(const QString &arg1)
{
    if (rect != nullptr) {
        rect->setX(arg1.toDouble());
        emit shapeChanged(rect);
    }
}

void RectangleForm::on_anchorY_textEdited(const QString &arg1)
{
    if (rect != nullptr) {
        rect->setY(arg1.toDouble());
        emit shapeChanged(rect);
    }
}

void RectangleForm::on_width_textEdited(const QString &arg1)
{
    validate(arg1.toDouble(), ui->height->text().toDouble());
}

void RectangleForm::on_height_textEdited(const QString &arg1)
{
    validate(ui->width->text().toDouble(), arg1.toDouble());
}

void RectangleForm::validate(qreal width, qreal height)
{
    if (width > 0 && height > 0) {
        ShapeAnchor::Point anchor = static_cast<ShapeAnchor::Point>(ui->anchorButtons->checkedId());
        if (rect != nullptr) {
            rect->setRect(ShapeAnchor::getRect(anchor, width, height));
            emit shapeChanged(rect);
        }
        else {
            rect = new RoundedRect(ShapeAnchor::getRect(anchor, width, height));
            rect->setPos(ui->anchorX->text().toDouble(), ui->anchorY->text().toDouble());
            rect->setRotation(ui->rotation->text().toDouble());
            rect->setCornerWidth(ui->radiusX->text().toDouble());
            rect->setCornerHeight(ui->radiusY->text().toDouble());
            rect->setAnchor(anchor);
            on_name_textEdited(ui->name->text());
            if (ui->stroke->isChecked()) rect->setPen(QPen(QBrush(strokeColor), ui->strokeWidth->text().toDouble(), Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
            else rect->setPen(QPen(Qt::transparent));
            rect->setBrush(QBrush(ui->fill->isChecked() ? fillColor : Qt::transparent));
            emit addShape(rect);
            watchEvents();
        }
    }
    else if (rect != nullptr) {
        unwatchEvents();
        emit deleteShape(rect);
        rect = nullptr;
    }
    ui->deleteButton->setEnabled(rect != nullptr);
}

void RectangleForm::on_radiusX_textEdited(const QString &arg1)
{
    if (rect != nullptr) {
        rect->setCornerWidth(arg1.toDouble());
        emit shapeChanged(rect);
    }
}

void RectangleForm::on_radiusY_textEdited(const QString &arg1)
{
    if (rect != nullptr) {
        rect->setCornerHeight(arg1.toDouble());
        emit shapeChanged(rect);
    }
}

void RectangleForm::on_rotation_textEdited(const QString &arg1)
{
    if (rect != nullptr) {
        rect->setRotation(arg1.toDouble());
        emit shapeChanged(rect);
    }
}

void RectangleForm::on_name_textEdited(const QString &arg1)
{
    if (rect != nullptr) {
        if (arg1.length() > 0) rect->setData(int(DataKey::Name), arg1);
        else rect->setData(int(DataKey::Name), QVariant::Invalid);
    }
}

void RectangleForm::on_fillColor_clicked()
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

void RectangleForm::on_strokeColor_clicked()
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

void RectangleForm::on_fill_toggled(bool checked)
{
    if (rect != nullptr) {
        rect->setBrush(QBrush(checked ? fillColor : Qt::transparent));
        emit shapeChanged(rect);
    }
}

void RectangleForm::on_stroke_toggled(bool checked)
{
    if (rect != nullptr) {
        rect->pen().setColor(checked ? strokeColor : Qt::transparent);
        emit shapeChanged(rect);
    }
}

void RectangleForm::setColorIcon(const QColor color, QToolButton *button)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(color);
    button->setIcon(QIcon(pixmap));
}

void RectangleForm::on_strokeWidth_textEdited(const QString &arg1)
{
    if (rect != nullptr) {
        rect->setPen(QPen(QBrush(strokeColor), arg1.toDouble(), Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        emit shapeChanged(rect);
    }
}

void RectangleForm::on_anchorButtons_buttonToggled(int id, bool checked)
{
    if (checked && rect != nullptr) {
        ShapeAnchor::Point anchor = ShapeAnchor::Point(id);
        rect->setAnchor(anchor);
        emit shapeChanged(rect);
    }
}

void RectangleForm::watchEvents()
{
    connect(diagram, &DiagramScene::changeShape, this, &RectangleForm::on_changeShape);
}

void RectangleForm::unwatchEvents()
{
    disconnect(diagram, &DiagramScene::changeShape, this, &RectangleForm::on_changeShape);
}

void RectangleForm::reset()
{
    if (rect != nullptr) {
        unwatchEvents();
        rect = nullptr;
        nextId++;
    }
    ui->anchorX->clear();
    ui->anchorY->clear();
    ui->width->clear();
    ui->height->clear();
    ui->rotation->clear();
    ui->name->setText(QString("rect-%1").arg(nextId));
    ui->anchorX->setFocus();
    ui->deleteButton->setEnabled(false);
}

void RectangleForm::on_newButton_clicked()
{
    reset();
}

void RectangleForm::on_deleteButton_clicked()
{
    if (rect != nullptr) emit deleteShape(rect);
    reset();
}

/* mouse handlers */

RectangleForm::MoveRectangle::MoveRectangle(RectangleForm* form)
{
    this->form = form;
}

void RectangleForm::MoveRectangle::adjust(QPointF delta)
{
    form->rect->moveBy(delta.x(), delta.y());
    setText(form->ui->anchorX, form->rect->x());
    setText(form->ui->anchorY, form->rect->y());
}

RectangleForm::ResizeRectangle::ResizeRectangle(RectangleForm *form, QPointF scenePos) :
    endPos(scenePos)
{
    this->form = form;
    this->resizeHandle = ShapeAnchor::getAnchor(form->rect->rect(), form->rect->mapFromScene(scenePos));
}

void RectangleForm::ResizeRectangle::adjust(QPointF delta)
{
    endPos += delta;
    resizeHandle = form->rect->moveTo(endPos, resizeHandle);

    setText(form->ui->anchorX, form->rect->x());
    setText(form->ui->anchorY, form->rect->y());
    setText(form->ui->width, form->rect->rect().width());
    setText(form->ui->height, form->rect->rect().height());
    form->ui->anchorButtons->button(form->rect->anchor())->setChecked(true);
}
