#include "postdialog.h"
#include "wordpressapi.h"
#include "wordpresspost.h"
#include "documentextractor.h"

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
#include <QFileDialog>
#include <QDesktopServices>
#include <QMaemo5InformationBox>

postDialog::postDialog(QWidget *parent) :
    QDialog(parent)
{
    setupDialog();
    fillAccounts();
    this->unsetCursor();
    this->setWindowTitle("New Post");
    connect(selectButton, SIGNAL(clicked()), this, SLOT(showOpenFileDialog()));
    connect(postButton, SIGNAL(clicked()), this, SLOT(postButtonClicked()));
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
        QStandardItem *item = new QStandardItem(accountKey);
        model->appendRow(item);
    }
    selector = new QMaemo5ListPickSelector;
    selector->setModel(model);
    selector->setCurrentIndex(0);
    accountButton->setPickSelector(selector);
}

void postDialog::showOpenFileDialog()
{
    QString filename = QFileDialog::getOpenFileName(this,"Select file", QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation), "Text Documents(*.odt *.doc)");
    if("" == filename)
        return;
    fileSelectEdit->setText(filename);
}

void postDialog::postButtonClicked()
{
    if("" == fileSelectEdit->text() | "" ==titleEdit->text()) {
        QMaemo5InformationBox::information(this, "At least select a file and give a title", QMaemo5InformationBox::DefaultTimeout);
        titleEdit->setFocus();
        return;
    }

    disableDialog();

    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, true);
    this->setWindowTitle("Preparing post");

    QString blog = accountButton->valueText();
    QSettings settings("freoffice", "blog-plugin");
    settings.beginGroup("Accounts");
    QVariantMap map = settings.value(blog).value<QVariantMap>();
    QString blogUrl = map.value("blogurl").toString();
    int blogId = map.value("blogid").toInt();
    QString usename = map.value("username").toString();
    QString password = map.value("password").toString();

    wordpressApi *api = new wordpressApi(blogUrl, this);
    api->setBlogid(blogId);
    api->setUsername(usename);
    api->setPassword(password);

    wordpressPost post;
    QString title = titleEdit->text();
    QString category = categoryEdit->text();
    QString tags = tagsEdit->text();
    QString filename = fileSelectEdit->text();
    QString postStatus = "publish";
    post.setTitle(title);
    post.setTags(tags);
    post.addCategory(category);
//    post.setPostStatus(postStatus);

    documentExtractor ext;
    QString description = ext.getBody(filename);
    post.setDescription(description);
    this->setWindowTitle("Posting ...");
    api->newPost(post);
    connect(api, SIGNAL(newPostSignal(int)), this, SLOT(newPostSignalSlot(int)));
}

void postDialog::newPostSignalSlot(int postid)
{
    this->setWindowTitle("Done");
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, false);
    QMaemo5InformationBox::information(this, QString("Post Sucessfull.\n New PostID is %1").arg(postid), QMaemo5InformationBox::DefaultTimeout);
    this->close();
}

void postDialog::disableDialog()
{
    accountButton->setDisabled(true);
    selectButton->setDisabled(true);
    titleEdit->setDisabled(true);
    categoryEdit->setDisabled(true);
    tagsEdit->setDisabled(true);
    postButton->setDisabled(true);
}
