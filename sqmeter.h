#ifndef SQMETER_H
#define SQMETER_H

#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsObject>

class SqMeter : public QGraphicsObject

//class SqMeter :  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    SqMeter(const QColor &color, int x, int y);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;
    void consumeGrass();
    int getX(){return x;}
    int getY(){return y;}
    void lowerGrassWeight(int times);
    void raiseGrassWeight(int times);
    void lowerWaterLevel(int times);
    void raiseWaterLevel(int times);

/* Pasto guinea (Panicum máximum) Ofrece 13 Ton de F.S/Ha/año con N 35 Ton de F.S/Ha/año
*  Pasto carimagua (Andropogon gayanus) Ofrece 17 Ton F.S/Ha/año con N 17
*  Pasto alemán (Echinochloa polystachya) 9 Ton de F.S/Ha/año. con N 22 Ton de F.S/Ha/año

*/
    enum tipoPasto { GUINEA, CARIMAGUA, ALEMAN };


    int m_pesoPasto;
    int m_nivelAgua;

public slots:
    void onRain(int mm);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;
    QColor getColor();

private:
    int x;
    int y;
    QColor color;

};

#endif // SQMETER_H
