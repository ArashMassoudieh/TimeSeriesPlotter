#include "qplotwindow.h"
#include "ui_qplotwindow.h"
#include "chartview.h"



QPlotWindow::QPlotWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QPlotWindow)
{
    ui->setupUi(this);
    ChartView *chartview = new ChartView(new QChart());
    ui->verticalLayout->addWidget(chartview);

}

QPlotWindow::~QPlotWindow()
{
    delete ui;
}
