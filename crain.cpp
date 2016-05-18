#include "crain.h"
#include <QDebug>

CRain::CRain(QObject *parent) : QObject(parent)
{

}



void CRain::onTimer()
{
    //qDebug() << "timer on rain";
    //TODO: random mm de lluvia entre tal y tal valor
    emit raining(4);
}
