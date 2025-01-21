/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *rank_input;
    QSpinBox *age_input;
    QLineEdit *surname_input;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(280, 160);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        rank_input = new QComboBox(Dialog);
        rank_input->addItem(QString());
        rank_input->addItem(QString());
        rank_input->addItem(QString());
        rank_input->setObjectName(QString::fromUtf8("rank_input"));

        formLayout->setWidget(0, QFormLayout::FieldRole, rank_input);

        age_input = new QSpinBox(Dialog);
        age_input->setObjectName(QString::fromUtf8("age_input"));
        age_input->setMinimum(1);
        age_input->setMaximum(140);

        formLayout->setWidget(1, QFormLayout::FieldRole, age_input);

        surname_input = new QLineEdit(Dialog);
        surname_input->setObjectName(QString::fromUtf8("surname_input"));

        formLayout->setWidget(2, QFormLayout::FieldRole, surname_input);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Stopie\305\204", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Wiek", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "Nazwisko", nullptr));
        rank_input->setItemText(0, QCoreApplication::translate("Dialog", "Kapral", nullptr));
        rank_input->setItemText(1, QCoreApplication::translate("Dialog", "Szeregowy", nullptr));
        rank_input->setItemText(2, QCoreApplication::translate("Dialog", "Genera\305\202", nullptr));

    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
