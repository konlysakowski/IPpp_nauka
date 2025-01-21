#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pixmap(":/obrazy/logo.png");
    ui->logo_label->setPixmap(pixmap);
    ui->logo_label->setScaledContents(true);

    connect(ui->dodajStudenta_pushButton, &QPushButton::clicked, this, &MainWindow::on_dodajStudenta_pushButton_clicked);
    connect(ui->obliczSrednia_pushButton, &QPushButton::clicked, this, &MainWindow::on_obliczSrednia_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_obliczSrednia_pushButton_clicked()
{
    double sumaMat = 0, sumaBiol = 0, liczbaOcen = ui->studenci_listWidget->count();
    if(liczbaOcen == 0)
    {
        QMessageBox::information(this, "Brak ocen", "Brak uczniów na liście");
        return;
    }

    for(int i = 0; i < liczbaOcen; i++)
    {
        QStringList skladowe = ui->studenci_listWidget->item(i)->text().split("- Matematyka:")[1].split("| Biologia:");
        sumaMat += skladowe[0].trimmed().toInt();
        sumaBiol += skladowe[1].trimmed().toInt();
    }

    double sredniaMat = static_cast<double>(sumaMat / liczbaOcen);
    double sredniaBiol = static_cast<double>(sumaBiol / liczbaOcen);

    ui->sredniaMat_lineEdit->setText(QString::number(sredniaMat, 'f', 2));
    ui->sredniaBiol_lineEdit->setText(QString::number(sredniaBiol, 'f', 2));
}


void MainWindow::on_dodajStudenta_pushButton_clicked()
{
    noweOkno = new Dialog(nullptr);
    if(noweOkno->exec() == QDialog::Accepted)
    {
        QString imieNazwisko = noweOkno->getImie() + " " + noweOkno->getNazwisko();
        int ocenaMat = noweOkno->getOcenaMat();
        int ocenaBiol = noweOkno->getOcenaBiol();

        ui->studenci_listWidget->addItem(QString("%1 - Matematyka: %2 | Biologia: %3").arg(imieNazwisko).arg(ocenaMat).arg(ocenaBiol));

        QList<QListWidgetItem*> studenci;
        for (int i = 0; i < ui->studenci_listWidget->count(); i++)
            studenci.append(ui->studenci_listWidget->takeItem(0));

 //       ui->studenci_listWidget->sortItems(Qt::AscendingOrder);

       this->ui->studenci_listWidget->sortItems(Qt::SortOrder::AscendingOrder);


        for (auto student : studenci)
            ui->studenci_listWidget->addItem(student);
    }
    delete noweOkno;
}





























