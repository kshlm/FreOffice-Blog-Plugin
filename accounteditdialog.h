#ifndef ACCOUNTEDITDIALOG_H
#define ACCOUNTEDITDIALOG_H

#include <QDialog>

class QMaemo5ValueButton;
class QMaemo5ListPickSelector;
class QPushButton;
class QLineEdit;

class accountEditDialog : public QDialog {
    Q_OBJECT
public:
    accountEditDialog(QWidget *parent = 0);
    accountEditDialog(QString & blog, QWidget *parent = 0);
    ~accountEditDialog();

private:
    QMaemo5ValueButton *blogPlatform;
    QMaemo5ListPickSelector *selector;
    QPushButton *saveButton;
    QLineEdit *blogUrlEdit;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;

    void setupDialog();

private slots:
    void platformSelected(const QString &);
    void saveAccount();
};

#endif // ACCOUNTEDITDIALOG_H
