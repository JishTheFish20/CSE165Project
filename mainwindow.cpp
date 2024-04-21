#include "mainwindow.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    glWidget = new GLWidget(this);
    setCentralWidget(glWidget);
}

MainWindow::~MainWindow()
{
    delete glWidget;
}
