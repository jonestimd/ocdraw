#ifndef SHAPEDIALOG_H
#define SHAPEDIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include "shapeform.h"

/**
 * @brief The ShapeDialog class displays a form for editing the parameters of a shape.
 */
class ShapeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShapeDialog(QWidget* parent = nullptr);

    void show(ShapeForm* form);
    void hide();

protected:
    void closeEvent(QCloseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    bool restorePosition;
    QPoint position;
    QStackedLayout layout;
    ShapeForm* form;

    void onClose();
};

#endif // SHAPEDIALOG_H
