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
LIBS +=  -lboost_serialization\
        -lboost_unit_test_framework\
        -lboost_system \
        -lboost_iostreams \
        -lboost_thread \
        -lboost_log



SOURCES +=  point.cpp \
    PuzzleOnBoard.cpp \
    LayoutCacheImage.cpp \
    PointOfEnvelope.cpp  \
    Segment.cpp \
    Layout.cpp   \
    Polygon.cpp   \
    SegmentOfEnvelope.cpp  \
    main.cpp  \
    puzzle.cpp \
    test.cpp  \
    mainwindow.cpp  \
    PuzzleList.cpp  \
    Vector.cpp

HEADERS  +=  point.h \
    PuzzleList.h \
    ui_mainwindow.h \
    LayoutCacheImage.h \
    PointOfEnvelope.h \
    PuzzleOnBoard.h  \
    Vector.h \
    Layout.h \
    Polygon.h \
    Segment.h \
    mainwindow.h \
    puzzle.h \
    SegmentOfEnvelope.h \
    CIniFile.h


FORMS    += mainwindow.ui
