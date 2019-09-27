#-------------------------------------------------
#
# Project created by QtCreator 2017-06-17T20:52:36
#
#-------------------------------------------------

QT       += core gui
RC_ICONS = programicon.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = airport
CONFIG += console
CONFIG -=app bundle
TEMPLATE = app

SOURCES += \
    MAIN_PROGRAM.cpp \
    PRGRAM_SIMULATION.cpp \
    PROGRAM_CONFIGURATION.cpp \
    PROGRAM_IO.cpp \
    PROGRAM_LINEANDWINDOW_SCAN.cpp \
    PROGRAM_MAIN_PROCESS.cpp \
      widget.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    PRGRAM_SIMULATION.h \
    PROGRAM_BASIC_ACTION.h \
    PROGRAM_CONFIGURATION.h \
    PROGRAM_IO.h \
    PROGRAM_LINEANDWINDOW_SCAN.h \
    PROGRAM_MAIN_PROCESS.h \
      widget.h
FORMS += \
        widget.ui
