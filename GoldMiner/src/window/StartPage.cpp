#include "StartPage.h"  
#include <QVBoxLayout>  

StartPage::StartPage(QWidget* parent) : QWidget(parent)
{
    // 设置背景图片  
    /*QString imagePath = "D:/Assignment/Grade2.2/c++/GoldMiner/GoldMiner/src/window/image/start_background.jpg";
    setStyleSheet("QWidget { background-image: url(" + imagePath + "); background-size: cover; }");*/

    // 创建开始游戏按钮  
    startButton = new QPushButton("Start Game", this);

    // 连接按钮的点击信号到槽函数  
    connect(startButton, &QPushButton::clicked, this, &StartPage::startButtonClicked);

    // 创建布局管理器  
    layout = new QVBoxLayout(this);
    layout->addWidget(startButton);
}


void StartPage::startButtonClicked()
{
    // 发射信号，将游戏状态切换为 Running  
    emit startGame(GameState::Running);
}