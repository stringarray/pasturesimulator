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

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}


Animal::Animal(int id)
    : angle(0), speed(0), AnimalEyeDirection(0),
      color(qrand() % 200, qrand() % 40, qrand() % 20)
{
    //setRotation(qrand() % (360 * 16));
    setZValue(1);
    //setFlags( ItemIsMovable );
    this->m_id = id;
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
    // Body
    painter->setBrush(color);
    painter->drawEllipse(-15, -20, 26, 40);
    painter->drawText(0, 5, QString::number(this->m_id));


}

void Animal::advance(int step)
{
    if (!step)
        return;

    QList<SqMeter *> metros;
    QList<QGraphicsItem *> surrounding = scene()->items(QPolygonF() << mapToScene(-50, 50)
                                                        << mapToScene(-50, -50)
                                                        << mapToScene(50, -50)
                                                        << mapToScene(50, 50));
    int i = 0;
    foreach (QGraphicsItem *item, surrounding) {
        if (item == this)
            continue;

       // qDebug() << "item: " << ++i << " x: " << item->pos().x() << " y: " << item->pos().y();

        SqMeter * meter = dynamic_cast<SqMeter*>(item);

        if (meter != NULL)
        {
            metros << meter;

        }
    }

    int nuevaPos = qrand() % metros.count();
 //   qDebug() << "mover a : " << nuevaPos << " total: " << metros.count();

    setPos(metros.at(nuevaPos)->pos().x()+25, metros.at(nuevaPos)->pos().y()+25 );

    metros.at(nuevaPos)->consumeGrass();

 //   qDebug() << "fin items.";

//scene()->addPolygon(QPolygonF() << mapToScene(-50, 50)
//                                << mapToScene(-50, -50)
//                                << mapToScene(50, -50)
//                                << mapToScene(50, 50), QPen(QColor(255,0,0)));
}


void Animal::onRain(int mm)
{
    //qDebug() << "slot on rain triggered on animal: " << m_id << "it rained: " << mm;
    //TODO: dibujar gotita celeste sobre el animal

}
