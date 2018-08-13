#include "shapedialog.h"
#include <QDebug>

ShapeDialog::ShapeDialog(QWidget* parent) :
    QDialog(parent),
    layout()
{
    restorePosition = false;
    position = QPoint();
    setLayout(&layout);
    form = nullptr;
}

void ShapeDialog::show(ShapeForm* form) {
    if (this->form != form && this->form != nullptr) this->form->uninitialize(false);
    this->form = form;

    if (! isVisible()) {
        QWidget* p = qobject_cast<QWidget*>(parent());
        if (restorePosition) move(p->pos() + position);
        else move(p->geometry().topRight());
        position = pos() - p->pos();
        restorePosition = true;
    }
    if (layout.currentWidget() != form) {
        int index = layout.indexOf(form);
        if (index < 0) index = layout.addWidget(form);
        layout.setCurrentIndex(index);
    }
    form->initialize();
    QDialog::show();
}

void ShapeDialog::hide()
{
    QDialog::hide();
    onClose();
}

void ShapeDialog::closeEvent(QCloseEvent* event)
{
    onClose();
    QDialog::closeEvent(event);
}

void ShapeDialog::keyPressEvent(QKeyEvent* event)
{
    if (event->matches(QKeySequence::Cancel)) {
        onClose();
    }
    QDialog::keyPressEvent(event);
}

void ShapeDialog::onClose()
{
    position = pos() - qobject_cast<QWidget*>(parent())->pos();
    form->uninitialize(true);
}
