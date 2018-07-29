#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rectangleform.h"
#include <QGraphicsScene>
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    eventProxy(),
    diagram()
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setScene(new QGraphicsScene());
    ui->graphicsView->scene()->addItem(&eventProxy);
    ui->graphicsView->scene()->addLine(-100, 0, 100, 0, QPen(Qt::red));
    ui->graphicsView->scene()->addLine(0, -100, 0, 100, QPen(Qt::red));
    ui->graphicsView->scene()->addItem(&diagram);

    toolDialog = nullptr;
    rectangleForm = nullptr;

    connect(&diagram, &GraphicsDiagram::selectShape, this, &MainWindow::on_selectShape);
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
        rectangleForm = new RectangleForm(this, &this->eventProxy);
        connect(rectangleForm, &RectangleForm::addShape, this, &MainWindow::on_addShape);
        connect(rectangleForm, &RectangleForm::shapeChanged, &diagram, &GraphicsDiagram::on_shapeChanged);
        connect(rectangleForm, &RectangleForm::deleteShape, this, &MainWindow::on_deleteShape);
    }
    toolDialog->show(rectangleForm);
    toolDialog->raise();
    toolDialog->activateWindow();
}

void MainWindow::on_addShape(QGraphicsItem* rect)
{
    selected = rect;
    diagram.addToGroup(rect);
    selected->setFlag(QGraphicsItem::ItemIsMovable, true);
}

void MainWindow::on_deleteShape(QGraphicsItem* shape)
{
    if (shape != nullptr) {
        ui->graphicsView->scene()->removeItem(shape);
        delete shape;
        if (selected == shape) selected = nullptr;
    }
}

void MainWindow::on_selectShape(QGraphicsItem* shape, QPointF /*scenePos*/)
{
    if (shape->type() == RoundedRect::Type) {
        if (!rectangleForm->isVisible()) on_actionRectangle_triggered();
        rectangleForm->editShape(qgraphicsitem_cast<RoundedRect*>(shape));
    }
}
