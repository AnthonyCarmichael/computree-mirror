#-------------------------------------------------
#
# Project created by QtCreator 2014-08-13T09:42:59
#
#-------------------------------------------------
include(../shared.pri)
include($${PLUGIN_SHARED_DIR}/include.pri)

DESTDIR = $${PLUGINSHARED_DESTDIR}

QT       += testlib

QT       += gui

TARGET = tst_modeltest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   -= plugin

TEMPLATE = app


SOURCES += \
    main.cpp \
    cloudtest.cpp \
    itemdrawabletest.cpp \
    steptest.cpp \
    step/steptestmodel1.cpp \
    step/steptestmodelinit1.cpp \
    step/steptestmodel2.cpp \
    step/steptestmodelinit2.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    cloudtest.h \
    itemdrawabletest.h \
    steptest.h \
    step/steptestmodel1.h \
    step/steptestmodelinit1.h \
    step/steptestmodel2.h \
    step/steptestmodelinit2.h
