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

#include "postdialog.h"
#include "wordpressapi.h"
#include "wordpresspost.h"
#include "bloggerapi.h"
#include "bloggerpost.h"
#include "documentextractor.h"
#include "encryptsupport.h"

#include <QMaemo5ValueButton>
#include <QMaemo5ListPickSelector>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QSettings>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMaemo5InformationBox>
#include <KoStore.h>

postDialog::postDialog(QWidget *parent) :
    QDialog(parent),
    cipher(new encryptSupport(this))
{
    setupDialog();
    fillAccounts();
    if("" == accountButton->valueText()) {
        QMaemo5InformationBox::information(this, "You have not configured any accounts.\nPlease add atleast one account to continue.", QMaemo5InformationBox::NoTimeout);
        return;
    }
    this->unsetCursor();
    this->setWindowTitle("New Post");
    connect(selectButton, SIGNAL(clicked()), this, SLOT(showOpenFileDialog()));
    connect(postButton, SIGNAL(clicked()), this, SLOT(postButtonClicked()));
    connect(selector, SIGNAL(selected(QString)), this, SLOT(selectorSelectedSlot(QString)));
    this->show();
}

postDialog::~postDialog()
{
}

void postDialog::setFilePath(const QString & filePath)
{
    fileSelectEdit->setText(filePath);
}

void postDialog::setupDialog()
{
    accountButton = new QMaemo5ValueButton("Select a blog", this);
    accountButton->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    selectButton = new QPushButton("Select file", this);
    postButton = new QPushButton("Post", this);
    fileSelectEdit = new QLineEdit(this);
    fileSelectEdit->setDisabled(true);
    titleEdit = new QLineEdit(this);
    tagsEdit = new QLineEdit();
    publishCheckbox = new QCheckBox("Publish post", this);
    publishCheckbox->setChecked(true);
    categoryEdit = new QLineEdit(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QFormLayout *flayout = new QFormLayout();
    flayout->addRow(accountButton);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(fileSelectEdit);
    hlayout->addWidget(selectButton);
    flayout->addRow(hlayout);
    flayout->addRow("Title", titleEdit);
    flayout->addRow("Category", categoryEdit);
    flayout->addRow("Tags", tagsEdit);
    flayout->addRow(publishCheckbox);
    QScrollArea *sarea = new QScrollArea(this);
    QWidget *wid = new QWidget(this);
    wid->setLayout(flayout);
    sarea->setWidgetResizable(true);
    sarea->setWidget(wid);
    layout->addWidget(sarea);
    layout->addWidget(postButton);
}

void postDialog::fillAccounts()
{
    QSettings settings("freoffice", "plugin-settings");
    settings.beginGroup("blog-plugin");
    settings.beginGroup("Accounts");
    QStringList accounts = settings.childKeys();
    QStandardItemModel *model = new QStandardItemModel(this);
    foreach(QString accountKey, accounts) {
        QStandardItem *item = new QStandardItem(accountKey);
        model->appendRow(item);
    }
    selector = new QMaemo5ListPickSelector;
    selector->setModel(model);
    selector->setCurrentIndex(-1);
    accountButton->setPickSelector(selector);
    selectorSelectedSlot(selector->currentValueText());
}

void postDialog::selectorSelectedSlot(QString value)
{
    QSettings settings("freoffice", "plugin-settings");
    settings.beginGroup("blog-plugin");
    settings.beginGroup("Accounts");
    QVariantMap m = settings.value(value).value<QVariantMap>();
    QString platform = m.value("platform").toString();

    if("Wordpress" == platform) {
        categoryEdit->setEnabled(true);
    }
    if("Blogger" == platform) {
        categoryEdit->setDisabled(true);
    }
}

void postDialog::showOpenFileDialog()
{
    QString presentPath = ("" != fileSelectEdit->text()) ? fileSelectEdit->text() : QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);
    QString filename = QFileDialog::getOpenFileName(this, "Select file", presentPath, "Text Documents(*.odt)");
    if("" == filename)
        return;
    fileSelectEdit->setText(filename);
}

