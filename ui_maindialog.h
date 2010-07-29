/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created: Thu Jul 29 10:28:09 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_mainDialog
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *mainDialog)
    {
        if (mainDialog->objectName().isEmpty())
            mainDialog->setObjectName(QString::fromUtf8("mainDialog"));
        mainDialog->resize(640, 158);
        verticalLayout = new QVBoxLayout(mainDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(mainDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(mainDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 53, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(mainDialog);

        QMetaObject::connectSlotsByName(mainDialog);
    } // setupUi

    void retranslateUi(QDialog *mainDialog)
    {
        mainDialog->setWindowTitle(QApplication::translate("mainDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("mainDialog", "Accounts", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("mainDialog", "Blog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainDialog: public Ui_mainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
