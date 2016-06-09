#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>
#include "crain.h"
#include <mainwindow.h>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QSpinBox>
#include "mylogger.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class View;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(View *v) : QGraphicsView(), m_view(v) { }

protected:
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;
#endif

private:
    View *m_view;

};


class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(const QString &name, QWidget *parent, tipoPasto TIPOPASTO);
    ~View();
    QGraphicsView *view() const;
    void populateScene(int squareMeters, int amountAnimals);
    void getSides(int sqMeters, int &w, int &n, int &r);

    int getIntervalForStep(){return m_intervalForStep;}
    void setIntervalForStep(int step){m_intervalForStep = step;}
    int getIntervalForRain(){return m_intervalForRain;}
    void setIntervalForRain(int rainInterval){m_intervalForRain = rainInterval;}
    int getSpeed(){return m_speed;}
    void setSpeed(int speed){m_speed = speed;}
    void setTipoPasto(tipoPasto t){M_TIPOPASTO = t;}
    tipoPasto getTipoPasto(){return M_TIPOPASTO;}

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);
    void onTimer();
    void onRainTimer();

signals:
    void simulationFinished();

private slots:
    void resetView();

    void setResetButtonEnabled();
    void setupMatrix();
    void rotateLeft();
    void rotateRight();
    void onPauseButton();
    void onSpinChange();

private:
    GraphicsView *m_graphicsView;
    QLabel *m_labelTitle;
    QToolButton *resetButton;
    QSlider *m_zoomSlider;
    QSlider *rotateSlider;
    QGraphicsScene *m_scene;
    CRain *m_rain;
    QTimer *m_rainTimer;
    QTimer *m_advanceTimer;
    QLabel *m_labelRain;
    QPropertyAnimation *m_rainAnimation;
    QGraphicsOpacityEffect *m_fadeEffect;
    QLabel *m_labelStep;

    int m_stepCount;
    QToolButton *m_pauseButton;
    int m_intervalForStep;
    int m_intervalForRain;
    QSpinBox *m_spinSpeed;
    MyLogger *m_myLogger;
    int m_speed;
    tipoPasto M_TIPOPASTO;
};

#endif // VIEW_H
