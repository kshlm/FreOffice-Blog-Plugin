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

#ifndef POSTDIALOG_H
#define POSTDIALOG_H

#include <QDialog>
#include <QMap>

class encryptSupport;
class KoStore;

namespace Ui
{
class postDialog;
}

class QMaemo5ValueButton;
class QMaemo5ListPickSelector;
class QPushButton;
class QLineEdit;
class QCheckBox;

class postDialog : public QDialog
{
    Q_OBJECT
public:
    postDialog(QWidget *parent = 0);
    ~postDialog();
    void setFilePath(const QString &);
private:
    void setupDialog();
    void fillAccounts();
    void disableDialog();
    void enableDialog();

    QMaemo5ValueButton *accountButton;
    QMaemo5ListPickSelector *selector;
    QLineEdit *fileSelectEdit;
    QLineEdit *titleEdit;
    QLineEdit *tagsEdit;
    QLineEdit *categoryEdit;
    QPushButton *selectButton;
    QPushButton *postButton;
    QCheckBox *publishCheckbox;

    encryptSupport *cipher;
private slots:
    void showOpenFileDialog();
    void postButtonClicked();
    void newPostSignalSlot(qulonglong);
    void errorSlot();
    void selectorSelectedSlot(QString);

};

#endif // POSTDIALOG_H
