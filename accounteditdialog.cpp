#include "accounteditdialog.h"
#include "wordpressapi.h"
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

#include <QDebug>
#include <QSettings>
#include <QVariantMap>

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
    QLabel *l1 = new QLabel("Blog Url", this);
    QLabel *l2 = new QLabel("Username", this);
    QLabel *l3 = new QLabel("Password", this);
    blogUrlEdit = new QLineEdit(this);
    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    QFormLayout *flayout = new QFormLayout();
    flayout->addRow(l1, blogUrlEdit);
    flayout->addRow(l2, usernameEdit);
    flayout->addRow(l3, passwordEdit);
    saveButton = new QPushButton("Save", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(blogPlatform);
    layout->addLayout(flayout);
    layout->addWidget(saveButton);

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
    wordpressApi *api = new wordpressApi(blogUrl, this);
    api->setUsername(username);
    api->setPassword(password);
    api->getBlogid();
    connect(api, SIGNAL(getBlogidSignal(int)), this, SLOT(saveAccount(int)));
    disableWidgets();
}

void accountEditDialog::saveAccount(int blogId)
{
    if(0 == blogId) {
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
    settings.setValue(selector->currentValueText() + QString::number(blogId), map);
    settings.endGroup();
    settings.sync();
    enableWidgets();
}

void accountEditDialog::disableWidgets()
{
    this->setDisabled(true);
}

void accountEditDialog::enableWidgets()
{
    this->setEnabled(true);
}
