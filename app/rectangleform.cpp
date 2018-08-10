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
    connect(diagram, &DiagramScene::beginDraw, this, &RectangleForm::on_beginDraw);
    reset();
}

void RectangleForm::uninitialize()
{
    disconnect(diagram, &DiagramScene::beginDraw, this, &RectangleForm::on_beginDraw);
    if (rect != nullptr) rect->setSelected(false);
}

void RectangleForm::on_changeShape(QPointF delta, bool complete)
{
    if (edit != nullptr) {
        edit->adjust(delta);
        if (complete) {
            delete edit;
            edit = nullptr;
            validate(rect->rect().width(), rect->rect().height());
        }
    }
}

void RectangleForm::on_beginDraw(QPointF scenePos)
{
    reset();
    setText(ui->anchorX, scenePos.x());
    setText(ui->anchorY, scenePos.y());
    ShapeAnchor::Point anchor = ShapeAnchor::Point(ui->anchorButtons->checkedId());
    createRect(anchor, 0, 0);
    edit = new DrawRectangle(this, scenePos);
}

void RectangleForm::editShape(RoundedRect* shape, QPointF scenePos, ShapeAction action)
{
    if (this->rect != shape) {
        if (this->rect != nullptr) {
            this->rect->setSelected(false);
            unwatchEvents();
        }
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
    case ShapeAction::Move : edit = new MoveRectangle(this, scenePos); break;
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
        ShapeAnchor::Point anchor = ShapeAnchor::Point(ui->anchorButtons->checkedId());
        if (rect != nullptr) {
            rect->setRect(ShapeAnchor::getRect(anchor, width, height));
            emit shapeChanged(rect);
        }
        else createRect(anchor, width, height);
    }
    else if (rect != nullptr) {
        unwatchEvents();
        emit deleteShape(rect);
        rect = nullptr;
    }
    ui->deleteButton->setEnabled(rect != nullptr);
}

void RectangleForm::createRect(ShapeAnchor::Point anchor, qreal width, qreal height)
{
    rect = new RoundedRect(ShapeAnchor::getRect(anchor, width, height));
    rect->setPos(ui->anchorX->text().toDouble(), ui->anchorY->text().toDouble());
    rect->setRotation(ui->rotation->text().toDouble());
    rect->setCornerWidth(ui->radiusX->text().toDouble());
    rect->setCornerHeight(ui->radiusY->text().toDouble());
    rect->setAnchor(anchor);
    rect->setFlag(QGraphicsItem::ItemIsSelectable, true);
    rect->setSelected(true);
    on_name_textEdited(ui->name->text());
    if (ui->stroke->isChecked()) rect->setPen(QPen(QBrush(strokeColor), ui->strokeWidth->text().toDouble(), Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    else rect->setPen(QPen(Qt::transparent));
    rect->setBrush(QBrush(ui->fill->isChecked() ? fillColor : Qt::transparent));
    emit addShape(rect);
    watchEvents();
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
        if (rect->scene() != nullptr) rect->setSelected(false);
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

/* mouse move handler */

RectangleForm::MoveRectangle::MoveRectangle(RectangleForm* form, QPointF scenePos)
{
    this->form = form;
    this->lastPos = scenePos;
}

void RectangleForm::MoveRectangle::adjust(QPointF scenePos)
{
    QPointF delta = scenePos - lastPos;
    form->rect->moveBy(delta.x(), delta.y());
    setText(form->ui->anchorX, form->rect->x());
    setText(form->ui->anchorY, form->rect->y());
    lastPos = scenePos;
}

/* mouse resize handler */

RectangleForm::ResizeRectangle::ResizeRectangle(RectangleForm *form, QPointF scenePos)
{
    this->form = form;
    this->resizeHandle = ShapeAnchor::getAnchor(form->rect->rect(), form->rect->mapFromScene(scenePos));
}

void RectangleForm::ResizeRectangle::adjust(QPointF scenePos)
{
    resizeHandle = form->rect->moveTo(scenePos, resizeHandle);

    setText(form->ui->anchorX, form->rect->x());
    setText(form->ui->anchorY, form->rect->y());
    setText(form->ui->width, form->rect->rect().width());
    setText(form->ui->height, form->rect->rect().height());
    form->ui->anchorButtons->button(form->rect->anchor())->setChecked(true);
}

/* mouse draw handler */

RectangleForm::DrawRectangle::DrawRectangle(RectangleForm *form, QPointF scenePos)
{
    this->form = form;
    startPos = scenePos;
}

void RectangleForm::DrawRectangle::adjust(QPointF scenePos)
{
    using namespace ShapeAnchor;
    QPointF delta = scenePos - startPos;
    Point anchor = Point(form->ui->anchorButtons->checkedId());
    qreal width = std::abs(delta.x()), height = std::abs(delta.y());

    if (isCenter(anchor, Horizontal)) width *= 2;
    else anchor = setX(anchor, delta.x() > 0 ? LEFT : RIGHT);

    if (isCenter(anchor, Vertical)) height *= 2;
    else anchor = setY(anchor, delta.y() > 0 ? TOP : BOTTOM);

    form->rect->setAnchor(anchor);
    form->rect->setRect(getRect(anchor, width, height));

    setText(form->ui->anchorX, form->rect->x());
    setText(form->ui->anchorY, form->rect->y());
    setText(form->ui->width, form->rect->rect().width());
    setText(form->ui->height, form->rect->rect().height());
    form->ui->anchorButtons->button(anchor)->setChecked(true);
}
