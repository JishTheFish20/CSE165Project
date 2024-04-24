QT += core gui opengl widgets openglwidgets

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
    SpeedFood.h \
    food.h \
    glwidget.h \
    mainwindow.h \
    snake.h \
    startupmenu.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    Assests/SnakeStartScreen.png
