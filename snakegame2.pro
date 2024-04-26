QT += core gui opengl widgets openglwidgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -lOpengl32

TARGET = SnakeGame
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

ASSESTS += \
    SnakeStartScreen.png


SOURCES += \
    food.cpp \
    main.cpp \
    glwidget.cpp \
    mainwindow.cpp \
    snake.cpp \
    startupmenu.cpp

HEADERS += \
    SlowFood.h \
    SpeedFood.h \
    TeleportFood.h \
    food.h \
    glwidget.h \
    mainwindow.h \
    snake.h \
    startupmenu.h

FORMS += \
    mainwindow.ui

DISTFILES +=

RESOURCES += \
    Assests.qrc
