#ifndef WORDPRESSAPI_H
#define WORDPRESSAPI_H

#include <QObject>

class wordpressPost;
class MaiaXmlRpcClient;
class QUrl;

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

public:
    void setUsername(QString &);
    void setPassword(QString &);
    void getBlogid();
    void setBlogid(int);
    void newPost(wordpressPost &);

private slots:
    void getBlogidSlot(QVariant &);
    void newPostSlot(QVariant &);
    void xmlrpcFaultSlot(int error, const QString message);

signals:
    void newPostSignal(int);
    void getBlogidSignal(int);
    void wordpressError();
};

#endif // WORDPRESSAPI_H
