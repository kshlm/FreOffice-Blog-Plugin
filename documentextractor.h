#ifndef DOCUMENTEXTRACTOR_H
#define DOCUMENTEXTRACTOR_H

class QString;
class QDomElement;

class documentExtractor
{
public:
    documentExtractor();

    QString getBody(QString & filePath);

private:
    void removeColor(QDomElement & node);
    void removeTags(QString & body);
};

#endif // DOCUMENTEXTRACTOR_H
