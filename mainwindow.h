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
     ~MainWindow();

     int getSquareMeters(){return m_squareMeters;}
     void setSquareMeters(int meters){m_squareMeters = meters;}
     void setMustClose(bool mustClose);
     bool getMustClose(){return m_mustClose;}

public slots:

private:

     int m_squareMeters;
     bool m_mustClose;

};

#endif // MAINWINDOW_H
