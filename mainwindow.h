#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QApplication>


class GLWidget;
class StartupMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int width, height;
    QLabel *speedLabel; // Declare a pointer to QLabel
    QLabel *scoreCounter;

private:
    GLWidget *glWidget;
    StartupMenu *startupMenu;

private slots:
    void startGame();
};

#endif // MAINWINDOW_H
