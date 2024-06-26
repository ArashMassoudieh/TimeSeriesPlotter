#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts>
#include <QtWidgets/QRubberBand>

QT_USE_NAMESPACE


class MainWindow;
class QPlotWindow;

class ChartView : public QChartView

{
public:
    ChartView(QChart *chart, QPlotWindow *plotWindow, MainWindow *parent);


protected:
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent( QMouseEvent * e );
    QPlotWindow* PlotWindow() {return plotWindow;}
private:
    bool m_isTouching;
    QPointF m_lastMousePos;
    bool double_clicked = false;
    MainWindow *parent;
    QPlotWindow *plotWindow;
};

#endif
