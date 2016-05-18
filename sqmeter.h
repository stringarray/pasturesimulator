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

/* Pasto guinea (Panicum máximum) Ofrece 13 Ton de F.S/Ha/año con N de 35 Ton de F.S/Ha/año
* Pasto carimagua (Andropogon gayanus) Ofrece de 17 Ton F.S/Ha/año con N de 17
* Pasto alemán (Echinochloa polystachya) de 9 Ton de F.S/Ha/año. con N de 22 Ton de F.S/Ha/año

*/
    enum tipoPasto { guinea, carimagua, aleman };


    int m_pesoPasto;

public slots:
    void onRain(int mm);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;

private:
    int x;
    int y;
    QColor color;
    bool isRaining;
};

#endif // SQMETER_H
