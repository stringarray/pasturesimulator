#include "view.h"

#include <QtWidgets>
#include <qmath.h>

#include "animal.h"
#include "sqmeter.h"
#include "crain.h"



#ifndef QT_NO_WHEELEVENT
void GraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->delta() > 0)
            m_view->zoomIn(6);
        else
            m_view->zoomOut(6);
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}
#endif

View::View(const QString &name, QWidget *parent)
    : QFrame(parent)
{

    m_scene = NULL;
    m_advanceTimer = NULL;
    m_rainTimer = NULL;

    setFrameStyle(Sunken | StyledPanel);
    m_graphicsView = new GraphicsView(this);
    m_graphicsView->setRenderHint(QPainter::Antialiasing, false);
    m_graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    m_graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    m_graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);


    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);

    QToolButton *zoomInIcon = new QToolButton;
    zoomInIcon->setAutoRepeat(true);
    zoomInIcon->setAutoRepeatInterval(33);
    zoomInIcon->setAutoRepeatDelay(0);
    zoomInIcon->setIcon(QPixmap(":/images/zoomin.png"));
    zoomInIcon->setIconSize(iconSize);
    QToolButton *zoomOutIcon = new QToolButton;
    zoomOutIcon->setAutoRepeat(true);
    zoomOutIcon->setAutoRepeatInterval(33);
    zoomOutIcon->setAutoRepeatDelay(0);
    zoomOutIcon->setIcon(QPixmap(":/images/zoomout.png"));
    zoomOutIcon->setIconSize(iconSize);
    m_zoomSlider = new QSlider;
    m_zoomSlider->setMinimum(0);
    m_zoomSlider->setMaximum(500);
    m_zoomSlider->setValue(250);
    m_zoomSlider->setTickPosition(QSlider::TicksRight);

    // Zoom slider layout
    QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
    zoomSliderLayout->addWidget(zoomInIcon);
    zoomSliderLayout->addWidget(m_zoomSlider);
    zoomSliderLayout->addWidget(zoomOutIcon);

    QToolButton *rotateLeftIcon = new QToolButton;
    rotateLeftIcon->setIcon(QPixmap(":/rotateleft.png"));
    rotateLeftIcon->setIconSize(iconSize);
    QToolButton *rotateRightIcon = new QToolButton;
    rotateRightIcon->setIcon(QPixmap(":/rotateright.png"));
    rotateRightIcon->setIconSize(iconSize);
    rotateSlider = new QSlider;
    rotateSlider->setOrientation(Qt::Horizontal);
    rotateSlider->setMinimum(0);
    rotateSlider->setMaximum(45);
    rotateSlider->setValue(0);
    rotateSlider->setTickPosition(QSlider::TicksBelow);

    // Rotate slider layout
    QHBoxLayout *rotateSliderLayout = new QHBoxLayout;
    rotateSliderLayout->addWidget(rotateLeftIcon);
    rotateSliderLayout->addWidget(rotateSlider);
    rotateSliderLayout->addWidget(rotateRightIcon);

    resetButton = new QToolButton;
    resetButton->setText(tr("0"));
    resetButton->setEnabled(false);

    // Label layout
    QHBoxLayout *labelLayout = new QHBoxLayout;
    m_labelTitle = new QLabel(name);

    labelLayout->addWidget(m_labelTitle);
    labelLayout->addStretch();

    m_labelRain = new QLabel("LLuvia");
    m_labelRain->setFont(QFont("Times", 20));
    m_labelRain->setVisible(false);
    labelLayout->addWidget(m_labelRain);
    labelLayout->addStretch();

    m_labelStep = new QLabel("Dia: 1");
    m_labelStep->setFont(QFont("Times", 20));
    labelLayout->addWidget(m_labelStep);
    labelLayout->addStretch();

    m_pauseButton = new QToolButton();
    m_pauseButton->setText("Pausar");
    labelLayout->addWidget(m_pauseButton);

    m_spinSpeed = new QSpinBox();
    m_spinSpeed->setMaximum(30);
    m_spinSpeed->setMinimum(1);
    m_spinSpeed->setValue(1);
    QLabel *speed = new QLabel("Velocidad: ");
    labelLayout->addWidget(speed);
    labelLayout->addWidget(m_spinSpeed);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(labelLayout, 0, 0);
    topLayout->addWidget(m_graphicsView, 1, 0);
    topLayout->addLayout(zoomSliderLayout, 1, 1);
    topLayout->addLayout(rotateSliderLayout, 2, 0);
    topLayout->addWidget(resetButton, 2, 1);
    setLayout(topLayout);

    m_graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    m_graphicsView->setInteractive(false);

    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetView()));
    connect(m_zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(rotateSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(m_graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));
    connect(m_graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));

    connect(zoomInIcon, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(zoomOutIcon, SIGNAL(clicked()), this, SLOT(zoomOut()));

    connect(m_pauseButton, SIGNAL(clicked(bool)), this, SLOT(onPauseButton()));
    connect(m_spinSpeed, SIGNAL(valueChanged(int)), this, SLOT(onSpinChange()));


    m_rain = new CRain(this);
    m_stepCount = 1;


    setupMatrix();




}

