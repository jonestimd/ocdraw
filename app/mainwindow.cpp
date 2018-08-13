#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rectangleform.h"
#include "diagramscene.h"
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(),
    toolDialog(this), rectangleForm(this, &scene), multiSelectForm(this, &scene)
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setScene(&scene);

    connect(&scene, &DiagramScene::shapeSelected, this, &MainWindow::on_shapeSelected);
    connect(&scene, &DiagramScene::shapeUnselected, this, &MainWindow::on_shapeUnselected);

    connect(&rectangleForm, &RectangleForm::addShape, this, &MainWindow::on_addShape);
    connect(&rectangleForm, &RectangleForm::deleteShape, this, &MainWindow::on_deleteShape);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRectangle_triggered()
{
    showToolDialog(&rectangleForm);
}

void MainWindow::showToolDialog(ShapeForm* form)
{
    toolDialog.show(form);
    toolDialog.raise();
    toolDialog.activateWindow();
}

void MainWindow::on_addShape(QGraphicsItem* shape)
{
    ui->graphicsView->scene()->addItem(shape);
}

void MainWindow::on_deleteShape(QGraphicsItem* shape)
{
    if (shape != nullptr) {
        scene.removeItem(shape);
        delete shape;
    }
}

void MainWindow::on_shapeSelected(QGraphicsItem* shape, QPointF scenePos, ShapeAction action)
{
    if (scene.selectedItems().length() == 1) {
        if (shape->type() == RoundedRect::Type) {
            if (!rectangleForm.isVisible()) on_actionRectangle_triggered();
            rectangleForm.editShape(qgraphicsitem_cast<RoundedRect*>(shape), scenePos, action);
        }
    }
    else showToolDialog(&multiSelectForm);
}

void MainWindow::on_shapeUnselected()
{
    if (scene.selectedItems().length() == 1) {
        QGraphicsItem* shape = scene.selectedItems()[0];
        if (shape->type() == RoundedRect::Type) {
            if (!rectangleForm.isVisible()) on_actionRectangle_triggered();
            rectangleForm.editShape(qgraphicsitem_cast<RoundedRect*>(shape));
        }
    }
    else if (scene.selectedItems().length() > 1) showToolDialog(&multiSelectForm);
    else if (toolDialog.isVisible()) toolDialog.hide();
}
