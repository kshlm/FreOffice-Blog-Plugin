#ifndef BLOGPLUGIN_H
#define BLOGPLUGIN_H

#include "OfficeInterface.h"
#include <QObject>

class mainDialog;
class KoDocument;

class blogPlugin: public QObject, public OfficeInterface
{
    Q_OBJECT
    Q_INTERFACES(OfficeInterface)
public:
    blogPlugin();
    ~blogPlugin();
    void setDocument(void *doc);
    QWidget * view();
    QString pluginName();
    QStringList pluginSupportTypes();

private:
    QString name;
    mainDialog *window;
    KoDocument *doc;
};

#endif // BLOGPLUGIN_H
