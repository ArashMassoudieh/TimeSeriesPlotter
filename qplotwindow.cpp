#include "qplotwindow.h"
#include "ui_qplotwindow.h"
#include "chartview.h"



QPlotWindow::QPlotWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QPlotWindow)
{
    ui->setupUi(this);
    chart = new QPlotter();
    ChartView *chartview = new ChartView(chart);
    ui->verticalLayout->addWidget(chartview);

}

QPlotWindow::~QPlotWindow()
{
    delete ui;
}


bool QPlotWindow::PlotData(const CTimeSeries<outputtimeseriesprecision>& timeseries, bool allowtime, string style)
{
    double x_min_val = timeseries.mint();
    double x_max_val = timeseries.maxt();
    double y_min_val = timeseries.minC();
    double y_max_val = timeseries.maxC();
    QString xAxisTitle = "Time (day)";
    QString yAxisTitle = "Value";
    QValueAxis* axisX = new QValueAxis();
    QValueAxis* axisY = new QValueAxis();
    axisX->setObjectName("axisX");
    axisY->setObjectName("axisY");
    axisX->setTitleText(xAxisTitle);
    axisY->setTitleText(yAxisTitle);
    axisX->setRange(x_min_val,x_max_val);
    axisY->setRange(y_min_val,y_max_val);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    QLineSeries *lineseries = new QLineSeries();
    chart->addSeries(lineseries);
    lineseries->attachAxis(axisX);
    lineseries->attachAxis(axisY);

    for (int j=0; j<timeseries.n; j++)
    {
        lineseries->append(timeseries.GetT(j),timeseries.GetC(j));
    }
    QPen pen = lineseries->pen();
    pen.setWidth(2);
    pen.setBrush(QColor(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)));
    lineseries->setPen(pen);
    lineseries->setName(QString::fromStdString("Value"));
    return true;
}
bool QPlotWindow::PlotData(const CTimeSeriesSet<outputtimeseriesprecision>& BTC, bool allowtime, string style)
{

}
bool QPlotWindow::AddData(const CTimeSeries<outputtimeseriesprecision>& BTC,bool allowtime, string style)
{

}
