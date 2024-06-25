#ifndef QPLOTWINDOW_H
#define QPLOTWINDOW_H

#include <QDialog>
#include <BTC.h>
#include <BTCSet.h>
#include <qplotter.h>

#define outputtimeseriesprecision double

class MainWindow;

struct plotformat{
    Qt::GlobalColor color = Qt::red;
    QBrush brush = QBrush(QColor(240, 255, 200));
    //QCPGraph *fillGraph = 0;
    //QCPGraph::LineStyle lineStyle = QCPGraph::lsLine;
    //QCPScatterStyle::ScatterShape scatterStyle = QCPScatterStyle::ssNone;// ssDisc;
    bool legend = true;
    Qt::PenStyle penStyle = Qt::DotLine;
    int penWidth = 2;
    //QCPAxis::ScaleType xAxisType = QCPAxis::stLinear;
    //QCPAxis::ScaleType yAxisType = QCPAxis::stLinear;
    QString xAxisLabel = "", yAxisLabel = "";
    bool xAxisTimeFormat = true;
    //QMap<QString, int> lineStyles = QMap<QString, int>{ { "Line", QCPGraph::lsLine }, { "None", QCPGraph::lsNone } };
    //QMap<QString, int> scatterStyles = QMap<QString, int>{ { "None", QCPScatterStyle::ssNone }, { "Cross", QCPScatterStyle::ssCross }, { "Cross Circle", QCPScatterStyle::ssCrossCircle }, { "Dot", QCPScatterStyle::ssDot } };
    //QMap<QString, int> axisTypes = QMap<QString, int>{ { "Normal", QCPAxis::ScaleType::stLinear }, { "Log", QCPAxis::ScaleType::stLogarithmic } };
    //QMap<QString, int> axisTimeFormats = QMap<QString, int>{ { "Number", 0 },{ "Time", 1 } };
    //QMap<QString, int> penStyles = QMap<QString, int>{ { "Solid Line", Qt::SolidLine }, { "Dot Line", Qt::DotLine }, { "Dash Line", Qt::DashLine }, { "Dash Dot Line", Qt::DashDotLine }, { "Dash Dot Dot Line", Qt::DashDotDotLine } };
    //QMap<QString, int> colors = QMap<QString, int> { { "Red", Qt::red }, { "Black", Qt::black }, { "Blue", Qt::blue }, { "Green", Qt::green }, { "Cyan", Qt::cyan }, { "Dark Green", Qt::darkGreen },
    //{ "Dark Red", Qt::darkRed }, { "Dark Blue", Qt::darkBlue }, { "Dark Gray", Qt::darkGray }, { "Magenta", Qt::magenta }, { "Light Gray", Qt::lightGray }, { "Yellow", Qt::yellow } };
    //QMap<QString, int> penWidths = QMap<QString, int>{ { "1", 1 }, { "2", 2 }, { "3", 3 }, { "4", 4 }, { "5", 5 } };
    //QMap<QString, int> legends = QMap<QString, int>{ { "Show", 1 }, { "Hide", 0 } };

};


struct _timeseries
{
    QString filename;
    QString name;
    CTimeSeriesSet<outputtimeseriesprecision> Data;
};


namespace Ui {
class QPlotWindow;
}

class QPlotWindow : public QDialog
{
    Q_OBJECT

public:
    explicit QPlotWindow(MainWindow *parent = nullptr);
    ~QPlotWindow();
    bool PlotData(const CTimeSeries<outputtimeseriesprecision>& BTC, bool allowtime=true, string style="line");
    bool PlotData(const CTimeSeriesSet<outputtimeseriesprecision>& BTC, bool allowtime=true, string style="line");
    bool AddData(const CTimeSeries<outputtimeseriesprecision>& BTC,bool allowtime=true, string style="line");
    void SetYAxisTitle(const QString& s);
    void SetXAxisTitle(const QString& s);
    void SetTimeFormat(bool timedate);
    void SetLegend(bool onoff);


private:
    Ui::QPlotWindow *ui;
    QPlotter* chart;
    double xtoTime(const double &x) {
        return x * 86400 - 2209161600;
    }
    double timetoX(const double &time) {
        return (time + 2209161600) / 86400;
    }

private slots:
     void contextMenuRequest(QPoint pos);

};

#endif // QPLOTWINDOW_H
