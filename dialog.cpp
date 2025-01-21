#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->OK_pushButton, &QPushButton::clicked, this, &Dialog::accept);
    connect(ui->Anuluj_pushButton, &QPushButton::clicked, this, &Dialog::reject);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getImie()
{
    return ui->dodajImie_lineEdit->text();
}

QString Dialog::getNazwisko()
{
    return ui->dodajNazwisko_lineEdit->text();
}

int Dialog::getOcenaMat()
{
    return ui->ocenaMat_spinBox->value();
}

int Dialog::getOcenaBiol()
{
    return ui->ocenaBiol_spinBox->value();
}
