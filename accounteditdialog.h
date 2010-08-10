#ifndef ACCOUNTEDITDIALOG_H
#define ACCOUNTEDITDIALOG_H

#include <QDialog>
#include <QMap>
class QMaemo5ValueButton;
class QMaemo5ListPickSelector;
class QPushButton;
class QLineEdit;
class QComboBox;
class QLabel;

class accountEditDialog : public QDialog
{
    Q_OBJECT
public:
    accountEditDialog(QWidget *parent = 0);
    accountEditDialog(QString & blog, QWidget *parent = 0);
    ~accountEditDialog();

private:
    QMaemo5ValueButton *blogPlatform;
    QMaemo5ListPickSelector *selector;
    QComboBox *bloggerBlogs;
    QPushButton *saveButton;
    QPushButton *fetchBlogsButton;
    QLineEdit *blogUrlEdit;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLabel *l1;
    QLabel *l2;
    QLabel *l3;
    QLabel *l4;

    QMap<QString, QString> bloggerBlogList;

    void setupDialog();
    void fillDetails(QString &);
    void disableWidgets();
    void enableWidgets();

private slots:
    void platformSelected(const QString &);
    void fetchBlogsButtonClickedSlot();
    void saveButtonClicked();
    void saveAccount(int blogId = 0);
    void bloggerApiListDoneSlot(QMap<QString, QString>);
    void errorSlot();
};

#endif // ACCOUNTEDITDIALOG_H
