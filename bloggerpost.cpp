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

QString *bloggerPost::getContent()
{
    return new QString(content);
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


