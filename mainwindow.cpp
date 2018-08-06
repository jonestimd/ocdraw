#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rectangleform.h"
#include "diagramscene.h"
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene()
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setScene(&scene);

    toolDialog = nullptr;
    rectangleForm = nullptr;

    connect(&scene, &DiagramScene::selectShape, this, &MainWindow::on_selectShape);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRectangle_triggered()
{
    if (!toolDialog) {
        toolDialog = new ShapeDialog(this);
    }
    if (!rectangleForm) {
        rectangleForm = new RectangleForm(this, static_cast<DiagramScene*>(ui->graphicsView->scene()));
        connect(rectangleForm, &RectangleForm::addShape, this, &MainWindow::on_addShape);
        connect(rectangleForm, &RectangleForm::deleteShape, this, &MainWindow::on_deleteShape);
    }
    toolDialog->show(rectangleForm);
    toolDialog->raise();
    toolDialog->activateWindow();
}

void MainWindow::on_addShape(QGraphicsItem* rect)
{
    selected = rect;
    ui->graphicsView->scene()->addItem(rect);
}

void MainWindow::on_deleteShape(QGraphicsItem* shape)
{
    if (shape != nullptr) {
        scene.removeItem(shape);
        delete shape;
        if (selected == shape) selected = nullptr;
    }
}

void MainWindow::on_selectShape(QGraphicsItem* shape, QPointF scenePos, ShapeAction action)
{
    if (shape->type() == RoundedRect::Type) {
        if (!rectangleForm->isVisible()) on_actionRectangle_triggered();
        rectangleForm->editShape(qgraphicsitem_cast<RoundedRect*>(shape), scenePos, action);
    }
}
