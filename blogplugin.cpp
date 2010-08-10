#include "blogplugin.h"
#include "maindialog.h"
#include "KoDocument.h"
#include <QWeakPointer>
blogPlugin::blogPlugin()
{
    name = "Blog";
    window = 0;
}
blogPlugin::~blogPlugin()
{
    delete window;
    window = 0;
}

void blogPlugin::setDocument(void *doc)
{
//    QWeakPointer<void> p = doc;
    this->doc = (KoDocument *) doc;
}

QWidget *blogPlugin::view()
{
    window = new mainDialog();
    if(doc) {
        window->setFilePath(doc->url().path());
    }
    return window;
}

QString blogPlugin::pluginName()
{
    return name;
}

QStringList blogPlugin::pluginSupportTypes()
{
    QStringList types;
    types << "Document";
    return types;
}

Q_EXPORT_PLUGIN2(BlogPlugin, blogPlugin)
