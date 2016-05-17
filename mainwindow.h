#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT
public:
     MainWindow(QWidget *parent = 0);
     int getSquareMeters(){return m_squareMeters;}
     void setSquareMeters(int meters){m_squareMeters = meters;}

public slots:

private:

     int m_squareMeters;
     QTimer *timer;

};

#endif // MAINWINDOW_H
