QT += core
QT -= gui

TARGET = shipsserver
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
        main.cpp \
        shipsserver.cpp \
    gamedata.cpp \
    ship.cpp \
    game.cpp \
    status.cpp

include(./REST/REST.pri)

HEADERS += \
        shipsserver.h \
    gamedata.h \
    ship.h \
    game.h \
    status.h



