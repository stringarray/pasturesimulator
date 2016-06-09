#include "dialogresults.h"
#include "ui_dialogresults.h"
#include <QDir>
#include <QDebug>

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

    this->m_viewList = *viewList;

    foreach(View *v,  m_viewList)
    {
        qDebug() << v->getTipoPasto();

    }

}

DialogResults::~DialogResults()
{
    delete ui;
}
