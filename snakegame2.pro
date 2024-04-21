QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = SnakeGame
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    glwidget.cpp \
    mainwindow.cpp

HEADERS += \
    glwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
