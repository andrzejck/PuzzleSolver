#-------------------------------------------------
#
# Project created by QtCreator 2020-01-10T22:56:16
#
#-------------------------------------------------

QT       += widgets core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Puzzle
TEMPLATE = app
#CONFIG += c++1z
QMAKE_CXXFLAGS += -std=c++1z

SOURCES += main.cpp\
        mainwindow.cpp \
    puzzle.cpp \
    point.cpp \
    Segment.cpp

HEADERS  += mainwindow.h \
    puzzle.h \
    point.h \
    Segment.h

FORMS    += mainwindow.ui
