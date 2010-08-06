#ifndef BLOGGERPOST_H
#define BLOGGERPOST_H

#include <QString>
#include <QStringList>

class bloggerPost
{
private:
    QString title;
    QString content;
    QStringList labels;

public:
    bloggerPost();
    void setTitle(const QString &);
    void setContent(const QString &);
    void addCategory(const QString &);
    QString preparePost();
};

#endif // BLOGGERPOST_H
