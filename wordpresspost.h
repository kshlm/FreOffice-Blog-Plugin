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
