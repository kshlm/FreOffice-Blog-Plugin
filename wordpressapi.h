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
    void getBlogidSlot(QVariant &);
    void newPostSlot(QVariant &);
    void uploadImageSlot(QVariant &);
    void xmlrpcFaultSlot(int error, const QString message);

signals:
    void imageUploaded();
    void newPostSignal(qulonglong);
    void getBlogidSignal(int);
    void wordpressError();
};

#endif // WORDPRESSAPI_H
