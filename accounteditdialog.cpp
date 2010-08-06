#include "accounteditdialog.h"
#include "wordpressapi.h"
#include "bloggerapi.h"
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
    QDialog(parent)
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
    saveButton = new QPushButton("Save", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(blogPlatform);
    layout->addLayout(flayout);
    layout->addWidget(saveButton);
    bloggerBlogs->setVisible(false);
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
}

void accountEditDialog::fillDetails(QString & blog)
{
    QSettings settings("freoffice", "blog-plugin");
    settings.beginGroup("Accounts");
    QVariantMap map = settings.value(blog).value<QVariantMap>();
    blogUrlEdit->setText(map.value("blogurl").toString());
    usernameEdit->setText(map.value("username").toString());
    passwordEdit->setText(map.value("password").toString());
}

void accountEditDialog::saveButtonClicked()
{
    if("" == blogUrlEdit->text() | "" == usernameEdit->text() | "" == passwordEdit->text()) {
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
    else if ("Blogger" == selector->currentValueText()) {
        bloggerApi *api = new bloggerApi(this);
        api->setUsername(username);
        api->setPassword(password);
        api->authenticate(bloggerApi::ListBlogs);
        connect(api,SIGNAL(listDone(QMap<QString,QString>)), this, SLOT(bloggerApiListDoneSlot(QMap<QString,QString>)));
        connect(api, SIGNAL(bloggerError()), this, SLOT(errorSlot()));
    }
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, true);
    disableWidgets();
}

void accountEditDialog::bloggerApiListDoneSlot(QMap<QString, QString> blogs)
{
    qDebug() << "In bloggerListdone slot";
    QListWidget *widget = new QListWidget(this);
    QStringList keys = blogs.keys();
    foreach(QString key, keys) {
        qDebug() << key;
        widget->addItem(key);
    }
    widget->setWindowFlags(Qt::Dialog);
    widget->setWindowTitle("Select a blog");
    widget->setEnabled(true);
    widget->show();
    qDebug() << "In bloggerListdone slot";
}

void accountEditDialog::saveAccount(int blogId)
{
    if(0 == blogId) {
        this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, true);
        QMaemo5InformationBox::information(this, "Failed to fetch blogid.\nCheck the details again.", QMaemo5InformationBox::NoTimeout);
        enableWidgets();
        return;
    }
    QSettings settings("freoffice","blog-plugin", this);
    settings.beginGroup("Accounts");
    QVariantMap map;
    map.insert("platform", selector->currentValueText());
    map.insert("blogurl", QString(blogUrlEdit->text()));
    map.insert("blogid", blogId);
    map.insert("username", QString(usernameEdit->text()));
    map.insert("password", QString(passwordEdit->text()));
    settings.setValue(QString(blogUrlEdit->text()).remove("http://"), map);
    settings.endGroup();
    settings.sync();
    QMaemo5InformationBox::information(this, QString("Saved account %1 sucessfully").arg(blogUrlEdit->text().remove("http://")), QMaemo5InformationBox::DefaultTimeout);
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
    this->setDisabled(true);
}

void accountEditDialog::enableWidgets()
{
    this->setEnabled(true);
}
