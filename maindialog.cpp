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

#include "maindialog.h"
#include "ui_maindialog.h"

#include "settingsdialog.h"
#include "postdialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("FOBlog");
    connect(ui->accountsButton, SIGNAL(clicked()), this, SLOT(showSettingsDialog()));
    connect(ui->postButton, SIGNAL(clicked()), this, SLOT(showPostDialog()));
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch(e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void mainDialog::setFilePath(const QString &filePath)
{
    this->filePath = filePath;
}

void mainDialog::showSettingsDialog()
{
    settingsDialog *sd = new settingsDialog(this);
    sd->show();
}

void mainDialog::showPostDialog()
{
    postDialog *pd = new postDialog(this);
    pd->setFilePath(filePath);
//    pd->show();
}
