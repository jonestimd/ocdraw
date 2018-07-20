#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rectangledialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRectangle_triggered()
{
    if (!rectangleDialog) {
        rectangleDialog = new RectangleDialog(this);
        connect(rectangleDialog, &RectangleDialog::addShape, this, &MainWindow::on_addShape);
        connect(rectangleDialog, &RectangleDialog::deleteShape, this, &MainWindow::on_deleteShape);
        connect(rectangleDialog, &RectangleDialog::shapeChanged, this, &MainWindow::on_shapChanged);
    }
    rectangleDialog->show();
    rectangleDialog->raise();
    rectangleDialog->activateWindow();
}

void MainWindow::on_addShape(RectangleModel *const model)
{
    qDebug() << "add rect";
}

void MainWindow::on_deleteShape(RectangleModel *const model)
{
    qDebug() << "delete rect";
}

void MainWindow::on_shapChanged(RectangleModel *const model, OcDraw::ModelChange changeType)
{
    qDebug() << "update rect";
}
