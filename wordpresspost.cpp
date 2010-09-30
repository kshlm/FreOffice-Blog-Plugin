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

#include "wordpresspost.h"

wordpressPost::wordpressPost()
{
}

void wordpressPost::setTitle(QString & title)
{
    this->title = title;
}

QString * wordpressPost::getTitle()
{
    return new QString(title);
}

void wordpressPost::setDescription(QString & description)
{
    this->description = description;
}

QString * wordpressPost::getDescription()
{
    return new QString(description);
}

void wordpressPost::setPostStatus(QString & status)
{
    this->post_status = status;
}

QString * wordpressPost::getPostStatus()
{
    return new QString(post_status);
}

void wordpressPost::addCategory(QString & category)
{
    categories.append(QString(category));
}

QVariantList wordpressPost::getCategories()
{
    return categories;
}

void wordpressPost::setAuthorName(QString & name)
{
    wp_author_display_name = name;
}

QString * wordpressPost::getAuthorName()
{
    return new QString(wp_author_display_name);
}

void wordpressPost::setPostid(QString & postid)
{
    this->postid = postid;
}

QString *wordpressPost::getPostid()
{
    return new QString(postid);
}

void wordpressPost::setTags(QString & tags)
{
    mt_keywords = tags;
}

QString * wordpressPost::getTags()
{
    return new QString(mt_keywords);
}

QVariantMap wordpressPost::preparePost()
{
    QVariantMap map;
    map.insert("title", QString(title));
    map.insert("description", QString(description));
    map.insert("post_status", QString(post_status));
    if(categories.length() > 0)
        map.insert("categories" , categories);
    map.insert("mt_keywords", QString(mt_keywords));
    return map;
}

