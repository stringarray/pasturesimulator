
#include "mainwindow.h"

#include "view.h"
#include <QHBoxLayout>
#include <qdebug>

//#include <math.h>

#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{



    View *view = new View("Start simulation:");
    //view->view()->setScene(m_scene);
    view->view()->setCacheMode(QGraphicsView::CacheBackground);
    view->view()->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->view()->setDragMode(QGraphicsView::ScrollHandDrag);

    view->view()->setBackgroundBrush(QPixmap(":/images/grass01.png"));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle(tr("Farm simulator"));

    timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), view, SLOT(onTimer()));
    timer->start(1000 / 33);

}




