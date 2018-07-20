#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rectangledialog.h"
#include "rectanglemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionRectangle_triggered();
    void on_addShape(RectangleModel *const model);
    void on_deleteShape(RectangleModel *const model);
    void on_shapChanged(RectangleModel *const model, OcDraw::ModelChange changeType);

private:
    Ui::MainWindow *ui;
    RectangleDialog *rectangleDialog;
};

#endif // MAINWINDOW_H
