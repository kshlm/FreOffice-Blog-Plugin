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
