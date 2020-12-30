#-------------------------------------------------
#
# Project created by QtCreator 2020-12-29T19:48:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zegotest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp\
        AppSupport/ZGHelper.cpp \
        AppSupport/ZGHttpClient.cpp \
        AppSupport/ZGLog.cpp \
        AppSupport/ZGManager.cpp \
        AppSupport/ZGTaskQueue.cpp \
        AppSupport/ZGTimer.cpp \
		AppSupport/ZGUtilTools.cpp\
        AppSupport/ZGConfigHelper.cpp 

HEADERS += \
        mainwindow.h\
        AppSupport/AppIDHelper.h \
        AppSupport/AppIDHelper.h \
        AppSupport/ZGConfigHelper.h \
        AppSupport/ZGHelper.h \
        AppSupport/ZGHttpClient.h \
        AppSupport/ZGLog.h \
        AppSupport/ZGManager.h \
        AppSupport/ZGTaskQueue.h \
        AppSupport/ZGTimer.h \
		AppSupport/ZGUtilTools.h

FORMS += \
        mainwindow.ui

message("asdfasdfasdfasd")
win32{

INCLUDEPATH += $$PWD/.
INCLUDEPATH += $$PWD/AppSupport/
INCLUDEPATH += $$PWD/libs/libyuv/include \
               $$PWD/libs/zegosdk/include \
               $$PWD/libs \
               $$PWD/libs/fuskd/Windows \

DEPENDPATH += $$PWD/.
DEPENDPATH += $$PWD/AppSupport/
DEPENDPATH += $$PWD/libs/libyuv/include \
              $$PWD/libs/zegosdk/include \			   
              $$PWD/libs/fuskd/Windows \
              $$PWD/libs

CONFIG += opengl
CONFIG += debug_and_release
debug{
    CONFIG+=console
	contains(QT_ARCH,i386){
	    LIBS +=	-L$$PWD/libs/zegosdk/libs/Win32 -lZegoLiveRoom
		LIBS += -L$$PWD/libs/libyuv/libs -llibyuv_d
		LIBS += -lcomsvcs
        LIBS += -lws2_32
        LIBS += -lcomsuppw
        LIBS += -lWininet
	}else{
	    LIBS +=	-L$$PWD/libs/zegosdk/libs/x64 -lZegoLiveRoom
		LIBS += -L$$PWD/libs/libyuv/libs -llibyuv_d
	    LIBS += -lcomsvcs
        LIBS += -lws2_32
        LIBS += -lcomsuppw
        LIBS += -lWininet
	}
}

release{
   	contains(QT_ARCH,i386){
	    LIBS +=	-L$$PWD/libs/zegosdk/libs/Win32 -lZegoLiveRoom
		LIBS += -L$$PWD/libs/libyuv/libs -llibyuv
		LIBS += -lcomsvcs
        LIBS += -lws2_32
        LIBS += -lcomsuppw
        LIBS += -lWininet
	}else{
	    LIBS +=	-L$$PWD/libs/zegosdk/libs/x64 -lZegoLiveRoom
		LIBS += -L$$PWD/libs/libyuv/libs -llibyuv
		LIBS += -lcomsvcs
        LIBS += -lws2_32
        LIBS += -lcomsuppw
        LIBS += -lWininet
	}
}

}
