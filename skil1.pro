QT += core
QT -= gui

TARGET = skil1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    xmlfile.cpp \
    requestprocessor.cpp

HEADERS += \
    xmlfile.h \
    requestprocessor.h

