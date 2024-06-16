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

#ifndef Qt6
        QDateTime start = QDateTime::fromTime_t(xtoTime(timeseries.GetT(0)), QTimeZone(0));
        QDateTime end = QDateTime::fromTime_t(xtoTime(timeseries.GetT(timeseries.n - 1)), QTimeZone(0));
#else
        QDateTime start = QDateTime::fromSecsSinceEpoch(xtoTime(BTC.GetT(0)));
        QDateTime end = QDateTime::fromSecsSinceEpoch(xtoTime(BTC.n - 1));
#endif

    QString xAxisTitle = "Time (day)";
    QString yAxisTitle = "Value";
    //QValueAxis* axisX = new QValueAxis();
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis* axisY = new QValueAxis();
    axisX->setObjectName("axisX");
    axisY->setObjectName("axisY");
    axisX->setTitleText(xAxisTitle);
    axisY->setTitleText(yAxisTitle);
    axisX->setRange(start ,end);
    axisY->setRange(y_min_val,y_max_val);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    QLineSeries *lineseries = new QLineSeries();
    chart->addSeries(lineseries);
    lineseries->attachAxis(axisX);
    lineseries->attachAxis(axisY);

    for (int j=0; j<timeseries.n; j++)
    {
        lineseries->append(QDateTime::fromTime_t(xtoTime(timeseries.GetT(j))).toMSecsSinceEpoch(),timeseries.GetC(j));
    }
    QPen pen = lineseries->pen();
    pen.setWidth(2);
    pen.setBrush(QColor(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)));
    lineseries->setPen(pen);
    lineseries->setName(QString::fromStdString("Value"));




    QString dformat;
    if (start.secsTo(end) < 600) {axisX->setFormat("mm:ss:zzz"); axisX->setTitleText("Time");}
    if (start.secsTo(end) > 3600) {axisX->setFormat("hh:mm:ss"); axisX->setTitleText("Time");}
    if (start.daysTo(end) > 1) {axisX->setFormat("MMM dd\nhh:mm:ss"); axisX->setTitleText("Date");}
    if (start.daysTo(end) > 5) {axisX->setFormat("MM.dd.yyyy\nhh:mm");axisX->setTitleText("Date");}
    if (start.daysTo(end) > 180) {axisX->setFormat("MM.dd.yyyy\nhAP");axisX->setTitleText("Date");}
    if (start.daysTo(end) > 2 * 365) {axisX->setFormat("MMMM\nyyyy");axisX->setTitleText("Date");}
    axisX->setLabelsAngle(-90);

    return true;
}
bool QPlotWindow::PlotData(const CTimeSeriesSet<outputtimeseriesprecision>& BTC, bool allowtime, string style)
{

}
bool QPlotWindow::AddData(const CTimeSeries<outputtimeseriesprecision>& BTC,bool allowtime, string style)
{

}
