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
    QValueAxis* axisX_normal = new QValueAxis();
    QDateTimeAxis *axisX_date = new QDateTimeAxis;

    axisX_normal->setTickCount(10);
    axisX_date->setTickCount(10);
    if (!allowtime)
    {   axisX_normal->setTitleText("X");
        chart->addAxis(axisX_normal, Qt::AlignBottom);
        axisX_normal->setObjectName("axisX");
        axisX_normal->setTitleText(xAxisTitle);
        axisX_normal->setRange(x_min_val ,x_max_val);
    }
    else
    {
        axisX_date->setTitleText("X");
        chart->addAxis(axisX_date, Qt::AlignBottom);
        axisX_date->setObjectName("axisX");
        axisX_date->setTitleText(xAxisTitle);
        axisX_date->setRange(start ,end);
    }

    QValueAxis* axisY = new QValueAxis();

    axisY->setObjectName("axisY");
    axisY->setTitleText(yAxisTitle);

    axisY->setRange(y_min_val,y_max_val);

    chart->addAxis(axisY, Qt::AlignLeft);

    QLineSeries *lineseries = new QLineSeries();
    chart->addSeries(lineseries);
    if (allowtime)
        lineseries->attachAxis(axisX_date);
    else
        lineseries->attachAxis(axisX_normal);
    lineseries->attachAxis(axisY);

    for (int j=0; j<timeseries.n; j++)
    {
        if (allowtime)
            lineseries->append(QDateTime::fromTime_t(xtoTime(timeseries.GetT(j))).toMSecsSinceEpoch(),timeseries.GetC(j));
        else
            lineseries->append(timeseries.GetT(j),timeseries.GetC(j));
    }
    QPen pen = lineseries->pen();
    pen.setWidth(2);
    pen.setBrush(QColor(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)));
    lineseries->setPen(pen);
    lineseries->setName(QString::fromStdString("Value"));




    if (allowtime)
    {   if (start.secsTo(end) < 600) {axisX_date->setFormat("mm:ss:zzz"); axisX_date->setTitleText("Time");}
        if (start.secsTo(end) > 3600) {axisX_date->setFormat("hh:mm:ss"); axisX_date->setTitleText("Time");}
        if (start.daysTo(end) > 1) {axisX_date->setFormat("MMM dd\nhh:mm:ss"); axisX_date->setTitleText("Date");}
        if (start.daysTo(end) > 5) {axisX_date->setFormat("MM.dd.yyyy\nhh:mm");axisX_date->setTitleText("Date");}
        if (start.daysTo(end) > 180) {axisX_date->setFormat("MM.dd.yyyy\nhAP");axisX_date->setTitleText("Date");}
        if (start.daysTo(end) > 2 * 365) {axisX_date->setFormat("MMMM\nyyyy");axisX_date->setTitleText("Date");}
        axisX_date->setLabelsAngle(-90);
    }
    else
        axisX_normal->setLabelsAngle(-90);
    return true;
}
bool QPlotWindow::PlotData(const CTimeSeriesSet<outputtimeseriesprecision>& timeseriesset, bool allowtime, string style)
{
    double x_min_val = timeseriesset.mintime();
    double x_max_val = timeseriesset.maxtime();
    double y_min_val = timeseriesset.minval();
    double y_max_val = timeseriesset.maxval();

#ifndef Qt6
        QDateTime start = QDateTime::fromTime_t(xtoTime(x_min_val), QTimeZone(0));
        QDateTime end = QDateTime::fromTime_t(xtoTime(x_max_val), QTimeZone(0));
#else
        QDateTime start = QDateTime::fromSecsSinceEpoch(xtoTime(x_min_val));
        QDateTime end = QDateTime::fromSecsSinceEpoch(xtoTime(x_max_val));
#endif

    QString xAxisTitle = "Time (day)";
    QString yAxisTitle = "Value";
    QValueAxis* axisX_normal = new QValueAxis();
    QDateTimeAxis *axisX_date = new QDateTimeAxis;

    axisX_normal->setTickCount(10);
    axisX_date->setTickCount(10);
    if (!allowtime)
    {   axisX_normal->setTitleText("X");
        chart->addAxis(axisX_normal, Qt::AlignBottom);
        axisX_normal->setObjectName("axisX");
        axisX_normal->setTitleText(xAxisTitle);
        axisX_normal->setRange(x_min_val ,x_max_val);
    }
    else
    {
        axisX_date->setTitleText("X");
        chart->addAxis(axisX_date, Qt::AlignBottom);
        axisX_date->setObjectName("axisX");
        axisX_date->setTitleText(xAxisTitle);
        axisX_date->setRange(start ,end);
    }

    QValueAxis* axisY = new QValueAxis();

    axisY->setObjectName("axisY");
    axisY->setTitleText(yAxisTitle);

    axisY->setRange(y_min_val,y_max_val);

    chart->addAxis(axisY, Qt::AlignLeft);

    for (int i=0; i<timeseriesset.nvars; i++)
    {   QLineSeries *lineseries = new QLineSeries();
        chart->addSeries(lineseries);
        if (allowtime)
            lineseries->attachAxis(axisX_date);
        else
            lineseries->attachAxis(axisX_normal);
        lineseries->attachAxis(axisY);

        for (int j=0; j<timeseriesset.BTC[i].n; j++)
        {
            if (allowtime)
                lineseries->append(QDateTime::fromTime_t(xtoTime(timeseriesset.BTC[i].GetT(j))).toMSecsSinceEpoch(),timeseriesset.BTC[i].GetC(j));
            else
                lineseries->append(timeseriesset.BTC[i].GetT(j),timeseriesset.BTC[i].GetC(j));
        }
        QPen pen = lineseries->pen();
        pen.setWidth(2);
        pen.setBrush(QColor(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)));
        lineseries->setPen(pen);
        lineseries->setName(QString::fromStdString(timeseriesset.names[i]));
    }



    if (allowtime)
    {   if (start.secsTo(end) < 600) {axisX_date->setFormat("mm:ss:zzz"); axisX_date->setTitleText("Time");}
        if (start.secsTo(end) > 3600) {axisX_date->setFormat("hh:mm:ss"); axisX_date->setTitleText("Time");}
        if (start.daysTo(end) > 1) {axisX_date->setFormat("MMM dd\nhh:mm:ss"); axisX_date->setTitleText("Date");}
        if (start.daysTo(end) > 5) {axisX_date->setFormat("MM.dd.yyyy\nhh:mm");axisX_date->setTitleText("Date");}
        if (start.daysTo(end) > 180) {axisX_date->setFormat("MM.dd.yyyy\nhAP");axisX_date->setTitleText("Date");}
        if (start.daysTo(end) > 2 * 365) {axisX_date->setFormat("MMMM\nyyyy");axisX_date->setTitleText("Date");}
        axisX_date->setLabelsAngle(-90);
    }
    else
        axisX_normal->setLabelsAngle(-90);
    return true;
}
bool QPlotWindow::AddData(const CTimeSeries<outputtimeseriesprecision>& BTC,bool allowtime, string style)
{

}
