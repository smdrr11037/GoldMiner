#include "StartPage.h"  
#include <QVBoxLayout>  

StartPage::StartPage(QWidget* parent) : QWidget(parent)
{
    // 设置背景图片  可否在此处实现
 
    // 创建一个圆形按钮  
    //RoundButton* roundButton = new RoundButton("Start Game", this);
    //roundButton->setGeometry(200, 200, 100, 100);  // 设置按钮的位置和大小  
    //roundButton->setStyleSheet("color: black; font-size: 16px;");
    startButton = new QPushButton("Start Game", this);
    startButton->setStyleSheet("background-color: yellow; color: orange;font-weight: bold;font-family: Arial; font-size: 40px; border-radius: 50px; padding: 30px 100px;");
    // 连接按钮的点击信号到槽函数  
    connect(startButton, &QPushButton::clicked, this, &StartPage::startButtonClicked);

    // 创建布局管理器  
    layout = new QVBoxLayout(this);
    layout->addStretch(1);  // 添加一个弹簧，将按钮推到底部  
    layout->addWidget(startButton, 0.5, Qt::AlignCenter);  // 将按钮放在布局的底部并水平居中
}


void StartPage::startButtonClicked()
{
    // 发射信号，将游戏状态切换为 Running  
    emit startGame();
}