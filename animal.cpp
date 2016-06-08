/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "Animal.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <math.h>
#include <QGraphicsObject>
#include "sqmeter.h"




//m_speed = m_intervalForStep de View
Animal::Animal(int id, int speed)
    : m_speed(speed),
      color(155,90,0)
{
    //setRotation(qrand() % (360 * 16));
    setZValue(1);
    //setFlags( ItemIsMovable );
    this->m_id = id;

    this->m_pesoAnimal = 20;
}

Animal::~Animal()
{

}

QRectF Animal::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath Animal::shape() const
{
    QPainterPath path;
    path.addRect(-10, -40, 35, 40);
    return path;
}

void Animal::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // TODO: reemplazar por imagen de vaca
    painter->setBrush(color);
    painter->drawEllipse(-15, -20, 15, 20);
    //painter->drawTiledPixmap(QRect(-15, -20, 50, 34), QPixmap(":/images/cow.png"), QPoint(-15, -20));

    QFont font("Times", 16);
    font.setStyleStrategy(QFont::ForceOutline);
    font.setBold(true);
    painter->setFont(font);
    painter->save();
    painter->setPen(QColor(255,255,255));
    painter->scale(0.16, 0.16);

    // Body
    if(m_pesoAnimal > 0)
    {

        painter->drawText(-70, -80, "Id: " + QString::number(this->m_id));
        painter->drawText(-70, -30, QString::number(m_pesoAnimal) + "%");
    }
    else
    {
        this->color = QColor(255, 0, 0);
        painter->drawText(0, 5, QString::number(this->m_id) + " MUERTA");
    }
    painter->restore();
}

void Animal::advance(int step)
{
    if (!step)
        return;

    if(m_pesoAnimal == 0)
        return;

    QList<SqMeter *> metros;
    QList<QGraphicsItem *> surrounding = scene()->items(QPolygonF() << mapToScene(-50, 50)
                                                        << mapToScene(-50, -50)
                                                        << mapToScene(50, -50)
                                                        << mapToScene(50, 50));
    int i = 0;
    foreach (QGraphicsItem *item, surrounding)
    {
        if (item == this)
            continue;
       // qDebug() << "item: " << ++i << " x: " << item->pos().x() << " y: " << item->pos().y();
        SqMeter * meter = dynamic_cast<SqMeter*>(item);
        if (meter != NULL)
        {
            metros << meter;
        }
    }

    //TODO: en vez de moverse randomicamente, que vaya hacia donde mas pasto hay?
    // o que solo se mueva si el pasto del cuadrado actual se termino?
    int nuevaPos = qrand() % metros.count();
    //qDebug() << "mover a : " << nuevaPos << " total: " << metros.count();



    if(metros.at(nuevaPos)->getNivelAgua() > FLOOD_LEVEL)
    {
       lowerWeight(2);

    }


    if(metros.at(nuevaPos)->getPesoPasto_0() > 5)
    {
        metros.at(nuevaPos)->consumeGrass();
        m_pesoAnimal++;

    } else {

        lowerWeight(1);
    }

    if(m_pesoAnimal > 0)
        moveAnimal(metros.at(nuevaPos)->pos().x()+25, metros.at(nuevaPos)->pos().y()+25 );

 //   qDebug() << "fin items.";

//scene()->addPolygon(QPolygonF() << mapToScene(-50, 50)
//                                << mapToScene(-50, -50)
//                                << mapToScene(50, -50)
//                                << mapToScene(50, 50), QPen(QColor(255,0,0)));
}


void Animal::onRain(int mm)
{
    //qDebug() << "slot on rain triggered on animal: " << m_id << "it rained: " << mm;
   lowerWeight(2);
}

void Animal::moveAnimal(int x, int y)
{

    QPoint startPosition;
    startPosition.setX(this->pos().x());
    startPosition.setY(this->pos().y());

//    qDebug() << "start x: " << startPosition.x() << " start y: " << startPosition.y();

    QPoint endPosition;
    endPosition.setX(x);
    endPosition.setY(y);

    m_animation = new QPropertyAnimation(this, "pos");
    m_animation->setStartValue(startPosition);
    m_animation->setEasingCurve(QEasingCurve::OutCubic);
    m_animation->setDuration(m_speed/3); // 1/3 seconds
    m_animation->setEndValue(endPosition);


//    qDebug() << "start animation x: " << x << "y: " << y;
    m_animation->start(QPropertyAnimation::DeleteWhenStopped);

    update();

}

void Animal::lowerWeight(int times)
{
    for(int i = 0; i < times; i++)
    {
        if(m_pesoAnimal > 0){
            m_pesoAnimal--;
        }
    }
}
