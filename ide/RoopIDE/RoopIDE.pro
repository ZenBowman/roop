#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T18:38:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoopIDE
TEMPLATE = app


SOURCES += main.cpp\
        roopenvironment.cpp \
    roopsyntaxhighlighter.cpp \
    syntaxkeywords.cpp \
    roopcommon.cpp

HEADERS  += roopenvironment.h \
    roopsyntaxhighlighter.h \
    roopconstants.h \
    syntaxkeywords.h \
    roopcommand.h \
    roopcommon.h

FORMS    += roopenvironment.ui
QMAKE_CXXFLAGS += -std=c++11
