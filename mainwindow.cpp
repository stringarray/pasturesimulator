
#include "mainwindow.h"

#include "view.h"
#include <QHBoxLayout>
#include <qdebug>

#include <QtWidgets>
#include "crain.h"
#include "dialogstart.h"
#include "dialogresults.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    m_isAleman = true;
    DialogStart dialog;

    int result = dialog.exec();

    if(result == QDialog::Accepted)
    {

        m_amountAnimals = dialog.getAnimals();
        m_amountSquares = dialog.getSqMeters();
        m_rainInterval = dialog.getRainInterval() * 1000;

        View *view = new View("Simulación pasto Carimagua");
        view->view()->setCacheMode(QGraphicsView::CacheBackground);
        view->view()->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        view->view()->setDragMode(QGraphicsView::ScrollHandDrag);
        view->view()->setBackgroundBrush(QPixmap(":/images/grass01.png"));
        view->setIntervalForStep(1000);
        view->setIntervalForRain(m_rainInterval);
        view->setSpeed(1);
        view->populateScene(m_amountSquares, m_amountAnimals);


        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(view);
        setLayout(layout);

        setWindowTitle(tr("Simulación de campos de engorde"));

        connect(view, SIGNAL(simulationFinished()), this, SLOT(onSimulationFinished()));

        setMustClose(false);
        this->show();

    }
    else
    {

        setMustClose(true);
        this->close();

    }

}

void MainWindow::setMustClose(bool mustClose)
{
    this->m_mustClose = mustClose;
}

MainWindow::~MainWindow()
{

}

void MainWindow::onSimulationFinished()
{
    QObject* sender = this->sender();

    View* previousView = qobject_cast<View*>(sender);

    previousView->getSpeed();

    if(m_isAleman == true)
    {
        qDebug() << "termino la uno";
        View *view = new View("Simulación pasto Alemán");
        view->view()->setCacheMode(QGraphicsView::CacheBackground);
        view->view()->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        view->view()->setDragMode(QGraphicsView::ScrollHandDrag);
        view->view()->setBackgroundBrush(QPixmap(":/images/grass01.png"));
        view->setIntervalForStep(1000);
        view->setIntervalForRain(m_rainInterval);
        view->setSpeed(previousView->getSpeed());
        view->populateScene(m_amountSquares, m_amountAnimals);


        this->layout()->addWidget(view);


        connect(view, SIGNAL(simulationFinished()), this, SLOT(onSimulationFinished()));
        m_isAleman = false;
    }
    else
    {
        qDebug() << "termino la dos";
        View *view = new View("Simulación pasto Guinea");
        view->view()->setCacheMode(QGraphicsView::CacheBackground);
        view->view()->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        view->view()->setDragMode(QGraphicsView::ScrollHandDrag);
        view->view()->setBackgroundBrush(QPixmap(":/images/grass01.png"));
        view->setIntervalForStep(1000);
        view->setIntervalForRain(m_rainInterval);
        view->setSpeed(previousView->getSpeed());
        view->populateScene(m_amountSquares, m_amountAnimals);


        this->layout()->addWidget(view);

        connect(view, SIGNAL(simulationFinished()), this, SLOT(onLastSimulationFinished()));

    }

}

void MainWindow::onLastSimulationFinished()
{
    DialogResults dialogResults;

    dialogResults.setWindowState(dialogResults.windowState() | Qt::WindowMaximized);
    dialogResults.exec();

}
