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

#include "wordpressapi.h"
#include "maiaXmlRpcClient.h"

#include <QUrl>
#include <QtXml>

#include <KoStore.h>
#include <kmimetype.h>

wordpressApi::wordpressApi(QString &blogUrl, QObject *parent)
    : QObject(parent),
      count(0)
{
    if(!blogUrl.endsWith("/", Qt::CaseInsensitive))
        blogUrl.append("/");
    blogUrl.append("xmlrpc.php");
    xmlrpcUrl = new QUrl(blogUrl);

    client = new MaiaXmlRpcClient(*xmlrpcUrl, this);
}

void wordpressApi::setUsername(QString &username)
{
    this->username = username;
}

void wordpressApi::setPassword(QString &password)
{
    this->password = password;
}

void wordpressApi::getBlogid()
{
    qDebug() << "----> wordpressApi::getBlogid()";
    QVariantList params;
    params << username << password;
    client->call("wp.getUsersBlogs", params, this, SLOT(getBlogidSlot(QVariant&)), this, SLOT(xmlrpcFaultSlot(int, QString)));
}

void wordpressApi::getBlogidSlot(QVariant & reply)
{
    qDebug() << "----> wordpressApi::getBlogidSlot()";
    QVariant tmp = reply.value<QVariantList>()[0];
    QVariantMap map = tmp.value<QVariantMap>();
    blogid = map.value("blogid").toInt();
    qDebug() << "blogid = " << blogid;
    emit getBlogidSignal(blogid);
}

void wordpressApi::setBlogid(int blogid)
{
    this->blogid = blogid;
}

void wordpressApi::setKoStore(KoStore *store)
{
    this->store = store;
}

void wordpressApi::newPost(wordpressPost & post)
{
    qDebug() << "----> worpressApi::newPost()" ;
    this->post = post;
    uploadImages();
    connect(this, SIGNAL(imagesUploaded()),this, SLOT(continuePost()));
}

void wordpressApi::continuePost()
{
        QVariantList params;
        params << blogid << username << password << post.preparePost();
        client->call("metaWeblog.newPost", params, this, SLOT(newPostSlot(QVariant&)), this, SLOT(xmlrpcFaultSlot(int, QString)));
}

void wordpressApi::newPostSlot(QVariant & reply)
{
    qDebug() << "----> wordpressApi::newPostSlot()";
    qDebug() << "New post successfull. ID = " << reply.toString();
    emit newPostSignal(reply.toULongLong());
}

void wordpressApi::xmlrpcFaultSlot(int error, QString message)
{
    qDebug() << "Error : " << error << message;
    emit wordpressError();
}

void wordpressApi::uploadImages()
{
    qDebug() << "----> wordpressApi::uploadImages()";
    doc.setContent(QString(*post.getDescription()));
    QDomNodeList list  = doc.documentElement().elementsByTagName("img");
    if(list.isEmpty()) {
        emit imagesUploaded();
        return;
    }
    for(uint i = 0; i < list.length(); i++) {
        QDomNode node = list.at(i);
        count++;
        uploadImage(node.toElement().attribute("ns0:src"));
        qDebug() << " IMAGE" << i << node.toElement().attribute("ns0:src");
    }
}

void wordpressApi::uploadImage(QString pathInStore)
{
    qDebug() << "----> wordpressApi::uploadImage() :" << pathInStore;
    QByteArray imgData;
    store->extractFile(pathInStore, imgData);
    QVariantMap map;
    map.insert("name", QString(pathInStore));
    map.insert("bits", QByteArray(imgData));
    QString mimetype = "";
    mimetype += KMimeType::findByContent(imgData)->name();
    qDebug() << mimetype;
    map.insert("type", QString(mimetype));
    QVariantList params;
    params << blogid << username << password << map;
    client->call("wp.uploadFile", params, this, SLOT(uploadImageSlot(QVariant&)), this, SLOT(xmlrpcFaultSlot(int,QString)));
}

void wordpressApi::uploadImageSlot(QVariant & reply) {
    qDebug() << "----> wordPressApi::uploadImageSlot() : Image uploaded";
    count--;
    imgUrlList << reply.value<QVariantMap>()["url"].toString();
    qDebug() << imgUrlList;
    if(count == 0) {
        qDebug() << "----> wordPressApi::uploadImageSlot() : Rebuilding body";
        QDomNodeList list  = doc.documentElement().elementsByTagName("img");
        for(int i = 0; i < list.length(); i++) {
            QDomElement element = list.at(i).toElement();
            element.removeAttribute("xmlns:ns0");
            element.removeAttribute("ns0:src");
            element.setAttribute("src", imgUrlList.at(i));
        }
        QString postData;
        QTextStream ts(&postData);
        doc.save(ts, 0);
        post.setDescription(postData);
        emit imagesUploaded();
        return;
    }
}
