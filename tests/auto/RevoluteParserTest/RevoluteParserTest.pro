QT = core testlib

TARGET = tst_revolute_parser
TEMPLATE = app
CONFIG += qt warn_on depend_includepath testcase

INCDIR = ../../../src
INCLUDEPATH += $$INCDIR
HEADERS += $$INCDIR/transaction_parser.h
SOURCES += $$INCDIR/transaction_parser.cpp

SOURCES += tst_revolute_parser.cpp
