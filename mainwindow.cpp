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

    QPlotWindow* plotwindow2= new QPlotWindow(this);
    CTimeSeriesSet<double> timeseriesset2(2);
    for (int j=0; j<2; j++)
    {   for (double t=44420; t<44600; t+=0.4)
        {
            timeseriesset2.BTC[j].append(t,cos(t/100)+j/3.0);
        }
        timeseriesset2.setname(j,("Value " + QString::number(j+10)).toStdString());
    }
    plotwindow2->PlotData(timeseriesset2,true);
    plotwindow->AddData(timeseriesset2.BTC[0],true);
    plotwindow->AddData(timeseriesset2.BTC[1],true);
    plotwindow2->show();
}

