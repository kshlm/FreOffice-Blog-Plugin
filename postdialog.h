#ifndef POSTDIALOG_H
#define POSTDIALOG_H

#include <QDialog>
#include <QMap>
namespace Ui {
    class postDialog;
}

class QMaemo5ValueButton;
class QMaemo5ListPickSelector;
class QPushButton;
class QLineEdit;

class postDialog : public QDialog {
    Q_OBJECT
public:
    postDialog(QWidget *parent = 0);
    ~postDialog();

private:
    void setupDialog();
    void fillAccounts();

    QMaemo5ValueButton *accountButton;
    QMaemo5ListPickSelector *selector;
    QLineEdit *fileSelectEdit;
    QLineEdit *titleEdit;
    QLineEdit *tagsEdit;
    QLineEdit *categoryEdit;
    QPushButton *selectButton;
    QPushButton *postButton;
    QMap<QString, QString> accountsList;
};

#endif // POSTDIALOG_H
