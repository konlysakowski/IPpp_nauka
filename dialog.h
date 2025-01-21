#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QString getImie();
    QString getNazwisko();
    int getOcenaMat();
    int getOcenaBiol();

private:
    Ui::Dialog *ui;

    QLineEdit *imie;
    QLineEdit *nazwisko;
    QSpinBox *ocenaMat;
    QSpinBox *ocenaBiol;
    QPushButton *OK;
    QPushButton *ANULUJ;
};

#endif // DIALOG_H
