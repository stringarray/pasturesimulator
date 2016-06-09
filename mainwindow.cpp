
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

        m_viewList.append( new View("Simulación pasto Carimagua", this, CARIMAGUA));
        m_viewList.at(0)->view()->setCacheMode(QGraphicsView::CacheBackground);
        m_viewList.at(0)->view()->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        m_viewList.at(0)->view()->setDragMode(QGraphicsView::ScrollHandDrag);
        m_viewList.at(0)->view()->setBackgroundBrush(QPixmap(":/images/andropogon_carimagua.png"));
        m_viewList.at(0)->setIntervalForStep(1000);
        m_viewList.at(0)->setIntervalForRain(m_rainInterval);
        m_viewList.at(0)->setSpeed(1);
        m_viewList.at(0)->populateScene(m_amountSquares, m_amountAnimals);


        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(m_viewList.at(0));
        setLayout(layout);

        setWindowTitle(tr("Simulación de campos de engorde"));

        connect(m_viewList.at(0), SIGNAL(simulationFinished()), this, SLOT(onSimulationFinished()));

        setMustClose(false);
        this->setWindowState(this->windowState() | Qt::WindowMaximized );
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
        m_viewList.append( new View("Simulación pasto Alemán", this, ALEMAN));
        m_viewList.at(1)->view()->setCacheMode(QGraphicsView::CacheBackground);
        m_viewList.at(1)->view()->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        m_viewList.at(1)->view()->setDragMode(QGraphicsView::ScrollHandDrag);
        m_viewList.at(1)->view()->setBackgroundBrush(QPixmap(":/images/echinochloa_aleman.png"));
        m_viewList.at(1)->setIntervalForStep(1000);
        m_viewList.at(1)->setIntervalForRain(m_rainInterval);
        m_viewList.at(1)->setSpeed(previousView->getSpeed());
        m_viewList.at(1)->populateScene(m_amountSquares, m_amountAnimals);


        this->layout()->addWidget(m_viewList.at(1));


        connect(m_viewList.at(1), SIGNAL(simulationFinished()), this, SLOT(onSimulationFinished()));
        m_isAleman = false;
    }
    else
    {
        qDebug() << "termino la dos";
        m_viewList.append( new View("Simulación pasto Guinea", this, GUINEA));
        m_viewList.at(2)->view()->setCacheMode(QGraphicsView::CacheBackground);
        m_viewList.at(2)->view()->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        m_viewList.at(2)->view()->setDragMode(QGraphicsView::ScrollHandDrag);
        m_viewList.at(2)->view()->setBackgroundBrush(QPixmap(":/images/panicum_guinea.png"));
        m_viewList.at(2)->setIntervalForStep(1000);
        m_viewList.at(2)->setIntervalForRain(m_rainInterval);
        m_viewList.at(2)->setSpeed(previousView->getSpeed());
        m_viewList.at(2)->populateScene(m_amountSquares, m_amountAnimals);


        this->layout()->addWidget(m_viewList.at(2));

        connect(m_viewList.at(2), SIGNAL(simulationFinished()), this, SLOT(onLastSimulationFinished()));

    }

}

void MainWindow::onLastSimulationFinished()
{
    DialogResults dialogResults(&m_viewList);

    dialogResults.setWindowState(dialogResults.windowState() | Qt::WindowMaximized);


    dialogResults.exec();
    setMustClose(true);
    this->close();
}
