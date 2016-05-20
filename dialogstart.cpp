#include "dialogstart.h"
#include "ui_dialogstart.h"
#include <QIntValidator>
#include <QPushButton>
#include <QLayout>

DialogStart::DialogStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStart)
{
    ui->setupUi(this);
//    ui->lineEditMetros->setValidator(new QIntValidator(100, 50000, this));
 //   ui->lineEditAnimales->setValidator((new QIntValidator(1, 500, this)));
    ui->pushButton->setIconSize(QSize(70, 70));

    ui->spinBoxAnimals->setMinimum(1);
    ui->spinBoxAnimals->setMaximum(1000);
    ui->spinBoxAnimals->setValue(10);

    ui->spinBoxSquares->setMinimum(25);
    ui->spinBoxSquares->setMaximum(50000);
    ui->spinBoxSquares->setValue(100);

}

DialogStart::~DialogStart()
{
    delete ui;
}

void DialogStart::on_pushButton_pressed()
{
    ui->pushButton->setIcon(QPixmap(":/images/btnPressed.png"));
}

void DialogStart::on_pushButton_released()
{
    ui->pushButton->setIcon(QPixmap(":/images/btnUnPressed.png"));
}

void DialogStart::on_pushButton_clicked()
{
    m_animals = ui->spinBoxAnimals->value();
    m_squareMeters = ui->spinBoxSquares->value();
    m_intervalForRains = ui->spinBoxRainInterval->value();
    emit QDialog::accept();
}


