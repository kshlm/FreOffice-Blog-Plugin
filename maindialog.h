#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

namespace Ui {
    class mainDialog;
}

class mainDialog : public QDialog {
    Q_OBJECT
public:
    mainDialog(QWidget *parent = 0);
    ~mainDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::mainDialog *ui;

private slots:
    void showSettingsDialog();
    void showPostDialog();
};

#endif // MAINDIALOG_H
