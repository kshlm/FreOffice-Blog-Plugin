# #####################################################################
# Automatically generated by qmake (2.01a) Tue Jul 20 14:59:43 2010
# #####################################################################
TEMPLATE = lib
DEPENDPATH += . \
    libmaia
INCLUDEPATH += . \
    libmaia \
    /usr/include/office/ \
    /usr/local/include/office/
QT += xml \
    network \
    maemo5 \
    xmlpatterns
LIBS += -lkoodf \
    -lcrypto
CONFIG += plugin
TARGET = BlogPlugin
target.path = /usr/lib/freoffice/
files.path = /usr/share/freoffice/plugins/
files.files = odf2html.xsl
INSTALLS += target \
    files

# Input
HEADERS += libmaia/maiaFault.h \
    libmaia/maiaObject.h \
    libmaia/maiaXmlRpcClient.h \
    libmaia/maiaXmlRpcServer.h \
    libmaia/maiaXmlRpcServerConnection.h \
    wordpressapi.h \
    wordpresspost.h \
    maindialog.h \
    settingsdialog.h \
    documentextractor.h \
    accounteditdialog.h \
    postdialog.h \
    blogplugin.h \
    bloggerapi.h \
    bloggerpost.h \
    encryptsupport.h \
    postdialog.h
SOURCES += libmaia/maiaFault.cpp \
    libmaia/maiaObject.cpp \
    libmaia/maiaXmlRpcClient.cpp \
    libmaia/maiaXmlRpcServer.cpp \
    libmaia/maiaXmlRpcServerConnection.cpp \
    wordpressapi.cpp \
    wordpresspost.cpp \
    maindialog.cpp \
    settingsdialog.cpp \
    documentextractor.cpp \
    accounteditdialog.cpp \
    postdialog.cpp \
    blogplugin.cpp \
    bloggerapi.cpp \
    bloggerpost.cpp \
    encryptsupport.cpp
FORMS += maindialog.ui
OTHER_FILES += odf2html.xsl
