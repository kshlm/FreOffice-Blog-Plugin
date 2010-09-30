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

#include "accounteditdialog.h"
#include "wordpressapi.h"
#include "bloggerapi.h"
#include "encryptsupport.h"

#include <QMaemo5ValueButton>
#include <QMaemo5ListPickSelector>
#include <QMaemo5InformationBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QListWidget>
#include <QDebug>
#include <QSettings>
#include <QVariantMap>
#include <QComboBox>
accountEditDialog::accountEditDialog(QWidget *parent) :
    QDialog(parent),
    cipher(new encryptSupport(this))
{
    setupDialog();
    this->setWindowTitle("New Account");
}

accountEditDialog::accountEditDialog(QString &blog, QWidget *parent):
    QDialog(parent)
{
    setupDialog();
    this->setWindowTitle("Edit Account");
    fillDetails(blog);
    qDebug() << blog;
}

accountEditDialog::~accountEditDialog()
{
}

void accountEditDialog::setupDialog()
{
    blogPlatform = new QMaemo5ValueButton("Select platform");
    blogPlatform->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    l1 = new QLabel("Blog Url", this);
    l2 = new QLabel("Username", this);
    l3 = new QLabel("Password", this);
    l4 = new QLabel("Select blog");
    blogUrlEdit = new QLineEdit(this);
    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    bloggerBlogs = new QComboBox(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    QFormLayout *flayout = new QFormLayout();
    flayout->addRow(l1, blogUrlEdit);
    flayout->addRow(l2, usernameEdit);
    flayout->addRow(l3, passwordEdit);
    flayout->addRow(l4, bloggerBlogs);
    fetchBlogsButton = new QPushButton("Fetch Blogs", this);
    saveButton = new QPushButton("Save", this);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(fetchBlogsButton);
    hlayout->addWidget(saveButton);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(blogPlatform);
    layout->addLayout(flayout);
    layout->addLayout(hlayout);
    bloggerBlogs->setVisible(false);
    fetchBlogsButton->setVisible(false);
    l4->setVisible(false);
    QStringList list;
    list << "Wordpress" << "Blogger";
    QStandardItemModel *model = new QStandardItemModel(this);
    foreach(QString s, list) {
        QStandardItem *item = new QStandardItem(s);
        model->appendRow(item);
    }
    selector = new QMaemo5ListPickSelector;
    selector->setModel(model);
    selector->setCurrentIndex(0);

    blogPlatform->setPickSelector(selector);
    blogUrlEdit->setInputMethodHints(Qt::ImhNoAutoUppercase);
    usernameEdit->setInputMethodHints(Qt::ImhNoAutoUppercase);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));
    connect(fetchBlogsButton, SIGNAL(clicked()), this, SLOT(fetchBlogsButtonClickedSlot()));
    connect(selector, SIGNAL(selected(const QString &)), this, SLOT(platformSelected(QString)));
}

void accountEditDialog::platformSelected(const QString & platform)
{
    if("Wordpress" == platform) {
        blogUrlEdit->setVisible(true);
        l1->setVisible(true);
        bloggerBlogs->setVisible(false);
        l4->setVisible(false);
        fetchBlogsButton->setVisible(false);
        selector->setCurrentIndex(0);
    }
    if("Blogger" == platform) {
        bloggerBlogs->setVisible(true);
        bloggerBlogs->setDisabled(true);
        l4->setVisible(true);
        blogUrlEdit->setVisible(false);
        l1->setVisible(false);
        saveButton->setDisabled(true);
        fetchBlogsButton->setVisible(true);
        selector->setCurrentIndex(1);
    }
}

void accountEditDialog::fillDetails(QString & blog)
{
    QSettings settings("freoffice", "blog-plugin");
    settings.beginGroup("Accounts");
    QVariantMap map = settings.value(blog).value<QVariantMap>();
    QString platform = map.value("platform").toString();
    QString blogUrl = map.value("platform").toString();
    QString username = map.value("username").toString();
    QString password = map.value("password").toString();

    platformSelected(platform);
    blogUrlEdit->setText(blogUrl);
    usernameEdit->setText(username);
    passwordEdit->setText(cipher->decrypt(password));
}

