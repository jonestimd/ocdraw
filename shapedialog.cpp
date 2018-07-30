#include "shapedialog.h"

ShapeDialog::ShapeDialog(QWidget* parent) :
    QDialog(parent),
    layout()
{
    restorePosition = false;
    position = QPoint();
    setLayout(&layout);
}

void ShapeDialog::show(ShapeForm* form) {
    QWidget* p = qobject_cast<QWidget*>(parent());
    if (restorePosition) move(p->pos() + position);
    else move(p->geometry().topRight());
    restorePosition = true;
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
}
