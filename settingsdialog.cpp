#include "settingsdialog.h"
#include "accounteditdialog.h"

#include <QDialog>
#include <QMaemo5ValueButton>
#include <QMaemo5ListPickSelector>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItem>
#include <QStandardItemModel>

settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("Accounts");
    setupDialog();
    fillAccounts();
    connect(newButton, SIGNAL(clicked()), this, SLOT(newButtonClicked()));
    connect(editButton, SIGNAL(clicked()), this, SLOT(editButtonClicked()));
}

settingsDialog::~settingsDialog()
{
}

void settingsDialog::setupDialog()
{
    accountButton = new QMaemo5ValueButton("Blog Accounts", this);
    accountButton->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    editButton = new QPushButton("Edit Account", this);
    newButton = new QPushButton("New Account", this);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(editButton);
    hlayout->addWidget(newButton);
    vlayout->addWidget(accountButton);
    vlayout->addLayout(hlayout);
    //this->setLayout(vlayout);
}

void settingsDialog::fillAccounts()
{
    list = new QStandardItemModel(this);
    for( int i = 0; i < 10; i++) {
        QStandardItem *item = new QStandardItem(QString::number(i));
        list->appendRow(item);
    }
    selector = new QMaemo5ListPickSelector;
    selector->setModel(list);
    selector->setCurrentIndex(0);
    accountButton->setPickSelector(selector);
}

void settingsDialog::newButtonClicked()
{
    accountEditDialog *aed = new accountEditDialog(this);
    aed->show();
}

void settingsDialog::editButtonClicked()
{
    accountEditDialog *aed = new accountEditDialog(this);
    aed->show();
}
