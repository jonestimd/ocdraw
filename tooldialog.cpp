#include "tooldialog.h"

ToolDialog::ToolDialog(QWidget *parent) :
    QDialog(parent)
{
    restorePosition = false;
    position = QPoint();
}

void ToolDialog::show() {
	QWidget* p = dynamic_cast<QWidget*>(parent());
    if (restorePosition) move(p->pos() + position);
    else move(p->geometry().topRight());
    restorePosition = true;
    QDialog::show();
}

void ToolDialog::closeEvent(QCloseEvent* event)
{
    position = pos() - dynamic_cast<QWidget*>(parent())->pos();
    QDialog::closeEvent(event);
}

void ToolDialog::keyPressEvent(QKeyEvent* event)
{
    if (event->matches(QKeySequence::Cancel)) {
	    position = pos() - dynamic_cast<QWidget*>(parent())->pos();
    }
    QDialog::keyPressEvent(event);
}
