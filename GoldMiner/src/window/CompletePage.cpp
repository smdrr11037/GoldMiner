#include "CompletePage.h"  
#include <QVBoxLayout>  

CompletePage::CompletePage(QWidget* parent) : QWidget(parent)
{
    // 设置背景图片  
    QString imagePath = "image/victory_background.jpg"; // 假设这是胜利页面的背景图片路径  
    setStyleSheet("QWidget { background-image: url(" + imagePath + "); }");

    // 创建显示游戏胜利画面的标签  
    victoryImageLabel = new QLabel(this);
    // 设置胜利画面图片  
    QPixmap victoryImage("image/victory_image.png"); // 假设这是胜利画面的图片路径  
    victoryImageLabel->setPixmap(victoryImage);
    victoryImageLabel->setAlignment(Qt::AlignCenter);

    // 创建进入下一关按钮  
    nextLevelButton = new QPushButton("下一关", this);

    // 连接按钮的点击信号到槽函数  
    connect(nextLevelButton, &QPushButton::clicked, this, &CompletePage::nextLevelButtonClicked);

    // 创建布局管理器  
    layout = new QVBoxLayout(this);
    layout->addWidget(victoryImageLabel);
    layout->addWidget(nextLevelButton);
}

void CompletePage::nextLevelButtonClicked()
{
    // 发射信号，通知进入下一关  
    emit nextLevel();
}