#include "wordpressapi.h"
#include "wordpresspost.h"
#include "maiaXmlRpcClient.h"

#include <QUrl>

wordpressApi::wordpressApi(QString &blogUrl, QObject *parent)
    : QObject(parent)
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
    client->call("wp.getUsersBlogs", params, this, SLOT(getBlogidSlot(QVariant&)), this, SLOT(xmlrpcFaultSlot(int,QString)));
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

void wordpressApi::newPost(wordpressPost & post)
{
    qDebug() << "----> worpressApi::newPost()" ;
    QVariantList params;
    params << blogid << username << password << post.preparePost();
    client->call("metaWeblog.newPost", params, this, SLOT(newPostSlot(QVariant&)), this, SLOT(xmlrpcFaultSlot(int,QString)));
}

void wordpressApi::newPostSlot(QVariant & reply)
{
    qDebug() << "----> wordpressApi::newPostSlot()";
    qDebug() << "New post successfull. ID = " << reply.toString();
    emit newPostSignal(reply.toInt());
}

void wordpressApi::xmlrpcFaultSlot(int error, QString message)
{
    qDebug() << "Error : " << error << message;
}
