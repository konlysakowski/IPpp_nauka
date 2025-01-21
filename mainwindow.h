#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QLineEdit>
#include <QPixmap>
#include <QMessageBox>
#include "dialog.h"


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
    void on_obliczSrednia_pushButton_clicked();

    void on_dodajStudenta_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QListWidget* listaStudentów;
    QLabel* logoSzkoly;
    QPushButton* dodajStudenta;
    QPushButton* obliczSrednia;
    QLineEdit* sredniaMat;
    QLineEdit* sredniaBiol;

    Dialog* noweOkno;

   // bool porownajStudentow(QListWidgetItem *student1, QListWidgetItem *student2);

};
#endif // MAINWINDOW_H
