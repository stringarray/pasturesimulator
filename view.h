#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>
#include "crain.h"
#include <mainwindow.h>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

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
    explicit View(MainWindow *theMainWindow, const QString &name, QWidget *parent = 0);
    QGraphicsView *view() const;
    void populateScene(int squareMeters, int amountAnimals);
    void getSides(int sqMeters, int &w, int &n, int &r);
    //void setMainWindow(MainWindow *w){this->theMainWindow = w;}

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);
    void onTimer();
    void onRainTimer();

private slots:
    void resetView();

    void setResetButtonEnabled();
    void setupMatrix();
    void rotateLeft();
    void rotateRight();

private:
    GraphicsView *m_graphicsView;
    QLabel *label;
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
};

#endif // VIEW_H
