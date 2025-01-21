#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->dodajKlienta_pushButton, &QPushButton::clicked, this, &MainWindow::on_dodajKlienta_pushButton_clicked);
    connect(ui->wyliczSume_pushButton, &QPushButton::clicked, this, &MainWindow::on_wyliczSume_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dodajKlienta_pushButton_clicked()
{
    m_okno = new Dialog(nullptr);
    int result = m_okno->exec();

    if(result)
    {
        QString adres = m_okno->getAdres();
        QString nazwa = m_okno->getNazwa();
        double wartoscZam = m_okno->getWartoscZam();

        ui->klienci_listWidget->addItem(QString("Adres: %1 - Klient: %2 - Wartosc Zamowienia: %3").arg(adres).arg(nazwa).arg(wartoscZam));
    }

    delete m_okno;
}


void MainWindow::on_wyliczSume_pushButton_clicked()
{
    double suma = 0.0, liczbaKlientow = ui->klienci_listWidget->count();
    Dialog pomocnicza;

    if(liczbaKlientow == 0)
    {
        QMessageBox::information(this, "Brak klientów", "Nie znaleziono zadnego klienta");
    }

    for(int i = 0; i < liczbaKlientow; i++)
    {

    }

    ui->suma_lineEdit->setText(QString::number(suma, 'f', 2));
}
























