#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T16:52:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4){ QT += widgets }

TARGET = tomatime
TEMPLATE = app


SOURCES += main.cpp\
        tomatime.cpp \
    settings.cpp \
    about.cpp

HEADERS  += tomatime.h \
    settings.h \
    about.h

FORMS    += tomatime.ui \
    settings.ui \
    about.ui

RESOURCES += \
    tomatime.qrc
