#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr);
private:
    GLWidget *glWidget;
};

#endif // MAINWINDOW_H
