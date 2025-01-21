#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Soldier{
    QString surname;
    QString rank;
    int age;

    bool operator<(Soldier& val){
        return this->age < val.age;
    }

    operator QString(){
        return this->rank + " " + this->surname + " " + QVariant(this->age).toString();
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_button_clicked();

    void on_find_youngest_button_clicked();

private:
    void update_table();

    std::vector<Soldier> soldiers;
    Dialog* dialog;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
