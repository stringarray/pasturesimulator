#include "view.h"

#include <QtWidgets>
#include <qmath.h>
#include "dialogstart.h"
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
    zoomInIcon->setIcon(QPixmap(":/zoomin.png"));
    zoomInIcon->setIconSize(iconSize);
    QToolButton *zoomOutIcon = new QToolButton;
    zoomOutIcon->setAutoRepeat(true);
    zoomOutIcon->setAutoRepeatInterval(33);
    zoomOutIcon->setAutoRepeatDelay(0);
    zoomOutIcon->setIcon(QPixmap(":/zoomout.png"));
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

    startSimButton = new QToolButton;
    startSimButton->setText("Start");
    startSimButton->setIcon(QPixmap(":/images/btnUnPressed.png"));
    startSimButton->setFixedSize(70,70);
    startSimButton->setIconSize(QSize(70, 70));


    // Label layout
    QHBoxLayout *labelLayout = new QHBoxLayout;
    label = new QLabel(name);
    label2 = new QLabel(tr("Pointer Mode"));
    selectModeButton = new QToolButton;
    selectModeButton->setText(tr("Select"));
    selectModeButton->setCheckable(true);
    selectModeButton->setChecked(true);
    dragModeButton = new QToolButton;
    dragModeButton->setText(tr("Drag"));
    dragModeButton->setCheckable(true);
    dragModeButton->setChecked(false);


    QButtonGroup *pointerModeGroup = new QButtonGroup;
    pointerModeGroup->setExclusive(true);
    pointerModeGroup->addButton(selectModeButton);
    pointerModeGroup->addButton(dragModeButton);

    labelLayout->addWidget(label);
    labelLayout->addWidget(startSimButton);
    labelLayout->addStretch();
    labelLayout->addWidget(label2);
    labelLayout->addWidget(selectModeButton);
    labelLayout->addWidget(dragModeButton);
    labelLayout->addStretch();


    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(labelLayout, 0, 0);
    topLayout->addWidget(m_graphicsView, 1, 0);
    topLayout->addLayout(zoomSliderLayout, 1, 1);
    topLayout->addLayout(rotateSliderLayout, 2, 0);
    topLayout->addWidget(resetButton, 2, 1);
    setLayout(topLayout);

    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetView()));
    connect(m_zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(rotateSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(m_graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));
    connect(m_graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));
    connect(selectModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
    connect(dragModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));


    connect(zoomInIcon, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(zoomOutIcon, SIGNAL(clicked()), this, SLOT(zoomOut()));
    connect(startSimButton, SIGNAL(clicked(bool)), this, SLOT(onStartSimButton()));
    connect(startSimButton, SIGNAL(pressed()), this, SLOT(onStartSimButtonPressed()));
    connect(startSimButton, SIGNAL(released()), this, SLOT(onStartSimButtonReleased()));

    m_rain = new CRain();



    setupMatrix();
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

void View::onStartSimButton()
{
    DialogStart dialog;
    int result = dialog.exec();

    if(result == QDialog::Accepted)
    {
        populateScene(dialog.getSqMeters());
        this->view()->setScene(m_scene);
        this->startSimButton->setDisabled(true);
    }

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

void View::setupTransform()
{
//    QTransform transform;
//    transform.rotate(rotateSlider->value(), Qt::XAxis);
//    this->view()->setTransform(transform);
}

void View::togglePointerMode()
{
    m_graphicsView->setDragMode(selectModeButton->isChecked()
                              ? QGraphicsView::RubberBandDrag
                              : QGraphicsView::ScrollHandDrag);
    m_graphicsView->setInteractive(selectModeButton->isChecked());
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

void View::populateScene(int squareMeters)
{

    int westSide = 0;
    int northSide = 0;
    int resto = 0;

    getSides(squareMeters, westSide, northSide, resto);

    //qDebug() << westSide << "and: " << northSide << "resto: " << resto;

    m_scene = new QGraphicsScene;


    int xx=0;
    QColor color(55,130,55);
    for (int i = 0; i < westSide ;i++)
    {
        ++xx;
        int yy=0;
        for (int j = 0; j < northSide; j++)
        {
            ++yy;
            QGraphicsItem *item = new SqMeter(color, xx, yy);
            item->setPos(QPointF(j*50, i*50));
            m_scene->addItem(item);
        }

    }

    for (int k = 0; k < resto; k++)
    {
        QGraphicsItem *item = new SqMeter(color, k, westSide+1);
        item->setPos(QPointF(k*50, westSide*50));
        m_scene->addItem(item);
    }



    for (int a = 0; a < 10; ++a) {
        Animal *animal = new Animal(a);
        animal->setPos(::sin((a * 6.28) / 10) * 200,
                      ::cos((a * 6.28) / 10) * 200);
        m_scene->addItem(animal);
        connect(m_rain, SIGNAL(raining()), animal, SLOT(onRain()));
    }
}

void View::onTimer()
{
    if(m_scene)
        emit m_scene->advance();

    emit m_rain->raining();
}

void View::onStartSimButtonPressed()
{
    this->startSimButton->setIcon(QPixmap(":/images/btnPressed.png"));
}

void View::onStartSimButtonReleased()
{
    this->startSimButton->setIcon(QPixmap(":/images/btnUnPressed.png"));
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
