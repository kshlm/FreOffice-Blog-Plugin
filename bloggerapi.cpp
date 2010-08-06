#include "bloggerapi.h"
#include "bloggerpost.h"
#include <QtXml>
#include <QNetworkAccessManager>

bloggerApi::bloggerApi(QObject *parent)
    : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
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

void bloggerApi::authenticate(BloggerFunction f)
{
    func = f;
    QByteArray data;
    data.append(QString("Email="+username+"&Passwd="+password).toUtf8());
    data.append(QString("&service=blogger&source=FreOffice").toUtf8());
    QNetworkRequest req(QUrl("https://www.google.com/accounts/ClientLogin"));
    req.setRawHeader("Host", "www.google.com");
    req.setRawHeader("GData-Version", "2.0");
    req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, data.length());

    reply = manager->post(req, data);
    connect(reply, SIGNAL(finished()), this, SLOT(authenticateSlot()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorSlot(QNetworkReply::NetworkError)));
}

void bloggerApi::authenticateSlot()
{
    qDebug() << "In authenticate" ;
    QByteArray m_data = reply->readAll();
    QString text(m_data.data());
    text = text.right(text.length()-text.indexOf("Auth=")-5);
    authToken = QString("GoogleLogin auth=")+text.left(text.indexOf("\n"));
    if (authToken.length() > 20) {
        qDebug() << "sucess" << authToken;
        emit authenticationDone(authToken);
        delete reply;
        reply = 0;
        if(func == this->ListBlogs) {
            listBlogs();
        }
    }
    else {
        emit bloggerError();
    }
}

void bloggerApi::listBlogs()
{
    qDebug() << "In listblogs";
    QUrl url("http://www.blogger.com/feeds/default/blogs");
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "FreOffice");
    request.setRawHeader("GData-Version", "2.0");
    request.setRawHeader("Authorization", authToken.toUtf8());

    reply = manager->get(request);
    connect (reply, SIGNAL(finished()), this, SLOT(listSlot()));
    connect (reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorSlot(QNetworkReply::NetworkError)));
}

void bloggerApi::listSlot()
{
    qDebug() << "In listslot" ;
    QMap<QString, QString> blogs;
    QByteArray data = reply->readAll();
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
}

void bloggerApi::post(bloggerPost & post)
{
    QByteArray postData = post.preparePost().toUtf8();
    QUrl url(blogUrl);
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "FreOffice");
    request.setRawHeader("GData-Version", "3.0");
    request.setRawHeader("Authorization", authToken.toUtf8());
    request.setRawHeader("Content-Type", "application/xml");
    request.setRawHeader("Content-Length", QString::number(postData.length()).toUtf8());

    reply = manager->post(request, postData);
    connect(reply, SIGNAL(finished()), this, SLOT(postDoneSlot()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorSlot(QNetworkReply::NetworkError)));
}

void bloggerApi::postDoneSlot()
{
    qDebug() << "POST DONE REPLY DUMP" ;
    qDebug() << reply->readAll();
    emit postDone(QString("000000"));
    reply->deleteLater();
}

void bloggerApi::errorSlot(QNetworkReply::NetworkError err)
{
    qDebug() << err << endl << reply->readAll();
    emit bloggerError();
    reply->deleteLater();
}

