#############################################################################
# Makefile for building: blogPlugin
# Generated by qmake (2.01a) (Qt 4.6.2) on: Thu Jul 29 10:32:03 2010
# Project:  blogPlugin.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile blogPlugin.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GL_NO_SCISSOR_TEST -DQT_DEFAULT_TEXTURE_GLYPH_CACHE_WIDTH=1024 -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O3 -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O3 -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/linux-g++-maemo5 -I. -I/targets/FREMANTLE_ARMEL/usr/include/QtCore -I/targets/FREMANTLE_ARMEL/usr/include/QtNetwork -I/targets/FREMANTLE_ARMEL/usr/include/QtGui -I/targets/FREMANTLE_ARMEL/usr/include/QtXml -I/targets/FREMANTLE_ARMEL/usr/include -I. -Ilibmaia -I. -I.
LINK          = g++
LFLAGS        = -Wl,-rpath-link,/usr/lib -Wl,-O1 -Wl,--hash-style=gnu -Wl,-rpath,/usr/lib
LIBS          = $(SUBLIBS)  -L/usr/lib -lkomain -lkwordprivate -L/usr/lib -lQtGui -L/usr/X11R6/lib -lQtNetwork -lQtDBus -lQtXml -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = libmaia/maiaFault.cpp \
		libmaia/maiaObject.cpp \
		libmaia/maiaXmlRpcClient.cpp \
		libmaia/maiaXmlRpcServer.cpp \
		libmaia/maiaXmlRpcServerConnection.cpp \
		wordpressapi.cpp \
		wordpresspost.cpp \
		main.cpp \
		maindialog.cpp \
		settingsdialog.cpp moc_maiaFault.cpp \
		moc_maiaObject.cpp \
		moc_maiaXmlRpcClient.cpp \
		moc_maiaXmlRpcServer.cpp \
		moc_maiaXmlRpcServerConnection.cpp \
		moc_wordpressapi.cpp \
		moc_maindialog.cpp \
		moc_settingsdialog.cpp
OBJECTS       = maiaFault.o \
		maiaObject.o \
		maiaXmlRpcClient.o \
		maiaXmlRpcServer.o \
		maiaXmlRpcServerConnection.o \
		wordpressapi.o \
		wordpresspost.o \
		main.o \
		maindialog.o \
		settingsdialog.o \
		moc_maiaFault.o \
		moc_maiaObject.o \
		moc_maiaXmlRpcClient.o \
		moc_maiaXmlRpcServer.o \
		moc_maiaXmlRpcServerConnection.o \
		moc_wordpressapi.o \
		moc_maindialog.o \
		moc_settingsdialog.o
DIST          = /targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/unix.conf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/linux.conf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/qconfig.pri \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_config.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_pre.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/release.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_post.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/warn_on.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/moc.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/resources.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/uic.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/yacc.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/lex.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		blogPlugin.pro
QMAKE_TARGET  = blogPlugin
DESTDIR       = 
TARGET        = blogPlugin

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_maindialog.h ui_settingsdialog.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: blogPlugin.pro  /targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/linux-g++-maemo5/qmake.conf /targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/unix.conf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/linux.conf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/qconfig.pri \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_config.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_pre.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/release.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_post.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/warn_on.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/moc.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/resources.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/uic.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/yacc.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/lex.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtXml.prl \
		/usr/lib/libQtCore.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtNetwork.prl \
		/usr/lib/libQtDBus.prl
	$(QMAKE) -unix -o Makefile blogPlugin.pro
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/unix.conf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/linux.conf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/qconfig.pri:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_functions.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_config.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_pre.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/release.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_post.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/warn_on.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/unix/thread.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/moc.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/resources.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/uic.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/yacc.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/lex.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtXml.prl:
/usr/lib/libQtCore.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtNetwork.prl:
/usr/lib/libQtDBus.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile blogPlugin.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/blogPlugin1.0.0 || $(MKDIR) .tmp/blogPlugin1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/blogPlugin1.0.0/ && $(COPY_FILE) --parents libmaia/maiaFault.h libmaia/maiaObject.h libmaia/maiaXmlRpcClient.h libmaia/maiaXmlRpcServer.h libmaia/maiaXmlRpcServerConnection.h wordpressapi.h wordpresspost.h maindialog.h settingsdialog.h .tmp/blogPlugin1.0.0/ && $(COPY_FILE) --parents libmaia/maiaFault.cpp libmaia/maiaObject.cpp libmaia/maiaXmlRpcClient.cpp libmaia/maiaXmlRpcServer.cpp libmaia/maiaXmlRpcServerConnection.cpp wordpressapi.cpp wordpresspost.cpp main.cpp maindialog.cpp settingsdialog.cpp .tmp/blogPlugin1.0.0/ && $(COPY_FILE) --parents maindialog.ui settingsdialog.ui .tmp/blogPlugin1.0.0/ && (cd `dirname .tmp/blogPlugin1.0.0` && $(TAR) blogPlugin1.0.0.tar blogPlugin1.0.0 && $(COMPRESS) blogPlugin1.0.0.tar) && $(MOVE) `dirname .tmp/blogPlugin1.0.0`/blogPlugin1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/blogPlugin1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_maiaFault.cpp moc_maiaObject.cpp moc_maiaXmlRpcClient.cpp moc_maiaXmlRpcServer.cpp moc_maiaXmlRpcServerConnection.cpp moc_wordpressapi.cpp moc_maindialog.cpp moc_settingsdialog.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_maiaFault.cpp moc_maiaObject.cpp moc_maiaXmlRpcClient.cpp moc_maiaXmlRpcServer.cpp moc_maiaXmlRpcServerConnection.cpp moc_wordpressapi.cpp moc_maindialog.cpp moc_settingsdialog.cpp
moc_maiaFault.cpp: libmaia/maiaFault.h
	/usr/bin/moc $(DEFINES) $(INCPATH) libmaia/maiaFault.h -o moc_maiaFault.cpp

