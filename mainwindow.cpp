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
        // TODO connect signals
    }
    rectangleDialog->show();
    rectangleDialog->raise();
    rectangleDialog->activateWindow();
}
