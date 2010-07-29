#include "accounteditdialog.h"

#include <QMaemo5ValueButton>
#include <QMaemo5ListPickSelector>
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
    connect(selector, SIGNAL(selected(const QString &)), this, SLOT(platformSelected(const QString&)));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveAccount()));
}

void accountEditDialog::platformSelected(const QString &value)
{
    qDebug() << selector->currentIndex() << value ;
}

void accountEditDialog::saveAccount()
{
    QSettings settings("freoffice","blog-plugin", this);
    settings.beginGroup("Accounts");
    QVariantMap map;
    map.insert("platform", selector->currentValueText());
    map.insert("blogurl", QString(blogUrlEdit->text()));
    map.insert("username", QString(usernameEdit->text()));
    map.insert("password", QString(passwordEdit->text()));
    settings.setValue(selector->currentValueText() + blogUrlEdit->text(), map);
    settings.endGroup();
    settings.sync();
}