moc_maiaObject.cpp: libmaia/maiaObject.h
	/usr/bin/moc $(DEFINES) $(INCPATH) libmaia/maiaObject.h -o moc_maiaObject.cpp

moc_maiaXmlRpcClient.cpp: libmaia/maiaObject.h \
		libmaia/maiaXmlRpcClient.h
	/usr/bin/moc $(DEFINES) $(INCPATH) libmaia/maiaXmlRpcClient.h -o moc_maiaXmlRpcClient.cpp

moc_maiaXmlRpcServer.cpp: libmaia/maiaObject.h \
		libmaia/maiaXmlRpcServerConnection.h \
		libmaia/maiaFault.h \
		libmaia/maiaXmlRpcServer.h
	/usr/bin/moc $(DEFINES) $(INCPATH) libmaia/maiaXmlRpcServer.h -o moc_maiaXmlRpcServer.cpp

moc_maiaXmlRpcServerConnection.cpp: libmaia/maiaFault.h \
		libmaia/maiaXmlRpcServerConnection.h
	/usr/bin/moc $(DEFINES) $(INCPATH) libmaia/maiaXmlRpcServerConnection.h -o moc_maiaXmlRpcServerConnection.cpp

moc_wordpressapi.cpp: wordpressapi.h
	/usr/bin/moc $(DEFINES) $(INCPATH) wordpressapi.h -o moc_wordpressapi.cpp

moc_maindialog.cpp: maindialog.h
	/usr/bin/moc $(DEFINES) $(INCPATH) maindialog.h -o moc_maindialog.cpp

moc_settingsdialog.cpp: settingsdialog.h
	/usr/bin/moc $(DEFINES) $(INCPATH) settingsdialog.h -o moc_settingsdialog.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_maindialog.h ui_settingsdialog.h
compiler_uic_clean:
	-$(DEL_FILE) ui_maindialog.h ui_settingsdialog.h
ui_maindialog.h: maindialog.ui
	/usr/bin/uic maindialog.ui -o ui_maindialog.h

ui_settingsdialog.h: settingsdialog.ui
	/usr/bin/uic settingsdialog.ui -o ui_settingsdialog.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

maiaFault.o: libmaia/maiaFault.cpp libmaia/maiaFault.h \
		libmaia/maiaObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o maiaFault.o libmaia/maiaFault.cpp

maiaObject.o: libmaia/maiaObject.cpp libmaia/maiaObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o maiaObject.o libmaia/maiaObject.cpp

maiaXmlRpcClient.o: libmaia/maiaXmlRpcClient.cpp libmaia/maiaXmlRpcClient.h \
		libmaia/maiaObject.h \
		libmaia/maiaFault.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o maiaXmlRpcClient.o libmaia/maiaXmlRpcClient.cpp

maiaXmlRpcServer.o: libmaia/maiaXmlRpcServer.cpp libmaia/maiaXmlRpcServer.h \
		libmaia/maiaObject.h \
		libmaia/maiaXmlRpcServerConnection.h \
		libmaia/maiaFault.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o maiaXmlRpcServer.o libmaia/maiaXmlRpcServer.cpp

maiaXmlRpcServerConnection.o: libmaia/maiaXmlRpcServerConnection.cpp libmaia/maiaXmlRpcServerConnection.h \
		libmaia/maiaFault.h \
		libmaia/maiaXmlRpcServer.h \
		libmaia/maiaObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o maiaXmlRpcServerConnection.o libmaia/maiaXmlRpcServerConnection.cpp

wordpressapi.o: wordpressapi.cpp wordpressapi.h \
		wordpresspost.h \
		libmaia/maiaXmlRpcClient.h \
		libmaia/maiaObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o wordpressapi.o wordpressapi.cpp

wordpresspost.o: wordpresspost.cpp wordpresspost.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o wordpresspost.o wordpresspost.cpp

main.o: main.cpp wordpressapi.h \
		wordpresspost.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

maindialog.o: maindialog.cpp maindialog.h \
		ui_maindialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o maindialog.o maindialog.cpp

settingsdialog.o: settingsdialog.cpp settingsdialog.h \
		ui_settingsdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o settingsdialog.o settingsdialog.cpp

moc_maiaFault.o: moc_maiaFault.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_maiaFault.o moc_maiaFault.cpp

moc_maiaObject.o: moc_maiaObject.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_maiaObject.o moc_maiaObject.cpp

moc_maiaXmlRpcClient.o: moc_maiaXmlRpcClient.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_maiaXmlRpcClient.o moc_maiaXmlRpcClient.cpp

moc_maiaXmlRpcServer.o: moc_maiaXmlRpcServer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_maiaXmlRpcServer.o moc_maiaXmlRpcServer.cpp

moc_maiaXmlRpcServerConnection.o: moc_maiaXmlRpcServerConnection.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_maiaXmlRpcServerConnection.o moc_maiaXmlRpcServerConnection.cpp

moc_wordpressapi.o: moc_wordpressapi.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_wordpressapi.o moc_wordpressapi.cpp

moc_maindialog.o: moc_maindialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_maindialog.o moc_maindialog.cpp

moc_settingsdialog.o: moc_settingsdialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_settingsdialog.o moc_settingsdialog.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

