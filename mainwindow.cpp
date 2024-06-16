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
    CTimeSeriesSet<double> timeseriesset(3);
    for (int j=0; j<3; j++)
    {   for (double t=44420; t<44600; t+=0.4)
        {
            timeseriesset.BTC[j].append(t,sin(t/100)+j/3.0);
        }
        timeseriesset.setname(j,("Value " + QString::number(j+1)).toStdString());
    }
    plotwindow->PlotData(timeseriesset,true);
    plotwindow->show();
}

