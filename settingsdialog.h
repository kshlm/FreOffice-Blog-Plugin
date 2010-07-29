#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
    class settingsDialog;
}

class settingsDialog : public QDialog {
    Q_OBJECT
public:
    settingsDialog(QWidget *parent = 0);
    ~settingsDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::settingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
