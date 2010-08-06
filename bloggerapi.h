#ifndef BLOGGERAPI_H
#define BLOGGERAPI_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPointer>
class bloggerPost;

class bloggerApi : public QObject
{
    Q_OBJECT
public:
    enum BloggerFunction{Nothing = 0, ListBlogs};
    bloggerApi(QObject *parent = 0);

    void setBlogUrl(const QString &);
    void setUsername(const QString &);
    void setPassword(const QString &);
    void setAuthToken(const QString &);
    void authenticate(BloggerFunction);
    void listBlogs();
//    QStringList retrieveBlogList();
    void post(bloggerPost &);

private:
    QString blogUrl;
    QString username;
    QString password;
    QString authToken;
    QNetworkAccessManager *manager;
    QPointer<QNetworkReply> reply;
    BloggerFunction func;

private slots:
    void authenticateSlot();
    void listSlot();
    void postDoneSlot();
    void errorSlot(QNetworkReply::NetworkError);

signals:
    void listDone(QMap<QString, QString>);
    void authenticationDone(QString);
    void postDone(QString);
    void bloggerError();
};

#endif // BLOGGERAPI_H
