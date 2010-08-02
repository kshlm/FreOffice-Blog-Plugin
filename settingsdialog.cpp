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
#include <QSettings>
#include <QDebug>
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
    QSettings settings("freoffice", "blog-plugin");
    settings.beginGroup("Accounts");
    QStringList accounts = settings.childKeys();
    QStandardItemModel *model = new QStandardItemModel(this);
    foreach(QString accountKey, accounts) {
        QStandardItem *item = new QStandardItem(accountKey);
        qDebug() << accountKey;
        model->appendRow(item);
    }
    selector = new QMaemo5ListPickSelector;
    selector->setModel(model);
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
    qDebug() << accountButton->valueText();
    QString blog = accountButton->valueText();
    accountEditDialog *aed = new accountEditDialog(blog,this);
    aed->show();
}
