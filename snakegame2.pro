QT += core gui opengl widgets openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -lOpengl32

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
