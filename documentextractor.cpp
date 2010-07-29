#include "documentextractor.h"

#include <kparts/part.h>
#include <kparts/componentfactory.h>
#include <kmimetype.h>
#include <KoView.h>
#include <KWView.h>
#include <KoTextEditor.h>
#include <kurl.h>
#include <KoToolProxy.h>
#include <KWCanvas.h>

#include <QtXml>
#include <QtCore>
#include <QTextDocument>

documentExtractor::documentExtractor()
{
}

QString documentExtractor::getBody(QString &filePath)
{
    KUrl url;
    url.setPath(filePath);
    QString mimetype = KMimeType::findByUrl()->name();
    KoDocument *kdoc = KParts::ComponentFactory::createPartInstanceFromQuery<KoDocument>(mimetype, QString::null);
    kdoc->openUrl(url);
    KoView *koview = kdoc->createView();
    KWView *kwview = qobject_cast<KWView *>(koview);
    KoTextEditor *editor = qobject_cast<KoTextEditor *>(kwview->kwcanvas()->toolProxy()->selection());
    QTextDocument *tdoc = editor->document();
    QString data = tdoc->toHtml();

    QDomDocument ddoc;
    ddoc.setContent(data.toUtf8());
    QDomElement bodyNode = ddoc.documentElement().firstChildElement("body");
    removeColor(bodyNode);

    QString body;
    QTextStream ts(body);
    bodyNode.save(ts, 0);

    removeTags(body);

    return body;
}

void documentExtractor::removeColor(QDomElement &node)
{
    if(node.hasChildNodes()) {
        QDomNodeList children = node.childNodes();
        for(int i = 0; i < children.length(); i++) {
            QDomNode x = children.at(i);
            if(x.isElement()) {
                QDomElement e = x.toElement();
                removeColor(e);
            }
        }
    }
    if(node.hasAttribute("style")) {
        QString style = node.attribute("style");
        node.removeAttribute("style");
        if(node.tagName() == "td")
            return;
        style = style.remove(QRegExp("color*;", Qt::CaseInsensitive, QRegExp::Wildcard));
        style = style.remove(QRegExp("background-", Qt::CaseInsensitive, QRegExp::Wildcard));
        node.setAttribute("style", style);
    }
    return;
}

void documentExtractor::removeTags(QString &body)
{
    body = body.right(body.size() - body.indexOf("<td>") - 4);
    body = body.left(body.lastIndexOf("</td>"));
    body.remove(QRegExp("<(?:span)[^>]*>", Qt::CaseInsensitive));
    body.remove(QRegExp("</span>", Qt::CaseInsensitive));
}
