#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rectangledialog.h"
#include <QGraphicsScene>
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setScene(new QGraphicsScene());
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
    QBrush fill = QBrush(model->fill ? model->fillColor : Qt::transparent);
    QPen stroke = QPen(model->stroke ? model->strokeColor : Qt::transparent);
    stroke.setWidthF(model->stroke ? model->strokeWidth : 0);

    selected = ui->graphicsView->scene()->addRect(0, 0, model->width, model->height, stroke, fill);
    selected->setPos(model->x, model->y);
//    selected->setFlag(QGraphicsItem::ItemIsSelectable, true);
    selected->setFlag(QGraphicsItem::ItemIsMovable, true);
}

void MainWindow::on_deleteShape()
{
    ui->graphicsView->scene()->removeItem(selected);
    selected = nullptr;
}

void MainWindow::on_shapChanged(RectangleModel *const model, OcDraw::ModelChange changeType)
{
    QGraphicsRectItem* rect = dynamic_cast<QGraphicsRectItem*>(selected);
    QPen stroke;
    switch (changeType) {
    case OcDraw::size:
        rect->setRect(0, 0, model->width, model->height);
        break;
    case OcDraw::position:
        rect->setPos(model->x, model->y);
        break;
    case OcDraw::rotation:
        rect->setRotation(model->rotation);
        break;
    case OcDraw::fill:
        rect->setBrush(QBrush(model->fill ? model->fillColor : Qt::transparent));
        break;
    case OcDraw::stroke:
	    stroke = QPen(model->stroke ? model->strokeColor : Qt::transparent);
	    stroke.setWidthF(model->stroke ? model->strokeWidth : 0);
	    rect->setPen(stroke);
        break;
    case OcDraw::anchor:
        break;
    case OcDraw::other:
        break;
    }
}
