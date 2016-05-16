#include "dialogstart.h"
#include "ui_dialogstart.h"
#include <QIntValidator>

DialogStart::DialogStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStart)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(100, 50000, this));
}

DialogStart::~DialogStart()
{
    delete ui;
}

void DialogStart::on_buttonBox_clicked(QAbstractButton *button)
{
    m_squareMeters = ui->lineEdit->text().toInt();
}
