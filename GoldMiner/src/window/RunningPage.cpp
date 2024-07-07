#include "RunningPage.h"  
#include <QVBoxLayout>  
#include <QPixmap>

RunningPage::RunningPage(QWidget* parent) : QWidget(parent)
{
    // 设置背景图片  可否在此处实现
    
    // 创建金块显示标签
    QString imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/gold_block.png";  // Assuming the image is in the src/images directory  
    QPixmap goldImage(imagePath);
    blocksLabel = new QLabel(this);
    blocksLabel->setPixmap(goldImage);
    int x_position = 10, y_position = 100;
    blocksLabel->setGeometry(x_position, y_position, goldImage.width(), goldImage.height());  // 设置金块标签的位置和大小
    // 创建分数显示标签  
    scoreLabel = new QLabel("Score: 0", this);

    // 创建过关目标显示标签  实际需要传入当前level的难度对应目标分数
    targetLabel = new QLabel("Target Points: 100", this);

    // 创建退出按钮  
    exitButton = new QPushButton("Exit Game", this);
    exitButton->setStyleSheet("background-color: white; color: black; border-radius: 50px; padding: 10px 20px;");

    // 连接退出按钮的点击信号到槽函数  
    QObject::connect(exitButton, &QPushButton::clicked, this, &RunningPage::exitButtonClicked);

    // 创建布局管理器  
    layout = new QVBoxLayout(this);
    layout->addWidget(scoreLabel);
    layout->addWidget(targetLabel);
    layout->addStretch(1);  // 添加一个弹簧，将按钮推到底部  
    layout->addWidget(exitButton, 0, Qt::AlignCenter);  // 将按钮放在布局的底部并水平居中
}

void RunningPage::exitButtonClicked()
{
    // 发射信号，通知游戏退出  
    emit exitGame(GameState::Start);
}

/*
    如果有很多个金块需要显示，你可以考虑使用列表或数组来管理它们。
    在这种情况下，你可以创建多个 QLabel 来显示金块的图片，并将它们添加到布局管理器中以确保它们正确地显示在页面上。
以下是一个示例代码，演示了如何在 RunningPage 中显示多个金块：
RunningPage::RunningPage(QWidget* parent) : QWidget(parent)  
{  
    // 创建金块显示标签  
    // 假设你有一个表示金块位置的坐标数组 goldBlockPositions，以及金块图片的路径 goldBlockImagePath  
    for(const auto& position : goldBlockPositions) {  
        QLabel* goldBlockLabel = new QLabel(this);  
        QPixmap goldImage(goldBlockImagePath);  
        goldBlockLabel->setPixmap(goldImage);  
        goldBlockLabel->setGeometry(position.x, position.y, width, height);  // 设置金块标签的位置和大小  
        layout->addWidget(goldBlockLabel);  // 将金块标签添加到布局管理器中  
    }  
   
    // 创建分数显示标签  
    scoreLabel = new QLabel("Score: 0", this);  
    // ...   
}  
在这个示例中，假设 `goldBlockPositions` 是一个包含金块位置的数组，`goldBlockImagePath` 是金块图片的路径。通过循环遍历这些位置，你可以创建多个 QLabel 并将它们添加到布局管理器中，以便它们能够在页面上正确显示。
*/