/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_2;
    QPushButton *dodajKlienta_pushButton;
    QListWidget *klienci_listWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *suma_lineEdit;
    QPushButton *wyliczSume_pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 672);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(760, 10, 211, 171));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/obrazy/logo.png")));
        label_2->setScaledContents(true);
        dodajKlienta_pushButton = new QPushButton(centralwidget);
        dodajKlienta_pushButton->setObjectName(QString::fromUtf8("dodajKlienta_pushButton"));
        dodajKlienta_pushButton->setGeometry(QRect(500, 380, 481, 91));
        klienci_listWidget = new QListWidget(centralwidget);
        klienci_listWidget->setObjectName(QString::fromUtf8("klienci_listWidget"));
        klienci_listWidget->setGeometry(QRect(20, 10, 461, 591));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(500, 490, 481, 81));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        suma_lineEdit = new QLineEdit(widget);
        suma_lineEdit->setObjectName(QString::fromUtf8("suma_lineEdit"));

        verticalLayout->addWidget(suma_lineEdit);

        wyliczSume_pushButton = new QPushButton(widget);
        wyliczSume_pushButton->setObjectName(QString::fromUtf8("wyliczSume_pushButton"));

        verticalLayout->addWidget(wyliczSume_pushButton);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QString());
        dodajKlienta_pushButton->setText(QCoreApplication::translate("MainWindow", "Wprowad\305\272 klienta", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Suma zam\303\263wie\305\204 wszystkich klient\303\263w: ", nullptr));
        wyliczSume_pushButton->setText(QCoreApplication::translate("MainWindow", "Wylicz sum\304\231", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
