#ifndef WORDPRESSPOST_H
#define WORDPRESSPOST_H

#include <QString>
#include <QMap>
#include <QVariantMap>
class wordpressPost
{
private:
    QString title;
    QString description;
    QString postid;
    QVariantList categories;
    QString post_status;
    QString wp_author_display_name;
    QString mt_keywords;

public:
    wordpressPost();
    void setTitle(QString &);
    QString *getTitle();
    void setDescription(QString &);
    QString *getDescription();
    void setPostStatus(QString &);
    QString *getPostStatus();
    void addCategory(QString &);
    QVariantList getCategories();
    void setAuthorName(QString &);
    QString *getAuthorName();
    void setPostid(QString &);
    QString *getPostid();
    void setTags(QString &);
    QString *getTags();
    QVariantMap preparePost();

signals:
    void error();
};

#endif // WORDPRESSPOST_H
