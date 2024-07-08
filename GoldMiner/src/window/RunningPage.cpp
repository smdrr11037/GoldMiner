#include "RunningPage.h"  
#include <QVBoxLayout>  
#include <QPixmap>

RunningPage::RunningPage(QWidget* parent) : QWidget(parent)
{
    // 设置背景图片  可否在此处实现
    
    // 创建夹子显示标签
    QString hookImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/hook.png";
    QPixmap hookImage(hookImagePath);
    hookLabel = new QLabel(this);
    hookLabel->setPixmap(hookImage);
    hookLabel->setGeometry(OX- hookImage.width()/2, OY, hookImage.width(), hookImage.height());


    // 创建金块显示标签
    QString imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/newgold.png";
    QPixmap goldImage(imagePath);
    blocksLabel = new QLabel(this);
    blocksLabel->setPixmap(goldImage);
    int x_position = 1200, y_position = 1000;
    blocksLabel->setGeometry(x_position, y_position, goldImage.width(), goldImage.height());  // 设置金块标签的位置和大小

    // 创建分数显示标签  
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setStyleSheet("font-family: Arial; font-size: 50px; font-weight: bold; color: black;");

    // 创建过关目标显示标签  实际需要传入当前level的难度对应目标分数
    targetLabel = new QLabel("Target Points: 100", this);
    targetLabel->setStyleSheet("font-family: Arial; font-size: 50px; font-weight: bold; color: black;");

    timeLabel = new QLabel("Time: 60 s", this);
    timeLabel->setStyleSheet("font-family: Arial; font-size: 50px; font-weight: bold; color: black;");

    // 创建退出按钮  
    exitButton = new QPushButton("Exit Game", this);
    exitButton->setStyleSheet("background-color: white; color: black; font-weight: bold;font-family: Arial; font-size: 40px; border-radius: 50px; padding: 30px 100px;");

    // 连接退出按钮的点击信号到槽函数  
    connect(exitButton, &QPushButton::clicked, this, &RunningPage::exitButtonClicked);

    // 创建布局管理器  
    layout = new QVBoxLayout(this);
    layout->addWidget(scoreLabel);
    layout->addWidget(targetLabel);
    layout->addWidget(timeLabel);
    layout->addStretch(1);  // 添加一个弹簧，将按钮推到底部  
    layout->addWidget(exitButton, 0, Qt::AlignCenter);  // 将按钮放在布局的底部并水平居中

    //connect(this, &RunningPage::testSignal, this, &RunningPage::refreshPage);
    startPoint = QPoint(OX, OY-65);
    endPoint = QPoint(OX, OY);
    // 调用 update() 函数触发重绘  
    update();
}

void RunningPage::exitButtonClicked()
{
    // 发射信号，通知游戏退出  
    emit exitGame(GameState::Start);
}

//TODO : 线的实现（Hook的getIsExtending()方法）
void RunningPage::refreshPage(const std::vector<Block>& blocks, const Hook& hook, const Player& player)
{
    // BLOCK
    for (const auto& block : blocks) {
        // 根据 block 的信息，创建相应的 QLabel 并设置位置、大小和图片  
        QLabel* blockLabel = new QLabel(this);
        if (block.isGoldBlock()) {
            QString blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/Bgold_block.gif";
            QPixmap blockImage(blockImagePath); // 假设 Block 类有一个 getImagePath 函数来获取图片路径  
            blockLabel->setPixmap(blockImage);
            blockLabel->setGeometry(OX +block.getPosition().x, OY +block.getPosition().y, blockImage.width(), blockImage.height());
        }
        else {
            QString blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/Bstone.png";
            QPixmap blockImage(blockImagePath); // 假设 Block 类有一个 getImagePath 函数来获取图片路径  
            blockLabel->setPixmap(blockImage);
            blockLabel->setGeometry(OX +block.getPosition().x, OY +block.getPosition().y, blockImage.width(), blockImage.height());
        }
        
    }

    // HOOK 
    QString hookImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/hook.png";
    QPixmap hookImage(hookImagePath);
    hookLabel->setPixmap(hookImage);
    hookLabel->setGeometry(OX +hook.getPosition().x, OY +hook.getPosition().y, hookImage.width(), hookImage.height());
    if (hook.getIsExtending() == false) {
        // 用 QTransform 实现爪子的旋转
        QTransform transform;
        transform.translate(hookImage.width() / 2, 0); // 设置旋转中心点   
        transform.rotate(hook.getAngle()); // 设置旋转角度  
        hookLabel->setPixmap(hookImage.transformed(transform));
    }
    else {
        // 需要旋转
        QTransform transform;
        transform.translate(hookImage.width() / 2, 0); // 设置旋转中心点 
        transform.rotate(hook.getAngle()); // 设置旋转角度  
        hookLabel->setPixmap(hookImage.transformed(transform));
        // 画绳子，原点：1200， 460
        startPoint = QPoint(OX, OY);
        endPoint = QPoint(OX + hook.getPosition().x, OY + hook.getPosition().y);
        // 调用 update() 函数触发重绘  
        update();
    }

    // PLAYER
    scoreLabel->setText("Score: " + QString::number(player.getScore())); // 假设 GameState 类有一个 getScore 函数来获取分数  
    targetLabel->setText("Target Points: " + QString::number(player.getTargetScore())); // 假设 GameState 类有一个 getTargetScore 函数来获取目标分数
    timeLabel->setText("Time: " + QString::number(player.getTargetScore())+" s");
}

void RunningPage::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Down) {
        // 发射信号通知 app 层按键被按下  
        emit runningPressKey();
        //Debug
        Position p1(300,1200), p2(600,1600), p3(900,1400), pH(1200,460);
        std::vector<Block> initialBlocks = { Block(true, 0, 0, p1), Block(false, 0, 0, p2), Block(true, 0, 0, p3) };
        // 使用引用来绑定到这个向量  
        std::vector<Block>& blocks = initialBlocks;
        Hook hook = Hook(pH);
        GameState gameState = GameState::Running;
        //emit testSignal(blocks, hook, gameState);
        //refreshPage(blocks, hook, gameState);
    }
    
    //QWidget::keyPressEvent(event);  // 调用基类的事件处理函数  
}

// 重写 QWidget 的 paintEvent 函数  
void RunningPage::paintEvent(QPaintEvent* event)
{
    // 首先调用父类的 paintEvent  
    QWidget::paintEvent(event);

    // 创建绘图对象  
    QPainter painter(this);

    // 设置线条样式  
    painter.setPen(QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap));

    // 画线  
    painter.drawLine(startPoint, endPoint);
}