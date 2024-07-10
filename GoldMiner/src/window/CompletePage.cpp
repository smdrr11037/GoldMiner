#include "CompletePage.h"  
#include <QVBoxLayout>  

CompletePage::CompletePage(QWidget* parent) : QWidget(parent)
{
    // 创建进入下一关按钮  
    nextLevelButton = new QPushButton("Next Level", this);
    nextLevelButton->setStyleSheet("background-color: blue; color: white;font-weight: bold;font-family: Arial; font-size: 40px; border-radius: 50px; padding: 30px 100px;");

    // 连接按钮的点击信号到槽函数  
    connect(nextLevelButton, &QPushButton::clicked, this, &CompletePage::nextLevelButtonClicked);

    // 创建布局管理器  
    layout = new QVBoxLayout(this);
    layout->addStretch(1);  // 添加一个弹簧，将按钮推到底部  
    layout->addWidget(nextLevelButton, 0.8, Qt::AlignCenter);  // 将按钮放在布局的底部并水平居中
}

void CompletePage::nextLevelButtonClicked()
{
    // 发射信号，通知进入下一关  
    emit nextLevel();
}