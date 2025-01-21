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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *table;
    QFormLayout *formLayout;
    QPushButton *add_button;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QPushButton *find_youngest_button;
    QLabel *youngest_soldier_label;
    QComboBox *youngest_rank_input;
    QLabel *label_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(100, 100));
        label->setPixmap(QPixmap(QString::fromUtf8(":/logo.png")));
        label->setScaledContents(true);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(18);
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        table = new QTableWidget(centralwidget);
        if (table->columnCount() < 3)
            table->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        table->setObjectName(QString::fromUtf8("table"));
        table->setSortingEnabled(true);
        table->horizontalHeader()->setVisible(true);
        table->horizontalHeader()->setCascadingSectionResizes(false);
        table->horizontalHeader()->setStretchLastSection(true);
        table->verticalHeader()->setVisible(true);
        table->verticalHeader()->setStretchLastSection(false);

        horizontalLayout_2->addWidget(table);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        add_button = new QPushButton(centralwidget);
        add_button->setObjectName(QString::fromUtf8("add_button"));
        add_button->setMinimumSize(QSize(300, 0));

        formLayout->setWidget(5, QFormLayout::SpanningRole, add_button);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(4, QFormLayout::LabelRole, verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(0, QFormLayout::LabelRole, verticalSpacer_2);

        find_youngest_button = new QPushButton(centralwidget);
        find_youngest_button->setObjectName(QString::fromUtf8("find_youngest_button"));

        formLayout->setWidget(2, QFormLayout::SpanningRole, find_youngest_button);

        youngest_soldier_label = new QLabel(centralwidget);
        youngest_soldier_label->setObjectName(QString::fromUtf8("youngest_soldier_label"));
        youngest_soldier_label->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(3, QFormLayout::SpanningRole, youngest_soldier_label);

        youngest_rank_input = new QComboBox(centralwidget);
        youngest_rank_input->addItem(QString());
        youngest_rank_input->addItem(QString());
        youngest_rank_input->addItem(QString());
        youngest_rank_input->setObjectName(QString::fromUtf8("youngest_rank_input"));

        formLayout->setWidget(1, QFormLayout::FieldRole, youngest_rank_input);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);


        horizontalLayout_2->addLayout(formLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Kompania wschodnioindyjska", nullptr));
        QTableWidgetItem *___qtablewidgetitem = table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "stopie\305\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "nazwisko", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "wiek", nullptr));
        add_button->setText(QCoreApplication::translate("MainWindow", "Dodaj \305\274o\305\202nierza", nullptr));
        find_youngest_button->setText(QCoreApplication::translate("MainWindow", "Znajd\305\272 najm\305\202odszego", nullptr));
        youngest_soldier_label->setText(QString());
        youngest_rank_input->setItemText(0, QCoreApplication::translate("MainWindow", "Kapral", nullptr));
        youngest_rank_input->setItemText(1, QCoreApplication::translate("MainWindow", "Szeregowy", nullptr));
        youngest_rank_input->setItemText(2, QCoreApplication::translate("MainWindow", "Genera\305\202", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "Ranga", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