void postDialog::postButtonClicked()
{
    if("" == fileSelectEdit->text() | "" == titleEdit->text()) {
        QMaemo5InformationBox::information(this, "At least select a file and give a title", QMaemo5InformationBox::DefaultTimeout);
        titleEdit->setFocus();
        return;
    }

    disableDialog();

    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, true);
    this->setWindowTitle("Preparing post");

    QString blog = accountButton->valueText();
    QSettings settings("freoffice", "plugin-settings");
    settings.beginGroup("blog-plugin");
    settings.beginGroup("Accounts");
    QVariantMap map = settings.value(blog).value<QVariantMap>();
    QString platform = map.value("platform").toString();
    QString blogUrl = map.value("blogurl").toString();
    int blogId = map.value("blogid").toInt();
    QString username = map.value("username").toString();
    QString password = map.value("password").toString();
    password = cipher->decrypt(password);
    QString title = titleEdit->text();
    QString category = categoryEdit->text();
    QString tags = tagsEdit->text();
    QString filename = fileSelectEdit->text();
    QString postStatus = publishCheckbox->isChecked() ? "publish" : "draft";
    KoStore *store = KoStore::createStore(filename, KoStore::Read);
    documentExtractor ext;
    QString description = ext.getBody(store);

    if("Wordpress" == platform) {
        wordpressApi *api = new wordpressApi(blogUrl, this);
        api->setBlogid(blogId);
        api->setUsername(username);
        api->setPassword(password);
        api->setKoStore(store);
        wordpressPost post;
        post.setTitle(title);
        post.setTags(tags);
        post.addCategory(category);
        post.setPostStatus(postStatus);
        post.setDescription(description);
        this->setWindowTitle("Posting ...");
        api->newPost(post);
        connect(api, SIGNAL(newPostSignal(qulonglong)), this, SLOT(newPostSignalSlot(qulonglong)));
        connect(api, SIGNAL(wordpressError()), this, SLOT(errorSlot()));
    }
    if("Blogger" == platform) {
        bloggerApi *api = new bloggerApi(this);
        api->setUsername(username);
        api->setPassword(password);
        api->setBlogUrl(blogUrl);
        api->setKoStore(store);
        bloggerPost post;
        post.setTitle(title);
        foreach(QString tag, tags.split(",", QString::SkipEmptyParts))
        post.addTags(tag);
        post.setContent(description);
        post.setPostStatus(postStatus);
        api->setPost(post);
        this->setWindowTitle("Posting...");
        api->authenticate(bloggerApi::NewPost);
        connect(api, SIGNAL(postDone(qulonglong)), this, SLOT(newPostSignalSlot(qulonglong)));
        connect(api, SIGNAL(bloggerError()), this, SLOT(errorSlot()));
    }
}

void postDialog::newPostSignalSlot(qulonglong postid)
{
    this->setWindowTitle("Done");
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, false);
    QMaemo5InformationBox::information(this, QString("Post Sucessfull.\n New PostID is %1").arg(postid), QMaemo5InformationBox::DefaultTimeout);
    this->close();
}

void postDialog::errorSlot()
{
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, false);
    QMaemo5InformationBox::information(this, "An error occured while posting to the blog.\n Please retry.\nIf the error persists, check your internet connection and retry later.", QMaemo5InformationBox::NoTimeout);
    enableDialog();
}

void postDialog::disableDialog()
{
    accountButton->setDisabled(true);
    selectButton->setDisabled(true);
    titleEdit->setDisabled(true);
    categoryEdit->setDisabled(true);
    tagsEdit->setDisabled(true);
    postButton->setDisabled(true);
    publishCheckbox->setDisabled(true);
}

void postDialog::enableDialog()
{
    accountButton->setEnabled(true);
    selectButton->setEnabled(true);
    titleEdit->setEnabled(true);
    tagsEdit->setEnabled(true);
    postButton->setEnabled(true);
    categoryEdit->setEnabled(true);
    publishCheckbox->setEnabled(true);
}
