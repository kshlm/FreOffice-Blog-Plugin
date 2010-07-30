#include "postdialog.h"

#include <QMaemo5ValueButton>
#include <QMaemo5ListPickSelector>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QSettings>
#include <QStandardItemModel>

postDialog::postDialog(QWidget *parent) :
    QDialog(parent)
{
    setupDialog();
    fillAccounts();
    this->setWindowTitle("New Post");
}

postDialog::~postDialog()
{
}

void postDialog::setupDialog()
{
    accountButton = new QMaemo5ValueButton("Select a blog", this);
    accountButton->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    selectButton = new QPushButton("Select file",this);
    postButton = new QPushButton("Post",this);
    fileSelectEdit = new QLineEdit(this);
    fileSelectEdit->setDisabled(true);
    titleEdit = new QLineEdit(this);
    tagsEdit = new QLineEdit();
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
    QSettings settings("freoffice", "blog-plugin");
    settings.beginGroup("Accounts");
    QStringList accounts = settings.childKeys();
    QStandardItemModel *model = new QStandardItemModel(this);
    foreach(QString accountKey, accounts) {
        QVariantMap account = settings.value(accountKey).value<QVariantMap>();
        QStandardItem *item = new QStandardItem(account.value("blogurl").toString());
        accountsList.insert(account.value("blogurl").toString(), accountKey);
//        qDebug() << accountKey << account.value("blogurl").toString() << account;
        model->appendRow(item);
    }
    selector = new QMaemo5ListPickSelector;
    selector->setModel(model);
    selector->setCurrentIndex(0);
    accountButton->setPickSelector(selector);
}
