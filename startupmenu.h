// startupmenu.h
#ifndef STARTUPMENU_H
#define STARTUPMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class StartupMenu : public QWidget
{
    Q_OBJECT
public:
    explicit StartupMenu(QWidget *parent = nullptr);

signals:
    void startGameClicked();

private:
    QPushButton *startButton;
    QLabel *imageLabel; // QLabel to display the image

private slots:
    void on_startButton_clicked();
};

#endif // STARTUPMENU_H