View::~View()
{
    if(m_scene != NULL){
        m_scene->clear();
        m_scene->deleteLater();
    }
    delete m_graphicsView;
    delete m_labelTitle;
    delete resetButton;
    delete m_zoomSlider;
    delete rotateSlider;

    delete m_rain;
    if(m_rainTimer != NULL) delete m_rainTimer;
    if(m_advanceTimer != NULL) delete m_advanceTimer;
    delete m_labelRain;
    delete m_labelStep;
    delete m_pauseButton;
    delete m_spinSpeed;
}

QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(m_graphicsView);
}

void View::resetView()
{
    m_zoomSlider->setValue(250);
    rotateSlider->setValue(0);
    setupMatrix();
    m_graphicsView->ensureVisible(QRectF(0, 0, 0, 0));

    resetButton->setEnabled(false);
}

void View::setResetButtonEnabled()
{
    resetButton->setEnabled(true);
}

void View::setupMatrix()
{
    qreal scale = qPow(qreal(2), (m_zoomSlider->value() - 250) / qreal(50));

    QMatrix matrix;
    QTransform transform;
    matrix.scale(scale, scale);

    transform.rotate(rotateSlider->value(), Qt::XAxis);
    m_graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    m_graphicsView->setTransform(transform);

    m_graphicsView->setMatrix(matrix, true);

    setResetButtonEnabled();
}

void View::zoomIn(int level)
{
    m_zoomSlider->setValue(m_zoomSlider->value() + level);
}

void View::zoomOut(int level)
{
    m_zoomSlider->setValue(m_zoomSlider->value() - level);
}

void View::rotateLeft()
{
    rotateSlider->setValue(rotateSlider->value() - 10);
}

void View::rotateRight()
{
    rotateSlider->setValue(rotateSlider->value() + 10);
}

