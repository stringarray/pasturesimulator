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
    ui->lineEditMetros->setValidator(new QIntValidator(100, 50000, this));
    ui->pushButton->setIconSize(QSize(70, 70));

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
    m_squareMeters = ui->lineEditMetros->text().toInt();
    m_animals = ui->lineEditAnimales->text().toInt();
    emit QDialog::accept();
}
