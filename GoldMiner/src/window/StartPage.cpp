#include "StartPage.h"  
#include <QVBoxLayout>  

StartPage::StartPage(CounterViewModel* viewModel, QWidget* parent) : QWidget(parent), m_viewModel(viewModel)
{
    // 设置背景图片  
    //setStyleSheet("QWidget { background-image: url(:/background.jpg); }");
    QString imagePath = "image/start_background.jpg";
    setStyleSheet("QWidget { background-image: url(" + imagePath + "); }");

    // 创建开始游戏按钮  
    startButton = new QPushButton("开始游戏", this);

    // 连接按钮的点击信号到槽函数  
    connect(startButton, &QPushButton::clicked, this, &StartPage::startGame);

    // 创建布局管理器  
    layout = new QVBoxLayout(this);
    layout->addWidget(startButton);
}


void StartPage::startButtonClicked()
{
    // 发射信号，将游戏状态切换为 Running  
    emit startGame(GameState::Running);
}