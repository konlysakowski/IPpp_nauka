#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    connect(this, SIGNAL(finished(int)), this, SLOT(on_finished(int)) );
    ui->setupUi(this);
}

void Dialog::on_finished(int accepted){
    Q_UNUSED(accepted);
    deleteLater();
}

Dialog::~Dialog()
{
    qDebug() << "deleting dialog";
    delete ui;
}


QString Dialog::getSurname(){
    return this->ui->surname_input->text();
}

QString Dialog::getRank(){
    return this->ui->rank_input->currentText();
}

int Dialog::getAge(){
    return this->ui->age_input->value();
}
