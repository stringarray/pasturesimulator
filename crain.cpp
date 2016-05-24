#include "crain.h"
#include <QDebug>

CRain::CRain(QObject *parent) : QObject(parent)
{

}



void CRain::onTimer()
{
    //qDebug() << "timer on rain";
    //TODO rango de milimetros de lluvia
    emit raining(4);
}