void View::populateScene(int squareMeters, int amountAnimals)
{

    int westSide = 0;
    int northSide = 0;
    int resto = 0;

    getSides(squareMeters, westSide, northSide, resto);

    //qDebug() << westSide << "and: " << northSide << "resto: " << resto;

    m_scene = new QGraphicsScene;


    int xx=0;
    QColor color(0,255/2,0);
    for (int i = 0; i < westSide ;i++)
    {
        ++xx;
        int yy=0;
        for (int j = 0; j < northSide; j++)
        {
            ++yy;
            SqMeter *item = new SqMeter(color, xx, yy);
            item->setPos(QPointF(j*50, i*50));
            m_scene->addItem(item);
            m_myLogger.addSquare(item);
            connect(m_rain, SIGNAL(raining(int)), item, SLOT(onRain(int)));
        }

    }

    for (int k = 0; k < resto; k++)
    {
        SqMeter *item = new SqMeter(color, k, westSide+1);
        item->setPos(QPointF(k*50, westSide*50));
        m_scene->addItem(item);
        m_myLogger.addSquare(item);
        connect(m_rain, SIGNAL(raining(int)), item, SLOT(onRain(int)));
    }



    for (int a = 0; a < amountAnimals; ++a) {
        Animal *animal = new Animal(a, this->m_intervalForStep);
        animal->setPos(25,25);
        m_scene->addItem(animal);
        m_myLogger.addAnimal(animal);
        connect(m_rain, SIGNAL(raining(int)), animal, SLOT(onRain(int)));
    }


    m_advanceTimer = new QTimer;
    QObject::connect(m_advanceTimer, SIGNAL(timeout()), this, SLOT(onTimer()));
    QObject::connect(m_advanceTimer, SIGNAL(timeout()), &m_myLogger, SLOT(onTimer()));
    m_advanceTimer->start(m_intervalForStep);


    m_rainTimer = new QTimer;
    QObject::connect(m_rainTimer, SIGNAL(timeout()), m_rain, SLOT(onTimer()));
    QObject::connect(m_rainTimer, SIGNAL(timeout()), this, SLOT(onRainTimer()));
    m_rainTimer->start(m_intervalForRain);

    this->view()->setScene(m_scene);

    this->m_spinSpeed->setValue(getSpeed());
    emit m_spinSpeed->valueChanged(m_spinSpeed->value());


}

void View::onTimer()
{
    if(m_stepCount < 450)
    {
        if(m_scene)
        {
            emit m_scene->advance();
            m_stepCount++;
            this->m_labelStep->setText("Día: " + QString::number(m_stepCount));
        }
    } else { //ya pasaron los 15 meses
        this->m_labelTitle->setText("Simulación finalizada.");
        m_advanceTimer->stop();
        m_rainTimer->stop();
        //TODO: mostrar resultados
        //DialogResults dialogResults;
        //dialogResults.exec();
        this->setVisible(false);
        setSpeed(m_spinSpeed->value()); //so i can start next simulation at the same speed
        emit simulationFinished();

    }

}

void View::onRainTimer()
{
     m_labelRain->setVisible(true);
     m_fadeEffect = new QGraphicsOpacityEffect(m_labelRain);
     m_labelRain->setGraphicsEffect(m_fadeEffect);
     m_rainAnimation = new QPropertyAnimation(m_fadeEffect, "opacity");
     m_rainAnimation->setEasingCurve(QEasingCurve::InOutQuad);
     m_rainAnimation->setDuration(1000);
     m_rainAnimation->setStartValue(1.0);
     m_rainAnimation->setEndValue(0.01);
     m_rainAnimation->start(QPropertyAnimation::DeleteWhenStopped);
     update();

}

void View::getSides(int sqMeters, int &w, int &n, int &r)
{
    double D = std::sqrt(sqMeters);

    w = floor(D);
    n = ceil(D);

    if((w*n) > sqMeters)
        n--;

    r = sqMeters - w*n;

}

void View::onPauseButton()
{
    if(m_pauseButton->text() == "Pausar")
    {
        this->m_pauseButton->setText("Continuar");
        this->m_advanceTimer->stop();
        this->m_rainTimer->stop();
        this->m_spinSpeed->setEnabled(false);
    } else {
        this->m_pauseButton->setText("Pausar");
        this->m_spinSpeed->setEnabled(true);
        emit m_spinSpeed->valueChanged(m_spinSpeed->value());
    }

}

void View::onSpinChange()
{
    this->m_advanceTimer->stop();
    this->m_rainTimer->stop();

    int step = this->m_intervalForStep /this->m_spinSpeed->value();
    int rain = this->m_intervalForRain /this->m_spinSpeed->value();

    this->m_advanceTimer->start(step);
    this->m_rainTimer->start(rain);
}
