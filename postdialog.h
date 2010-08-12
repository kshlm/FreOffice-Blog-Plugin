#ifndef POSTDIALOG_H
#define POSTDIALOG_H

#include <QDialog>
#include <QMap>

class encryptSupport;

namespace Ui
{
class postDialog;
}

class QMaemo5ValueButton;
class QMaemo5ListPickSelector;
class QPushButton;
class QLineEdit;
class QCheckBox;

class postDialog : public QDialog
{
    Q_OBJECT
public:
    postDialog(QWidget *parent = 0);
    ~postDialog();
    void setFilePath(const QString &);
private:
    void setupDialog();
    void fillAccounts();
    void disableDialog();
    void enableDialog();

    QMaemo5ValueButton *accountButton;
    QMaemo5ListPickSelector *selector;
    QLineEdit *fileSelectEdit;
    QLineEdit *titleEdit;
    QLineEdit *tagsEdit;
    QLineEdit *categoryEdit;
    QPushButton *selectButton;
    QPushButton *postButton;
    QCheckBox *publishCheckbox;

    encryptSupport *cipher;
private slots:
    void showOpenFileDialog();
    void postButtonClicked();
    void newPostSignalSlot(int);
    void errorSlot();

};

#endif // POSTDIALOG_H
