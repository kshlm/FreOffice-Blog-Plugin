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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QMap>

class QMaemo5ValueButton;
class QPushButton;
class QStandardItemModel;
class QMaemo5ListPickSelector;
class accountEditDialog;
namespace Ui
{
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT
public:
    settingsDialog(QWidget *parent = 0);
    ~settingsDialog();

private:
    void setupDialog();

    QMaemo5ValueButton *accountButton;
    QMaemo5ListPickSelector *selector;
    QPushButton *newButton;
    QPushButton *editButton;
    accountEditDialog *aed;

private slots:
    void fillAccounts();
    void newButtonClicked();
    void editButtonClicked();

};

#endif // SETTINGSDIALOG_H
