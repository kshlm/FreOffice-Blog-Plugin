#include "bloggerpost.h"

bloggerPost::bloggerPost()
{
}

void bloggerPost::addCategory(const QString &label)
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

QString bloggerPost::preparePost()
{
    QString post = "<entry xmlns='http://www.w3.org/2005/Atom'>";
    post.append(QString("<title type='text'>%1</title>").arg(title));
    post.append("<content type='xhtml'>");
    post.append(content);
    post.append("</content>");
    foreach(QString label, labels) {
        post.append(QString("<category scheme=\"http://www.blogger.com/atom/ns#\" term=\"%1\" />").arg(label));
    }
    post.append("</entry>");
}


