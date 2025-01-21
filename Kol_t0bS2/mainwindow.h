#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "dialog.h"
#include <vector>

class Klienci
{
public:
    QString m_nazwa;
    QString m_adres;
    double m_wartoscZamowienia;

    void setNazwa(QString nazwa) {m_nazwa = nazwa;}
    void setAdres(QString adres) {m_adres = adres;}
    void setWartoscZamowienia(double wartosc) {m_wartoscZamowienia = wartosc;}

};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dodajKlienta_pushButton_clicked();

    void on_wyliczSume_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Dialog* m_okno;



    std::vector<Klienci> klienci;

};
#endif // MAINWINDOW_H
