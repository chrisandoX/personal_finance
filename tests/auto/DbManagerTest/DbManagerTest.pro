QT = core testlib sql

TARGET = tst_dbmanager
TEMPLATE = app
CONFIG += qt warn_on depend_includepath testcase

INCDIR = ../../../src
INCLUDEPATH += $$INCDIR
HEADERS += $$INCDIR/dbmanager.h
SOURCES += $$INCDIR/dbmanager.cpp

SOURCES += tst_dbmanager.cpp
