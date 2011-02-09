#include "passphrasedialog.h"

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDialogButtonBox>

passphraseDialog::passphraseDialog(QWidget *parent):
        QDialog(parent),
        changeClicked(false) {
    init();
}

void passphraseDialog::init() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Enter the passphrase", this);
    layout->addWidget(label);

    linedit = new QLineEdit(this);
    linedit->setEchoMode(QLineEdit::Password);
    layout->addWidget(linedit);

    okButton = new QPushButton("Ok",this);
    changeButton = new QPushButton("Change Passphrase", this);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->addButton(changeButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
    okButton->setDefault(true);
    layout->addWidget(buttonBox);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(changeButton, SIGNAL(clicked()), this, SLOT(changeClickedSlot()));
}

void passphraseDialog::changeClickedSlot() {
    this->changeClicked = true;
}

QString passphraseDialog::getPassphrase(int &val, QWidget *parent) {
    passphraseDialog dialog(parent);

    QString passphrase = "";
    bool accepted = (dialog.exec() == QDialog::Accepted);

    if(accepted) {
        if(dialog.changeClicked) {
            val = 1;
        }
        else {
            QLineEdit *linedit = dialog.linedit;
            passphrase = linedit->text();
            val = 0;
        }
    }
    else {
        val = -1;
    }

    return passphrase;
}
