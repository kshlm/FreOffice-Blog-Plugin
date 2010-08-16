#include "bloggerpost.h"

bloggerPost::bloggerPost()
{
}

void bloggerPost::addTags(const QString &label)
{
    labels.append(label);
}

void bloggerPost::setContent(const QString &content)
{
    this->content = content;
}

void bloggerPost::setTitle(const QString & title)
{
    this->title = title;
}

void bloggerPost::setPostStatus(const QString & postStatus)
{
    this->postStatus = postStatus;
}

QString bloggerPost::preparePost()
{
    QString post = "<entry xmlns='http://www.w3.org/2005/Atom'>\n";
    post.append(QString("<title type='text'>%1</title>\n").arg(title));
    post.append("<content type='xhtml'>\n");
    post.append(content);
    post.append("</content>\n");
    foreach(QString label, labels) {
        post.append(QString("<category scheme=\"http://www.blogger.com/atom/ns#\" term=\"%1\" />\n").arg(label));
    }
    if(postStatus != "publish") {
        post.append("<app:control xmlns:app=\"http://www.w3.org/2007/app\">\n<app:draft>yes</app:draft>\n</app:control>");
    }
    post.append("</entry>\n");
    return post;
}


