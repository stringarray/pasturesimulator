
#include "mainwindow.h"

#include "view.h"
#include <QHBoxLayout>
#include <qdebug>

#include <QtWidgets>
#include "crain.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    View *view = new View(this, "Corriendo simulación:");
    //view->setMainWindow(this); // tratando de cerrar la aplicacion desde view.

    view->view()->setCacheMode(QGraphicsView::CacheBackground);
    view->view()->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->view()->setDragMode(QGraphicsView::ScrollHandDrag);

    view->view()->setBackgroundBrush(QPixmap(":/images/grass01.png"));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle(tr("Simulación de campo de engorde"));


}

MainWindow::~MainWindow()
{

}



