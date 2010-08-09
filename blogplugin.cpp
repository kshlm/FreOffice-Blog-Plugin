#include "blogplugin.h"
#include "maindialog.h"
#include "KoDocument.h"
#include <QWeakPointer>
onlineServicesPlugin::onlineServicesPlugin()
{
    name = "Blog";
    window = 0;
}
onlineServicesPlugin::~onlineServicesPlugin()
{
    delete window;
    window = 0;
}

void onlineServicesPlugin::setDocument(void *doc)
{
//    QWeakPointer<void> p = doc;
    this->doc = (KoDocument *) doc;
}

QWidget *onlineServicesPlugin::view()
{
    window = new mainDialog();
    if(doc) {
        window->setFilePath(doc->url().path());
    }
    return window;
}

QString onlineServicesPlugin::pluginName()
{
    return name;
}

QStringList onlineServicesPlugin::pluginSupportTypes()
{
    QStringList types;
    types << "All";
    return types;
}

Q_EXPORT_PLUGIN2(OnlineServicesPlugin, onlineServicesPlugin)
