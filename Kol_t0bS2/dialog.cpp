#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


QString Dialog::getNazwa()
{
    return this->ui->nazwaKlienta_lineEdit->text();
}

QString Dialog::getAdres()
{
    return this->ui->adresKlienta_lineEdit->text();
}

double Dialog::getWartoscZam()
{
    return this->ui->wartoscZamowienia_lineEdit->text().toDouble() * getRabat();
}

double Dialog::getRabat()
{
    double mnoznik = this->ui->rabat_spinBox->value();
    return  1 - mnoznik * 0.01;
}
