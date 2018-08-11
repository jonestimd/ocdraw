#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include "shapedialog.h"
#include "rectangleform.h"
#include "rectanglemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

private slots:
    void on_actionRectangle_triggered();
    void on_addShape(QGraphicsItem* rect);
    void on_deleteShape(QGraphicsItem* shape);
    void on_shapeSelected(QGraphicsItem* shape, QPointF scenePos, ShapeAction action);
    void on_shapeUnselected();

private:
    Ui::MainWindow* ui;
    DiagramScene scene;
    ShapeDialog* toolDialog;
    RectangleForm* rectangleForm;
};

#endif // MAINWINDOW_H
