TEMPLATE = app
TARGET = snakegame2
CONFIG += c++17
CONFIG += qt

QT += core gui widgets opengl

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    glwidget.cpp

HEADERS += \
    mainwindow.h \
    glwidget.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

# Define any additional libraries needed
LIBS += -lGL
