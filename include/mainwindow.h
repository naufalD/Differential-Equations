#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include <QwtPlot>
#include <QwtPlotCurve>
#include <QElapsedTimer>

using namespace std;

class Plot : public QwtPlot
{
public:
    Plot(QWidget *parent = nullptr);
    void updateCurve(double x, double y);
private:
    QwtPlotCurve *m_curve;
    QPolygonF m_points;
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    virtual void timerEvent( QTimerEvent* ) QWT_OVERRIDE;
private:
    Plot *m_plot;
    Plot *m_plotKE;
    QElapsedTimer m_timer;
    vector<double> m_y;
    int m_timerID;
    int pause;
};
#endif // MAINWINDOW_H
