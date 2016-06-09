#include "dialogresults.h"
#include "ui_dialogresults.h"
#include <QDir>
#include <QDebug>
#include <QTableWidgetItem>

DialogResults::DialogResults(QList<View*> *viewList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogResults)
{
    ui->setupUi(this);
    QString url(QDir::currentPath() +  "/debug/pages/Factsheet-Andropogon-gayanus.htm"); //carimagua
    ui->link_carimagua->setText("<a href='" + url + "'>Fact sheet</a>");

    QString url2(QDir::currentPath() +  "/debug/pages/Factsheet-Echinochloa-polystachya.htm"); //aleman
    ui->link_echinochloa->setText("<a href='" + url2 + "'>Fact sheet</a>");

    QString url3(QDir::currentPath() +  "/debug/pages/Factsheet-Panicum-maximum.htm"); //guinea
    ui->link_panicum->setText("<a href='" + url3 + "'>Fact sheet</a>");

    QString url4(QDir::currentPath() +  "/0_simulation.csv");
    ui->link_csv0->setText("<a href='" + url4 + "'>CSV File</a>");
    QString url5(QDir::currentPath() +  "/1_simulation.csv");
    ui->link_csv1->setText("<a href='" + url5 + "'>CSV File</a>");
    QString url6(QDir::currentPath() +  "/2_simulation.csv");
    ui->link_csv2->setText("<a href='" + url6 + "'>CSV File</a>");

    this->m_viewList = *viewList;
    QList<QTableWidget *> tables;
    tables.append(ui->tableWidget0);
    tables.append(ui->tableWidget1);
    tables.append(ui->tableWidget2);

    QVector<QLabel *> labelsA;
    QVector<QLabel *> labelsV;
    labelsA.append(ui->pa0); //animal
    labelsV.append(ui->pv0); //vegetal
    labelsA.append(ui->pa1);
    labelsV.append(ui->pv1);
    labelsA.append(ui->pa2);
    labelsV.append(ui->pv2);

    int i = 0;
    foreach(View *v,  m_viewList)
    {

        QList<SqMeter *> metros;
        QList<Animal *> animals;
        QList<QGraphicsItem *> allItems  = v->view()->scene()->items();

        foreach (QGraphicsItem *item, allItems)
        {
            Animal * animal = dynamic_cast<Animal*>(item);
            if (animal != NULL)
                animals.append(animal);

            SqMeter * meter = dynamic_cast<SqMeter*>(item);
            if (meter != NULL)
                metros.append(meter);


        }

        int pesoVacasTotal = 0;
        tables.at(i)->setColumnCount(2);
        tables.at(i)->setHorizontalHeaderLabels(QStringList() << "Vaca nro." << "Peso");
        int j = 0;
        foreach (Animal *vaca, animals)
        {
            tables.at(i)->insertRow( j );

            QTableWidgetItem *item0 = new QTableWidgetItem("Vaca " + QString::number(j+1));
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(vaca->m_pesoAnimal));

            tables.at(i)->setItem( j, 0, item0 );
            tables.at(i)->setItem( j, 1, item1 );

            pesoVacasTotal += vaca->m_pesoAnimal;
            ++j;
        }

        int pesoPastoTotal = 0;
        foreach(SqMeter *m, metros)
        {
             pesoPastoTotal += m->getPesoPasto_0();

        }


        labelsA.at(i)->setText(QString::number(pesoVacasTotal));
        labelsV.at(i)->setText(QString::number(pesoPastoTotal));



        ++i;
    }

}

DialogResults::~DialogResults()
{
    delete ui;
}
