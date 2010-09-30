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

#include "documentextractor.h"

#include <QXmlQuery>
#include <QFile>
#include <QDebug>
#include <QDomElement>
#include <QTextStream>

#include <KoStore.h>



documentExtractor::documentExtractor()
{
}

QString documentExtractor::getBody(KoStore *store)
{
    qDebug() << "----> documentExtractor::getBody() : Extracting body";
    QByteArray content, tmp;
    content.append("<?xml version='1.0' encoding='UTF-8'?> <office:document xmlns:office='urn:oasis:names:tc:opendocument:xmlns:office:1.0'>");
    store->extractFile("meta.xml",tmp);
    tmp.remove(0,38);
    content.append(tmp);
    tmp.clear();
    store->extractFile("styles.xml",tmp);
    tmp.remove(0,38);
    content.append(tmp);
    tmp.clear();
    store->extractFile("content.xml", tmp);
    tmp.remove(0,38);
    content.append(tmp);
    tmp.clear();
    content.append("</office:document>");

    QFile *odf2html = new QFile("/usr/share/freoffice/plugins/odf2html.xsl");
    odf2html->open(QFile::ReadOnly);

    QXmlQuery query2(QXmlQuery::XSLT20);
    query2.setFocus(content);
    query2.setQuery(odf2html);

    QString html;
    query2.evaluateTo(&html);

    odf2html->close();

    QDomDocument doc;
    doc.setContent(html);
    QDomElement bodyNode = doc.documentElement().firstChildElement("body");
    QString body;
    QTextStream ts(&body);
    bodyNode.save(ts, 0);

    return body;
}

