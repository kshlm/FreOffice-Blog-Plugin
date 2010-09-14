#ifndef DOCUMENTEXTRACTOR_H
#define DOCUMENTEXTRACTOR_H

class QString;
class KoStore;

class documentExtractor
{
public:
    documentExtractor();

    QString getBody(KoStore *store);
};

#endif // DOCUMENTEXTRACTOR_H
