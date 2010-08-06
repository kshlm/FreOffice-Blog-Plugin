# #####################################################################
# Automatically generated by qmake (2.01a) Tue Jul 20 14:59:43 2010
# #####################################################################
TEMPLATE = app
TARGET =
DEPENDPATH += . \
    libmaia
INCLUDEPATH += . \
    libmaia \
    $
QT += xml \
    network \
    maemo5
LIBS += -lkomain \
    -lkwordprivate
#CONFIG += debug
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
    bloggerpost.h \
    bloggerapi.h
SOURCES += libmaia/maiaFault.cpp \
    libmaia/maiaObject.cpp \
    libmaia/maiaXmlRpcClient.cpp \
    libmaia/maiaXmlRpcServer.cpp \
    libmaia/maiaXmlRpcServerConnection.cpp \
    wordpressapi.cpp \
    wordpresspost.cpp \
    main.cpp \
    maindialog.cpp \
    settingsdialog.cpp \
    documentextractor.cpp \
    accounteditdialog.cpp \
    postdialog.cpp \
    bloggerpost.cpp \
    bloggerapi.cpp
FORMS += maindialog.ui
