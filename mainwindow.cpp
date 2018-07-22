#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rectangledialog.h"
#include <QGraphicsScene>
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    eventProxy()
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setScene(new QGraphicsScene());
    ui->graphicsView->scene()->addItem(&eventProxy);
    ui->graphicsView->scene()->addLine(-100, 0, 100, 0, QPen(Qt::red));
    ui->graphicsView->scene()->addLine(0, -100, 0, 100, QPen(Qt::red));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRectangle_triggered()
{
    if (!rectangleDialog) {
        rectangleDialog = new RectangleDialog(this, &this->eventProxy);
        connect(rectangleDialog, &RectangleDialog::addShape, this, &MainWindow::on_addShape);
        connect(rectangleDialog, &RectangleDialog::deleteShape, this, &MainWindow::on_deleteShape);
    }
    rectangleDialog->show();
    rectangleDialog->raise();
    rectangleDialog->activateWindow();
}

void MainWindow::on_addShape(QGraphicsRectItem *const rect)
{
    selected = rect;
    ui->graphicsView->scene()->addItem(rect);
//    selected->setFlag(QGraphicsItem::ItemIsSelectable, true);
    selected->setFlag(QGraphicsItem::ItemIsMovable, true);
}

void MainWindow::on_deleteShape()
{
    ui->graphicsView->scene()->removeItem(selected);
    selected = nullptr;
}
