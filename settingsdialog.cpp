/*
 *  Copyright (c) 2010 Kaushal M <kshlmster@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

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
    aed = 0;
    if("" == accountButton->valueText()) {
        newButtonClicked();
    }
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
    QSettings settings("freoffice", "plugin-settings");
    settings.beginGroup("blog-plugin");
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
    if(aed != 0) {
        delete aed;
        aed = 0;
    }
    aed = new accountEditDialog(this);
    aed->show();
    connect(aed, SIGNAL(accepted()), this, SLOT(fillAccounts()));
}

void settingsDialog::editButtonClicked()
{
    if(aed != 0) {
        delete aed;
        aed = 0;
    }
    qDebug() << accountButton->valueText();
    QString blog = accountButton->valueText();
    aed = new accountEditDialog(blog, this);
    aed->show();
    connect(aed, SIGNAL(accepted()), this, SLOT(fillAccounts()));
}
