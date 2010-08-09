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
    enum BloggerFunction{Nothing = 0, ListBlogs, NewPost};
    bloggerApi(QObject *parent = 0);

    void setBlogUrl(const QString &);
    void setUsername(const QString &);
    void setPassword(const QString &);
    void setAuthToken(const QString &);
    void authenticate(BloggerFunction func = Nothing);
    void listBlogs();
    void setPost(bloggerPost &);
    void newPost();

private:
    bool loggingIn;
    bool waitingForList;
    bool postingAPost;
    QString blogUrl;
    QString username;
    QString password;
    QString authToken;
    QNetworkAccessManager *manager;

    BloggerFunction func;
    bloggerPost *post;

private slots:
    void handleData(QNetworkReply *);

signals:
    void listDone(QMap<QString, QString>);
    void authenticationDone(QString);
    void postDone(int);
    void bloggerError();
};

#endif // BLOGGERAPI_H
