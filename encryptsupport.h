#ifndef ENCRYPTSUPPORT_H
#define ENCRYPTSUPPORT_H

#include <QWidget>
class QString;
class QByteArray;

class encryptSupport: public QWidget
{
public:
    encryptSupport(QWidget * parent = 0);
    QString encrypt(const QString &);
    QString decrypt(const QString &);
private:
    QByteArray key;
    QByteArray iv;

    void getDetails();
    void newPassphraseDialog();
    void enterPassphraseDialog();
};

#endif // ENCRYPTSUPPORT_H
