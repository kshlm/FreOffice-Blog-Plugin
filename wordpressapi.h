#ifndef WORDPRESSAPI_H
#define WORDPRESSAPI_H

#include <QObject>

#include "wordpresspost.h"
#include <QDomDocument>
#include <QStringList>
class MaiaXmlRpcClient;
class QUrl;
class KoStore;

class wordpressApi : public QObject
{
    Q_OBJECT
public:
    wordpressApi(QString &blogUrl, QObject *parent = 0);
private:
    MaiaXmlRpcClient * client;
    QUrl *xmlrpcUrl;
    int blogid;
    QString username;
    QString password;
    uint count;
    wordpressPost post;
    KoStore *store;
    QDomDocument doc;
    QStringList imgUrlList;

public:
    void setUsername(QString &);
    void setPassword(QString &);
    void getBlogid();
    void setBlogid(int);
    void setKoStore(KoStore *);
    void newPost(wordpressPost &);
    void uploadImages();
    void uploadImage(QString pathInStore);
private slots:
    void continuePost();
    void getBlogidSlot(QVariant &);
    void newPostSlot(QVariant &);
    void uploadImageSlot(QVariant &);
    void xmlrpcFaultSlot(int error, const QString message);

signals:
    void imagesUploaded();
    void newPostSignal(qulonglong);
    void getBlogidSignal(int);
    void wordpressError();
};

#endif // WORDPRESSAPI_H
