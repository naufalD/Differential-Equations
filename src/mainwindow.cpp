#include "include/mainwindow.h"
#include "include/ODE.h"

#include <cmath>
#include <QLayout>
#include <QwtPlotGrid>

double m =1;
//

vector<double> theFunction(double t, vector<double> y){
    // From y"=(1/m)F(t,y,y')
    //
    return {y[1], -9*y[0]-2*y[1]+(5/t)*sin(10*pow(t,2))};
}

Plot::Plot(QWidget *parent) : QwtPlot(parent)
{
    setTitle( "Differential Equation" );
    setCanvasBackground( Qt::white );
    setMinimumSize(300,300);
    //setAxisScale( QwtAxis::YLeft, -1.1, 1.1 );
    setAxisScale( QwtAxis::XBottom, 0, 50.5 );

    QwtPlotGrid* grid = new QwtPlotGrid();
    grid->attach( this );

    m_curve = new QwtPlotCurve();
    m_curve->setPen(Qt::blue, 1);
    m_curve->setCurveAttribute(QwtPlotCurve::Fitted, true);
    m_curve->attach(this);
}

void Plot::updateCurve(double x, double y){
    m_points<<QPointF(x,y);
    m_curve->setSamples(m_points);
    replot();
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    pause = 0;
    m_y = {10,1}; //Initial {position, velocity}


    m_plot = new Plot();
    m_plot->updateCurve(0, m_y[0]);

    m_plotKE = new Plot();
    m_plotKE->setTitle("Total Energy");
    m_plotKE->updateCurve(0,0.5*m*pow(m_y[1],2));

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_plot);
    layout->addWidget(m_plotKE);

    m_timerID = startTimer(50);
    m_timer.start();

}

void MainWindow::timerEvent( QTimerEvent* ){
    if (pause==0){
        if (m_timer.elapsed()>5000){
            pause=1;
            m_timer.start();
        }
    }
    else{
        //m_y = odeRK2(m_timer.elapsed()*0.001, m_y, &theFunction);
        //m_y = odeEuler(m_timer.elapsed()*0.001, m_y, &theFunction);
        m_y = odeRK4(m_timer.elapsed()*0.001, m_y, &theFunction);

        m_plot->updateCurve(m_timer.elapsed()*0.001, m_y[1]);
        m_plotKE->updateCurve(m_timer.elapsed()*0.001,0.5*m*pow(m_y[1],2)+0.5*9*pow(m_y[0],2));

        if (m_timer.elapsed()*0.001>50){
            killTimer(m_timerID);
        }
    }
}
