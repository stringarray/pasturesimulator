#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class View;
QT_END_NAMESPACE

enum tipoPasto {CARIMAGUA, ALEMAN, GUINEA};


class MainWindow : public QWidget
{
    Q_OBJECT

public:

     MainWindow(QWidget *parent = 0);
     ~MainWindow();

     int getSquareMeters(){return m_squareMeters;}
     void setSquareMeters(int meters){m_squareMeters = meters;}
     void setMustClose(bool mustClose);
     bool getMustClose(){return m_mustClose;}

public slots:
     void onSimulationFinished();
     void onLastSimulationFinished();

private:

     int m_squareMeters;
     bool m_mustClose;
     bool m_isAleman;
     int m_amountAnimals;
     int m_amountSquares;
     int m_rainInterval;
     int m_speed;
     QList<View*> m_viewList;

};

#endif // MAINWINDOW_H
