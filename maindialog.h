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

#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

namespace Ui
{
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT
public:
    mainDialog(QWidget *parent = 0);
    ~mainDialog();
    void setFilePath(const QString &);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::mainDialog *ui;
    QString filePath;

private slots:
    void showSettingsDialog();
    void showPostDialog();
};

#endif // MAINDIALOG_H
