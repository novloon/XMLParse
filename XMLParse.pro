#-------------------------------------------------
#
# Project created by QtCreator 2017-10-31T10:42:48
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XMLParse
#TEMPLATE = lib
TEMPLATE = app
#CONFIG += dll
#CONFIG += staticlib

DEFINES += XMLPARSE_LIB

#DESTDIR = ../../lib

MOC_DIR     = xmlparse
OBJECTS_DIR = xmlparse


SOURCES +=\
        xmlparsewidget.cpp \
    xmlreader.cpp \
    xmlwriter.cpp \
    main.cpp

HEADERS  += xmlparsewidget.h \
    xmlreader.h \
    xmlwriter.h \
    winpos.h

#FORMS    += xmlparsewidget.ui
