// startupmenu.cpp
#include "startupmenu.h"

StartupMenu::StartupMenu(QWidget *parent) : QWidget(parent)
{
    startButton = new QPushButton("Start Game", this);
    connect(startButton, &QPushButton::clicked, this, &StartupMenu::on_startButton_clicked);

    imageLabel = new QLabel(this);
    QPixmap image("C:/Users/JOSHU/Documents/Projects/CSE165Project/Assests/SnakeStartScreen.png"); // Replace ":/images/startup_image.png" with the path to your image file
    imageLabel->setPixmap(image);
    imageLabel->setAlignment(Qt::AlignCenter); // Center the image within the label
    imageLabel->setPixmap(image.scaled(imageLabel->size(), Qt::KeepAspectRatio));

}

void StartupMenu::on_startButton_clicked()
{
    emit startGameClicked();
}
