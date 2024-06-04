#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qplotwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Plot, SIGNAL(clicked()),this, SLOT(on_Plot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Plot()
{
    QPlotWindow* plotwindow = new QPlotWindow(this);
    plotwindow->show();
}

