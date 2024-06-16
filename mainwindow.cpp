#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qplotwindow.h"
#include "BTC.h"

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
    CTimeSeries<double> timeseries;
    for (double t=1; t<2; t+=0.4)
    {
        timeseries.append(t,sin(t/100));
    }
    plotwindow->PlotData(timeseries);
    plotwindow->show();
}

