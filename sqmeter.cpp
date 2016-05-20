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

    this->m_pesoPasto = 50;
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
        painter->drawText(20, 100, QString("Pasto: ") + QString::number(m_pesoPasto));
       // painter->drawText(10, 220, QString("TODO: Mas características"));
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
    this->color = color.lighter(105);
    this->m_pesoPasto++;
    update();
}

void SqMeter::consumeGrass()
{
  //  qDebug() << "pasto consumido en (" << this->x << ", " << this->y << ")";
    this->color = color.darker(110);
    this->m_pesoPasto-=5;
    update();
}

void SqMeter::advance(int step)
{
    if (!step)
        return;
}

