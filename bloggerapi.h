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

#ifndef BLOGGERAPI_H
#define BLOGGERAPI_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QQueue>
#include <QDomDocument>
class bloggerPost;
class KoStore;

class bloggerApi : public QObject
{
    Q_OBJECT
public:
    enum BloggerFunction {Nothing = 0, ListBlogs, NewPost};
    bloggerApi(QObject *parent = 0);

    void setBlogUrl(const QString &);
    void setUsername(const QString &);
    void setPassword(const QString &);
    void setAuthToken(const QString &);
    void authenticate(BloggerFunction func = Nothing);
    void listBlogs();
    void setPost(bloggerPost &);
    void newPost();
    void setKoStore(KoStore *);

private:
    bool loggingIn;
    bool waitingForList;
    bool postingAPost;
    bool loggingInPicasa;
    QString blogUrl;
    QString username;
    QString password;
    QString authToken;
    QString picasaToken;
    QNetworkAccessManager *manager;

    BloggerFunction func;
    bloggerPost *post;

    KoStore *store;

    QDomDocument doc;

    void picasaAuth();
    QString picasaUpload(QString pathInStore);
    void uploadImages();

private slots:
    void handleData(QNetworkReply *);

signals:
    void listDone(QMap<QString, QString>);
    void authenticationDone(QString);
    void postDone(qulonglong);
    void bloggerError();
};

#endif // BLOGGERAPI_H
