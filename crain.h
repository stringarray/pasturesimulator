#ifndef CRAIN_H
#define CRAIN_H

#include <QObject>

class CRain : public QObject
{
    Q_OBJECT
public:
    explicit CRain(QObject *parent = 0);

signals:
   void raining(int mm);
public slots:
    void onTimer();

};

#endif // CRAIN_H
