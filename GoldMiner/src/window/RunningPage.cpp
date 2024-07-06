#include "RunningPage.h"  
#include <QVBoxLayout>  

RunningPage::RunningPage(GameViewModel* viewModel, QWidget* parent) : QWidget(parent), m_viewModel(viewModel)
{
    // 设置背景图片  
    QString imagePath = "image/running_background.jpg"; // 运行页面的背景图片路径  
    setStyleSheet("QWidget { background-image: url(" + imagePath + "); }");

    // 创建分数显示标签  
    scoreLabel = new QLabel("Score: 0", this);

    // 创建过关目标显示标签  实际需要传入当前level的难度对应目标分数
    targetLabel = new QLabel("Target Points: 100", this);

    // 创建退出按钮  
    exitButton = new QPushButton("退出游戏", this);

    // 连接退出按钮的点击信号到槽函数  
    connect(exitButton, &QPushButton::clicked, this, &RunningPage::exitButtonClicked);

    // 创建布局管理器  
    layout = new QVBoxLayout(this);
    layout->addWidget(scoreLabel);
    layout->addWidget(targetLabel);
    layout->addWidget(exitButton);
}

void RunningPage::exitButtonClicked()
{
    // 发射信号，通知游戏退出  
    emit exitGame();
}