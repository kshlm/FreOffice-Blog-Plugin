/*
 *  Copyright (c) 2010 Kaushal M <kshlmster@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "bloggerapi.h"
#include "bloggerpost.h"
#include <QtXml>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QtXml>

#include <KoStore.h>
#include <kmimetype.h>

bloggerApi::bloggerApi(QObject *parent)
    : QObject(parent)
{
    loggingIn = false;
    loggingInPicasa = false;
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

void bloggerApi::picasaAuth()
{
    QByteArray data;
    data.append(QString("Email=" + username + "&Passwd=" + password).toUtf8());
    data.append(QString("&service=lh2&source=FreOffice").toUtf8());
    QNetworkRequest req(QUrl("https://www.google.com/accounts/ClientLogin"));
    req.setRawHeader("Host", "www.google.com");
    req.setRawHeader("GData-Version", "2.0");
    req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, data.length());

    manager->post(req, data);
    loggingInPicasa = true;
}

void bloggerApi::listBlogs()
{
    qDebug() << "In listblogs";
    QUrl url("http://www.blogger.com/feeds/default/blogs");
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "FreOffice");
    request.setRawHeader("GData-Version", "2.0");
    request.setRawHeader("Authorization", authToken.toUtf8());

    manager->get(request);
    waitingForList = true;
}

void bloggerApi::newPost()
{
    qDebug() << "In newPost";
    uploadImages();

    QByteArray postData = post->preparePost().toUtf8();
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

void bloggerApi::uploadImages()
{
    qDebug() << "In uploadImages";
    doc.setContent(QString(*post->getContent()));
    QDomNodeList list = doc.documentElement().elementsByTagName("img");
    if(!list.isEmpty()) {
        for(uint i = 0; i < list.length(); i++) {
            QDomElement node = list.at(i).toElement();
            QString imgPath = node.attribute("ns0:src");
            QString imgUrl = picasaUpload(imgPath);
            node.removeAttribute("ns0:src");
            node.removeAttribute("xmlns:ns0");
            node.setAttribute("src", imgUrl);
        }
        QString postData;
        QTextStream ts(&postData);
        doc.save(ts, 0);
        post->setContent(postData);
    }
}

QString bloggerApi::picasaUpload(QString pathInStore)
{
    qDebug() << "In uploadImage()";
    QByteArray imgData;
    store->extractFile(pathInStore, imgData);

    QUrl url("http://picasaweb.google.com/data/feed/api/user/default/albumid/default");
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "FreOffice");
    request.setRawHeader("GData-Version", "2.0");
    request.setRawHeader("Authorization", picasaToken.toUtf8());
    QString mimetype = KMimeType::findByContent(imgData)->name();
    request.setRawHeader("Content-Type", mimetype.toUtf8());
    request.setRawHeader("Content-Length", QString::number(imgData.length()).toUtf8());
    request.setRawHeader("Slug", pathInStore.toUtf8());

    QNetworkReply *reply = manager->post(request, imgData);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec() ;

    QByteArray data = reply->readAll();
    QDomDocument doc;
    doc.setContent(data);
    QDomElement content = doc.documentElement().firstChildElement("content");
    QString imgUrl = content.attribute("src");

    return imgUrl;
}

void bloggerApi::handleData(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    if(!reply->error()) {
        if(loggingIn) {
            loggingIn = false;
            qDebug() << "--------> In authenticate" ;
            QString text(data.data());
            text = text.right(text.length() - text.indexOf("Auth=") - 5);
            authToken = QString("GoogleLogin auth=") + text.left(text.indexOf("\n"));
            if(authToken.length() > 20) {
                qDebug() << "Authentication sucessfull";
                emit authenticationDone(authToken);
                reply->deleteLater();
                if(func == this->ListBlogs) {
                    listBlogs();
                }
                if(func == this->NewPost) {
                    picasaAuth();
                }
            } else {
                emit bloggerError();
            }
        } else if(loggingInPicasa) {
            loggingInPicasa = false;
            qDebug() << "--------> In picasa authenticate";
            QString text(data.data());
            text = text.right(text.length() - text.indexOf("Auth=") -5);
            picasaToken = QString("GoogleLogin auth=") + text.left(text.indexOf("\n"));
            if(picasaToken.length() > 20) {
                qDebug() << "Picasa authentication sucessfull";
                reply->deleteLater();
                newPost();
            } else {
                emit bloggerError();
            }
        } else if(waitingForList) {
            waitingForList = false;
            qDebug() << "--------> In listslot" ;
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
            qDebug() << "List done";
            emit listDone(blogs);
            reply->deleteLater();
        } else if(postingAPost) {
            postingAPost = false;
            qDebug() << "--------> In new post slot";
            QDomDocument doc;
            doc.setContent(data);
            QDomNode entry = doc.documentElement();
            QDomElement id = entry.firstChildElement("id");
            QString postId = id.text();
            postId = postId.right(postId.length() - postId.lastIndexOf("-") - 1);
            qDebug() << "New post successful : " << postId.toULongLong();
            emit postDone(postId.toULongLong());
            reply->deleteLater();
        }
    } else {
        qDebug() << "ERROR" << endl << data;
        qDebug() << reply->errorString();
        emit bloggerError();
        reply->deleteLater();
    }
}
