#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    glWidget = new GLWidget(this);
    setCentralWidget(glWidget);
}
