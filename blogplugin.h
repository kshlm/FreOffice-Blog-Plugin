#ifndef ONLINESERVICESPLUGIN_H
#define ONLINESERVICESPLUGIN_H

#include "OfficeInterface.h"
#include <QObject>

class mainDialog;
class KoDocument;

class onlineServicesPlugin: public QObject, public OfficeInterface
{
    Q_OBJECT
    Q_INTERFACES(OfficeInterface)
public:
    onlineServicesPlugin();
    ~onlineServicesPlugin();
    void setDocument(void *doc);
    QWidget * view();
    QString pluginName();
    QStringList pluginSupportTypes();

private:
    QString name;
    mainDialog *window;
    KoDocument *doc;
};

#endif // ONLINESERVICESPLUGIN_H
