#include "mylogger.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMetaEnum>

MyLogger::MyLogger(QObject *parent, tipoPasto TIPOPASTO) : QObject(parent)
{
    m_currentDay = 1;

    QString filename = QString::number(TIPOPASTO) + "_simulation.csv";;

    m_fileAnimals.setFileName(filename);
    if(m_fileAnimals.exists())
        m_fileAnimals.remove();

     m_fileAnimals.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Append);


}

MyLogger::~MyLogger()
{
    m_fileAnimals.close();
}

void MyLogger::addAnimal(Animal *animal)
{
    this->m_animals.append(animal);
}

void MyLogger::addSquare(SqMeter *square)
{
   this->m_squares.append(square);
}

void MyLogger::onTimer()
{
    QString logline;
    logline = QString::number(m_currentDay) + ", ";

    for(int i = 0; i < m_animals.size(); i++)
    {
        if(i == m_animals.size()-1)
        {
            logline = logline + QString::number(m_animals.at(i)->m_pesoAnimal);

        } else {

            logline = logline + QString::number(m_animals.at(i)->m_pesoAnimal) + ", ";
        }

    }


    QTextStream stream(&m_fileAnimals);
    stream << logline << endl;

    m_currentDay++;
}
