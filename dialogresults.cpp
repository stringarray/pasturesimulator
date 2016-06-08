#include "dialogresults.h"
#include "ui_dialogresults.h"

DialogResults::DialogResults(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogResults)
{
    ui->setupUi(this);


}

DialogResults::~DialogResults()
{
    delete ui;
}
