#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_button_clicked()
{
    this->dialog = new Dialog;
    bool accepted = this->dialog->exec();

    if (accepted){
        this->soldiers.push_back({dialog->getSurname(),dialog->getRank(),dialog->getAge()});
        qDebug() << this->soldiers.back();

        this->update_table();
    }
}

void MainWindow::update_table(){

    this->ui->table->insertRow(0);
    auto temp = this->soldiers.back();

    this->ui->table->setItem(0, 0, new QTableWidgetItem(temp.rank));
    this->ui->table->setItem(0, 1, new QTableWidgetItem(temp.surname));
    this->ui->table->setItem(0, 2, new QTableWidgetItem(QVariant(temp.age).toString()));

    this->ui->table->sortItems(2, Qt::SortOrder::DescendingOrder);
}

void MainWindow::on_find_youngest_button_clicked()
{
    QString chosen_rank = this->ui->youngest_rank_input->currentText();

    Soldier* youngest = nullptr;

    for (auto &soldier : this->soldiers){
        if (soldier.rank == chosen_rank)
            if (youngest == nullptr || soldier < *youngest )
                youngest = &soldier;
    }

    if (youngest == nullptr)
        ui->youngest_soldier_label->setText("nie znaleziono");
    else
        ui->youngest_soldier_label->setText(*youngest);
}

