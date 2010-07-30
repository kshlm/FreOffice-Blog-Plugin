#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QMap>

class QMaemo5ValueButton;
class QPushButton;
class QStandardItemModel;
class QMaemo5ListPickSelector;

namespace Ui {
    class settingsDialog;
}

class settingsDialog : public QDialog {
    Q_OBJECT
public:
    settingsDialog(QWidget *parent = 0);
    ~settingsDialog();

private:
    void setupDialog();
    void fillAccounts();

    QMaemo5ValueButton *accountButton;
    QMaemo5ListPickSelector *selector;
    QPushButton *newButton;
    QPushButton *editButton;
    QMap<QString, QString> accountsList;

private slots:
    void newButtonClicked();
    void editButtonClicked();

};

#endif // SETTINGSDIALOG_H