void accountEditDialog::saveButtonClicked()
{
    if("Blogger" == selector->currentValueText()) {
//        blogUrlEdit->setText(bloggerBlogList.value(QString(bloggerBlogs->currentText())));
        saveAccount(-1);
    } else if("" == blogUrlEdit->text() | "" == usernameEdit->text() | "" == passwordEdit->text()) {
        QMaemo5InformationBox::information(this, "Please enter all details", QMaemo5InformationBox::DefaultTimeout);
        return;
    }
    QString blogUrl = blogUrlEdit->text();
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    if("Wordpress" == selector->currentValueText()) {
        wordpressApi *api = new wordpressApi(blogUrl, this);
        api->setUsername(username);
        api->setPassword(password);
        api->getBlogid();
        connect(api, SIGNAL(getBlogidSignal(int)), this, SLOT(saveAccount(int)));
        connect(api, SIGNAL(wordpressError()), this, SLOT(errorSlot()));
    }
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, true);
    disableWidgets();
}

void accountEditDialog::fetchBlogsButtonClickedSlot()
{
    if("" == usernameEdit->text() | "" == passwordEdit->text()) {
        QMaemo5InformationBox::information(this, "Please enter all details", QMaemo5InformationBox::DefaultTimeout);
        return;
    }
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    bloggerApi *api = new bloggerApi(this);
    api->setUsername(username);
    api->setPassword(password);
    api->authenticate(bloggerApi::ListBlogs);
    connect(api, SIGNAL(listDone(QMap<QString, QString>)), this, SLOT(bloggerApiListDoneSlot(QMap<QString, QString>)));
    connect(api, SIGNAL(bloggerError()), this, SLOT(errorSlot()));
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, true);
    disableWidgets();
}

void accountEditDialog::bloggerApiListDoneSlot(QMap<QString, QString> blogs)
{
    qDebug() << "In bloggerListdone slot";
    bloggerBlogList = blogs;
    QStringList keys = blogs.keys();
    foreach(QString key, keys) {
        qDebug() << key;
        bloggerBlogs->addItem(key);
    }
    bloggerBlogs->setEnabled(true);
    saveButton->setEnabled(true);
    l4->setEnabled(true);
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, false);
    qDebug() << "In bloggerListdone slot";
}

void accountEditDialog::saveAccount(int blogId)
{
    if("Blogger" == selector->currentValueText()) {
        blogUrlEdit->setText(bloggerBlogList.value(QString(bloggerBlogs->currentText())));
    }
    if(0 == blogId) {
        this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, true);
        QMaemo5InformationBox::information(this, "Failed to fetch blogid.\nCheck the details again.", QMaemo5InformationBox::NoTimeout);
        enableWidgets();
        return;
    }
    QString name;
    QString platform = selector->currentValueText();
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    QString blogUrl = blogUrlEdit->text();

    QSettings settings("freoffice", "blog-plugin", this);
    settings.beginGroup("Accounts");
    QVariantMap map;
    map.insert("platform", platform);
    map.insert("blogurl", blogUrl);
    if("Blogger" != selector->currentValueText())
        map.insert("blogid", blogId);
    map.insert("username", username);
    map.insert("password", cipher->encrypt(password));
    if("Blogger" == selector->currentValueText()) {
        name = bloggerBlogs->currentText().replace(" ", "_");
    } else {
        name = blogUrlEdit->text().remove("http://");
    }
    settings.setValue(name, map);
    settings.endGroup();
    settings.sync();
    QMaemo5InformationBox::information(this, QString("Saved account %1 sucessfully").arg(name.replace("_", " ")), QMaemo5InformationBox::DefaultTimeout);
    this->accept();
}

void accountEditDialog::errorSlot()
{
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, false);
    QMaemo5InformationBox::information(this, "An error occured while verifying blog details.\n Please check the details you have entered.\nIf the error persists, check your internet connection and retry later.", QMaemo5InformationBox::NoTimeout);
    this->enableWidgets();
}

void accountEditDialog::disableWidgets()
{
    blogPlatform->setDisabled(true);
    bloggerBlogs->setDisabled(true);
    saveButton->setDisabled(true);
    fetchBlogsButton->setDisabled(true);
    blogUrlEdit->setDisabled(true);
    usernameEdit->setDisabled(true);
    passwordEdit->setDisabled(true);
    l1->setDisabled(true);
    l2->setDisabled(true);
    l3->setDisabled(true);
    l4->setDisabled(true);
}

void accountEditDialog::enableWidgets()
{
    blogPlatform->setDisabled(false);
    bloggerBlogs->setDisabled(false);
    if("Blogger" != selector->currentValueText())
        saveButton->setDisabled(false);
    fetchBlogsButton->setDisabled(false);
    blogUrlEdit->setDisabled(false);
    usernameEdit->setDisabled(false);
    passwordEdit->setDisabled(false);
    l1->setDisabled(false);
    l2->setDisabled(false);
    l3->setDisabled(false);
    l4->setDisabled(false);
}
