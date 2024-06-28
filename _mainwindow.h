#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QLineSeries>
#include "BTC.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QMap<QString, CTimeSeries<double>* > graphsClipboard;
    QString resource_directory;
private:
    Ui::MainWindow *ui;

public slots:
    void on_Plot();
};
#endif // MAINWINDOW_H
