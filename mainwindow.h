#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include "rectangledialog.h"
#include "rectanglemodel.h"
#include "graphicsitemeventproxy.h"
#include "graphicsdiagram.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionRectangle_triggered();
    void on_addShape(QGraphicsItem* rect);
    void on_shapeChanged(QGraphicsItem *shape);
    void on_deleteShape();

private:
    Ui::MainWindow *ui;
    RectangleDialog *rectangleDialog;

    QGraphicsItem* selected;
    GraphicsItemEventProxy eventProxy;
    GraphicsDiagram diagram;
};

#endif // MAINWINDOW_H
