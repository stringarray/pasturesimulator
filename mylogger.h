#ifndef MYLOGGER_H
#define MYLOGGER_H
#include <QVector>
#include "Animal.h"
#include "sqmeter.h"
#include <QObject>
#include <QFile>
#include "mainwindow.h"

class MyLogger : public QObject
{
    Q_OBJECT

public:
    explicit MyLogger(QObject *parent, tipoPasto TIPOPASTO);
    ~MyLogger();
    void addAnimal(Animal *animal);
    void addSquare(SqMeter *square);

signals:

public slots:
    void onTimer();
private:
    QVector<Animal*> m_animals;
    QVector<SqMeter*> m_squares;
    int m_currentDay;
    QFile m_fileAnimals;
};

#endif // MYLOGGER_H
