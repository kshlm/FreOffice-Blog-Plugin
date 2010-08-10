#include "bloggerapi.h"
#include "bloggerpost.h"
#include <QtXml>
#include <QNetworkAccessManager>

bloggerApi::bloggerApi(QObject *parent)
    : QObject(parent)
{
    loggingIn = false;
    waitingForList = false;
    postingAPost = false;
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleData(QNetworkReply*)));
    func = this->Nothing;
}

void bloggerApi::setAuthToken(const QString & authToken)
{
    this->authToken = authToken;
}

void bloggerApi::setBlogUrl(const QString & blogUrl)
{
    this->blogUrl = blogUrl;
}

void bloggerApi::setPassword(const QString & password)
{
    this->password = password;
}

void bloggerApi::setUsername(const QString & username)
{
    this->username = username;
}

void bloggerApi::setPost(bloggerPost & post)
{
    this->post = new bloggerPost(post);
}

void bloggerApi::authenticate(BloggerFunction f)
{
    func = f;
    QByteArray data;
    data.append(QString("Email=" + username + "&Passwd=" + password).toUtf8());
    data.append(QString("&service=blogger&source=FreOffice").toUtf8());
    QNetworkRequest req(QUrl("https://www.google.com/accounts/ClientLogin"));
    req.setRawHeader("Host", "www.google.com");
    req.setRawHeader("GData-Version", "2.0");
    req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, data.length());

    manager->post(req, data);
    loggingIn = true;
}

void bloggerApi::newPost()
{
    qDebug() << "NewPost 1";
    QByteArray postData = post->preparePost().toUtf8();
    qDebug() << postData;
    QUrl url(blogUrl.replace("http://", "https://"));
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "FreOffice");
    request.setRawHeader("GData-Version", "2.0");
    request.setRawHeader("Authorization", authToken.toUtf8());
    request.setRawHeader("Content-Type", "application/atom+xml");
    request.setRawHeader("Content-Length", QString::number(postData.length()).toUtf8());

    manager->post(request, postData);
    postingAPost = true;
}

void bloggerApi::handleData(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    if(!reply->error()) {
        if(loggingIn) {
            loggingIn = false;
            qDebug() << "In authenticate" ;
            QString text(data.data());
            text = text.right(text.length() - text.indexOf("Auth=") - 5);
            authToken = QString("GoogleLogin auth=") + text.left(text.indexOf("\n"));
            if(authToken.length() > 20) {
                qDebug() << "sucess" << authToken;
                emit authenticationDone(authToken);
                delete reply;
                reply = 0;
                if(func == this->ListBlogs) {
                    listBlogs();
                }
                if(func == this->NewPost) {
                    newPost();
                }
            } else {
                emit bloggerError();
            }
        } else if(waitingForList) {
            waitingForList = false;
            qDebug() << "In listslot" ;
            QMap<QString, QString> blogs;
            QDomDocument doc;
            doc.setContent(data);
            QDomNodeList entries = doc.documentElement().elementsByTagName("entry");
            QString title, blogUrl;
            for(int i = 0; i < entries.length(); i++) {
                title = entries.at(i).firstChildElement("title").text();
                QDomNodeList links = entries.at(i).toElement().elementsByTagName("link");
                for(int j = 0; j < links.length(); j++) {
                    if(links.at(j).toElement().attributeNode("rel").value().endsWith("#post"))
                        blogUrl = links.at(j).toElement().attributeNode("href").value();
                }
                blogs.insert(title, blogUrl);
            }
            emit listDone(blogs);
            reply->deleteLater();
        } else if(postingAPost) {
            postingAPost = false;
            qDebug() << "POST DONE REPLY DUMP" ;
            qDebug() << reply->readAll();
            emit postDone(0);
            reply->deleteLater();
        }
    } else {
        qDebug() << "ERROR" << endl << data;
        qDebug() << reply->errorString();
        emit bloggerError();
    }
}
