#include "mainwindow.h"
#include "glwidget.h"
#include"startupmenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    startupMenu = new StartupMenu(this); // Create an instance of the startup menu
    setCentralWidget(startupMenu); // Set the startup menu as the central widget

    connect(startupMenu, &StartupMenu::startGameClicked, this, &MainWindow::startGame); // Connect startGameClicked signal to startGame slot

    // width = 1000;
    // height = 1000;
    // setFixedSize(width,height);
}

void MainWindow::startGame()
{
    glWidget = new GLWidget(this);

    setCentralWidget(glWidget);
    setWindowTitle("Snake Game");
    glWidget->show();
}

MainWindow::~MainWindow()
{
    delete glWidget;
}
