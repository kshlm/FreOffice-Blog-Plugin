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

