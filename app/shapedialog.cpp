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
    if (this->form != form && this->form != nullptr) this->form->uninitialize();
    this->form = form;

    if (! isVisible()) {
        QWidget* p = qobject_cast<QWidget*>(parent());
        if (restorePosition) move(p->pos() + position);
        else move(p->geometry().topRight());
        position = pos() - p->pos();
        restorePosition = true;
    }
    if (layout.currentWidget() != form) {
        if (layout.count() == 0) layout.addWidget(form);
        else layout.replaceWidget(layout.currentWidget(), form);
    }
    form->initialize();
    QDialog::show();
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
    form->uninitialize();
}
