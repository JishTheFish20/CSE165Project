#include "startupmenu.h"
#include <QUrl>

StartupMenu::StartupMenu(QWidget *parent) : QWidget(parent)
{
    startButton = new QPushButton("Start Game", this);
    connect(startButton, &QPushButton::clicked, this, &StartupMenu::on_startButton_clicked);

    imageLabel = new QLabel(this);
    QPixmap image("qrc:/images/Assests/SnakeStartScreen.png");
    imageLabel->setPixmap(image);
    imageLabel->setAlignment(Qt::AlignCenter); // Center the image within the label

    // Adjust size of image label to fit the image
    imageLabel->setFixedSize(image.size());
}

void StartupMenu::on_startButton_clicked()
{
    emit startGameClicked();
}
