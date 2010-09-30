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

#ifndef ACCOUNTEDITDIALOG_H
#define ACCOUNTEDITDIALOG_H

#include <QDialog>
#include <QMap>
class QMaemo5ValueButton;
class QMaemo5ListPickSelector;
class QPushButton;
class QLineEdit;
class QComboBox;
class QLabel;
class encryptSupport;

class accountEditDialog : public QDialog
{
    Q_OBJECT
public:
    accountEditDialog(QWidget *parent = 0);
    accountEditDialog(QString & blog, QWidget *parent = 0);
    ~accountEditDialog();

private:
    encryptSupport *cipher;

    QMaemo5ValueButton *blogPlatform;
    QMaemo5ListPickSelector *selector;
    QComboBox *bloggerBlogs;
    QPushButton *saveButton;
    QPushButton *fetchBlogsButton;
    QLineEdit *blogUrlEdit;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLabel *l1;
    QLabel *l2;
    QLabel *l3;
    QLabel *l4;

    QMap<QString, QString> bloggerBlogList;

    void setupDialog();
    void fillDetails(QString &);
    void disableWidgets();
    void enableWidgets();

private slots:
    void platformSelected(const QString &);
    void fetchBlogsButtonClickedSlot();
    void saveButtonClicked();
    void saveAccount(int blogId = 0);
    void bloggerApiListDoneSlot(QMap<QString, QString>);
    void errorSlot();
};

#endif // ACCOUNTEDITDIALOG_H
