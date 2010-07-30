#include "maindialog.h"
#include "ui_maindialog.h"

#include "settingsdialog.h"
#include "postdialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("FOBlog");
    connect(ui->accountsButton, SIGNAL(clicked()), this, SLOT(showSettingsDialog()));
    connect(ui->postButton, SIGNAL(clicked()), this, SLOT(showPostDialog()));
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void mainDialog::showSettingsDialog()
{
    settingsDialog *sd = new settingsDialog(this);
    sd->show();
}

void mainDialog::showPostDialog()
{
    postDialog *pd = new postDialog(this);
    pd->show();
}
