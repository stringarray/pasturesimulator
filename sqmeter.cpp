#include "sqmeter.h"
#include <QtWidgets>



SqMeter::SqMeter(const QColor &color, int x, int y)
{

    this->x = x;
    this->y = y;
    this->color = color;
    setZValue(0);

    setFlags( ItemIsSelectable );
    setAcceptHoverEvents(true);

    this->m_pesoPasto_0 = 50;
    this->m_nivelAgua = 300;
}

QRectF SqMeter::boundingRect() const
{
    return QRectF(0, 0, 50, 50);
}

QPainterPath SqMeter::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 50, 50);
    return path;
}

void SqMeter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    painter->setPen(QPen(Qt::black, 0));

    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);

    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    if (lod < 0.2) {
        if (lod < 0.125) {
            painter->fillRect(QRectF(0, 0, 50, 50), fillColor);
            return;
        }

        QBrush b = painter->brush();
        painter->setBrush(fillColor);
        painter->drawRect(0, 0, 50, 50);
        painter->setBrush(b);
        return;
    }

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
//    if (option->state & QStyle::State_Selected)
//        width += 2;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor));

    painter->drawRect(QRect(0, 0, 50, 50));
    painter->setBrush(b);

    if (lod >= 1) {
       // painter->setPen(QPen(Qt::gray, 1));
       // painter->drawLine(15, 54, 94, 54);
       // painter->drawLine(94, 53, 94, 15);
        //painter->setPen(QPen(Qt::black, 0));
    }

    // Draw text
    if (lod >= 2) {
        QFont font("Times", 20);
        font.setStyleStrategy(QFont::ForceOutline);
        painter->setFont(font);
        painter->save();
        painter->setPen(QColor(255,255,255));
        painter->scale(0.12, 0.12);
        painter->drawText(20, 60, QString("Hectárea en posición (%1, %2)").arg(x).arg(y));
        painter->drawText(20, 100, QString("Pasto: ") + QString::number(m_pesoPasto_0));
        painter->drawText(20, 140, QString("Agua: ") + QString::number(m_nivelAgua));
        painter->restore();
    }

}

void SqMeter::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void SqMeter::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

void SqMeter::onRain(int mm)
{
   // qDebug() << "llovio sobre el pasto en: (" << this->x << ", " << this->y << ")";
    //this->color = color.lighter(105);
    raiseWaterLevel(4);

    if(this->m_nivelAgua > HUMID_LEVEL)
        raiseGrassWeight_0(1);

    if(this->m_nivelAgua > FLOOD_LEVEL)
        lowerGrassWeight_0(1);



    this->color = getColor();

    update();
}

void SqMeter::consumeGrass()
{
  //  qDebug() << "pasto consumido en (" << this->x << ", " << this->y << ")";
    //this->color = color.darker(110);
    lowerGrassWeight_0(3);
    //this->m_nivelAgua+=2; ????

    this->color = getColor();

    update();
}

QColor SqMeter::getColor()
{

    if(m_nivelAgua > FLOOD_LEVEL)
    {
       // qDebug() << this->m_nivelAgua;
         return QColor(0,128,255);
    }
    else
    {
        float peso = m_pesoPasto_0;
        float green = (peso /100.0) * 255.0;
        float red =  ((peso /100.0) * 100.0);
        //qDebug() << "red " << red << " green " << green;

        if(green < 0) green = 0;
        if(red < 0) red = 0;
        if(green > 255) green = 255;
        if(red > 255) red = 255;

        if(green < 10){
            return QColor(red, green, 0);
        }else {
            return QColor(0, green, 0);
        }
    }
}

void SqMeter::advance(int step)
{
    if (!step)
        return;

    lowerWaterLevel(1);

    if(this->m_nivelAgua < HUMID_LEVEL) {
        lowerGrassWeight_0(1);
    }
    else if (this->m_nivelAgua > FLOOD_LEVEL) {
        lowerGrassWeight_0(1);
    }

    update();
}

void SqMeter::lowerGrassWeight_0(int times)
{
    for(int i = 0; i < times; i++)
    {
        if(m_pesoPasto_0 > 0){
            m_pesoPasto_0--;
        }
    }
}

void SqMeter::raiseGrassWeight_0(int times)
{
    for(int i = 0; i < times; i++)
    {
        if(m_pesoPasto_0 < 100){
            m_pesoPasto_0++;
        }
    }
}

void SqMeter::lowerWaterLevel(int times)
{
    for(int i = 0; i < times; i++)
    {
        if(m_nivelAgua > 0){
            m_nivelAgua--;
        }
    }
}

void SqMeter::raiseWaterLevel(int times)
{
    for(int i = 0; i < times; i++)
    {
        if(m_nivelAgua < 1000){
            m_nivelAgua++;
        }
    }
}
