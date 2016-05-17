#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>
#include "crain.h"


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
    explicit View(const QString &name, QWidget *parent = 0);
    QGraphicsView *view() const;
    void populateScene(int squareMeters);
    void getSides(int sqMeters, int &w, int &n, int &r);

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);
    void onTimer();
    void onStartSimButtonPressed();
    void onStartSimButtonReleased();

private slots:
    void resetView();
    void onStartSimButton();
    void setResetButtonEnabled();
    void setupMatrix();
    void setupTransform();
    void togglePointerMode();

    void rotateLeft();
    void rotateRight();

private:
    GraphicsView *m_graphicsView;
    QLabel *label;
    QLabel *label2;
    QToolButton *selectModeButton;
    QToolButton *dragModeButton;

    QToolButton *resetButton;
    QToolButton *startSimButton;
    QSlider *m_zoomSlider;
    QSlider *rotateSlider;
    QGraphicsScene *m_scene;

    CRain *m_rain;
    QTimer *m_rainTimer;
};

#endif // VIEW_H
