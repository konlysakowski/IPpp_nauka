#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QString getSurname();
    QString getRank();
    int getAge();

public slots:
    void on_finished(int accepted);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
