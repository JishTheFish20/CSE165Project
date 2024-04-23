#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int width, height;
    QLabel *speedLabel; // Declare a pointer to QLabel

private:
    GLWidget *glWidget;
};

#endif // MAINWINDOW_H
