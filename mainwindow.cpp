#include "mainwindow.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    glWidget = new GLWidget(this);
    setCentralWidget(glWidget);
    setWindowTitle("Snake Game");
    glWidget->show();

    // width = 1000;
    // height = 1000;
    // setFixedSize(width,height);
}

MainWindow::~MainWindow()
{
    delete glWidget;
}
