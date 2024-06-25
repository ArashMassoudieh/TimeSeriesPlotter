#include "chartview.h"
#include <QtGui/QMouseEvent>
#include "mainwindow.h"


ChartView::ChartView(QChart *chart, MainWindow *_parent) :
    QChartView(chart, _parent),
    m_isTouching(false)
{
    parent = _parent;
    setRubberBand(QChartView::NoRubberBand);
}

bool ChartView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        m_isTouching = true;

        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    m_lastMousePos = event->pos();
    qDebug()<<event->type();
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        chart()->zoomReset();
        return;
    }
    if (m_isTouching)
        return;

    if (event->button() == Qt::MiddleButton)
    {
        m_lastMousePos = event->pos();
        event->accept();
    }



    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;

    if (event->buttons() == Qt::MiddleButton)
    {
        auto dPos = event->pos() - m_lastMousePos;
        chart()->scroll(-dPos.x(), dPos.y());

        m_lastMousePos = event->pos();
        event->accept();

    }

    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (double_clicked)
    {
        double_clicked = false;
        return;
    }

    if (m_isTouching)
        m_isTouching = false;

    chart()->setAnimationOptions(QChart::SeriesAnimations);

    if (event->button() == Qt::MouseButton::LeftButton)
    {
        QRect rect(QPoint(m_lastMousePos.x(),m_lastMousePos.y()), QPoint(event->pos().x(),event->pos().y()));
        chart()->zoomIn(rect);
    }
    else
    {
        QMenu *menu = new QMenu(this);
        if (chart()->series().count()==1)
        {
            menu->addAction("Copy curve");
        }
        else
            menu->addAction("Copy Curves");

        menu->addAction("Zoom Extends");
        QAction *selectedAction = menu->exec(mapToGlobal(event->pos()));
        if (selectedAction->text().contains("Copy"))
        {
            parent ->graphsClipboard.clear();
            for (int i = 0; i < chart()->series().count() ; i++)
            {
                QLineSeries *series = new QLineSeries(chart()->series()[i]);
                parent->graphsClipboard.insert(chart()->series()[i]->name(), series);
            }

        }

    }

}


void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    case Qt::Key_Space:
        chart()->zoomReset();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}

void ChartView::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton )
    {
        chart()->zoomReset();
        double_clicked = true;
    }

    QGraphicsView::mouseDoubleClickEvent( e );
}
