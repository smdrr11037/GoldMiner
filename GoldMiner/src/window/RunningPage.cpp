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
    hookLabel->setGeometry(1200, 460, hookImage.width(), hookImage.height());


    // 创建金块显示标签
    QString imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/Bgold_block.gif";
    QPixmap goldImage(imagePath);
    blocksLabel = new QLabel(this);
    blocksLabel->setPixmap(goldImage);
    int x_position = 1200, y_position = 1000;
    blocksLabel->setGeometry(x_position, y_position, goldImage.width(), goldImage.height());  // 设置金块标签的位置和大小

    // 创建分数显示标签  
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setStyleSheet("font-family: Arial; font-size: 40px; font-weight: bold; color: white;");

    // 创建过关目标显示标签  实际需要传入当前level的难度对应目标分数
    targetLabel = new QLabel("Target Points: 100", this);
    targetLabel->setStyleSheet("font-family: Arial; font-size: 40px; font-weight: bold; color: white;");

    // 创建退出按钮  
    exitButton = new QPushButton("Exit Game", this);
    exitButton->setStyleSheet("background-color: white; color: black; font-weight: bold;font-family: Arial; font-size: 40px; border-radius: 50px; padding: 30px 100px;");

    // 连接退出按钮的点击信号到槽函数  
    connect(exitButton, &QPushButton::clicked, this, &RunningPage::exitButtonClicked);

    // 创建布局管理器  
    layout = new QVBoxLayout(this);
    layout->addWidget(scoreLabel);
    layout->addWidget(targetLabel);
    layout->addStretch(1);  // 添加一个弹簧，将按钮推到底部  
    layout->addWidget(exitButton, 0, Qt::AlignCenter);  // 将按钮放在布局的底部并水平居中

    //connect(this, &RunningPage::testSignal, this, &RunningPage::refreshPage);
}

void RunningPage::exitButtonClicked()
{
    // 发射信号，通知游戏退出  
    emit exitGame(GameState::Start);
}

//TODO : 线的实现（Hook的getIsExtending()方法）
void RunningPage::refreshPage(const std::vector<Block>& blocks, const Hook& hook, const Player& player)
{
    // 更新金块和石块的显示  
    for (const auto& block : blocks) {
        // 根据 block 的信息，创建相应的 QLabel 并设置位置、大小和图片  
        QLabel* blockLabel = new QLabel(this);
        if (block.isGoldBlock()) {
            QString blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/Bgold_block.gif";
            QPixmap blockImage(blockImagePath); // 假设 Block 类有一个 getImagePath 函数来获取图片路径  
            blockLabel->setPixmap(blockImage);
            blockLabel->setGeometry(block.getPosition().x, block.getPosition().y, blockImage.width(), blockImage.height());
        }
        else {
            QString blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/Bstone.png";
            QPixmap blockImage(blockImagePath); // 假设 Block 类有一个 getImagePath 函数来获取图片路径  
            blockLabel->setPixmap(blockImage);
            blockLabel->setGeometry(block.getPosition().x, block.getPosition().y, blockImage.width(), blockImage.height());
        }
        
    }

    // 更新爪子显示  
    // 假设 Hook 类有一个 getImagePath 函数来获取爪子图片路径，getAngle 函数来获取爪子角度，getXPosition 和 getYPosition 函数来获取爪子位置  
    QString hookImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/hook.png";
    QPixmap hookImage(hookImagePath);
    hookLabel->setPixmap(hookImage);
    hookLabel->setGeometry(hook.getPosition().x, hook.getPosition().y, hookImage.width(), hookImage.height());

    // 用 QTransform 实现爪子的旋转
    QTransform transform;
    transform.translate(hookImage.width() / 2, hookImage.height() / 2); // 设置旋转中心点  
    //transform.rotate(hook.getAngle()); // 设置旋转角度  
    hookLabel->setPixmap(hookImage.transformed(transform));

    // 更新游戏状态信息（分数、目标分数等）  
    //scoreLabel->setText("Score: " + QString::number(gameState.getScore())); // 假设 GameState 类有一个 getScore 函数来获取分数  
    //targetLabel->setText("Target Points: " + QString::number(gameState.getTargetScore())); // 假设 GameState 类有一个 getTargetScore 函数来获取目标分数
}

void RunningPage::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Down) {
        // 发射信号通知 app 层按键被按下  
        emit runningPressKey();
        //Debug
        Position p1, p2, p3, pH;
        p1.x = 300;
        p1.y = 1200;
        p2.x = 600;
        p2.y = 1600;
        p3.x = 900;
        p3.y = 1400; 
        pH.x = 1200;
        pH.y = 460;
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
/*
使用 Qt 库中的绘图功能来在 `RunningPage` 里面画直线。你可以通过重写 `paintEvent` 函数来实现这一点。以下是一个简单的示例，展示了如何在 `RunningPage` 中画一条直线：
void RunningPage::paintEvent(QPaintEvent *event)
{
    // 调用基类的 paintEvent 函数
    QWidget::paintEvent(event);

    // 创建绘图对象
    QPainter painter(this);

    // 设置直线的颜色和宽度
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));

    // 画一条直线，起点 (x1, y1)，终点 (x2, y2)
    painter.drawLine(x1, y1, x2, y2);
}
在这个示例中，`paintEvent` 函数用于绘制直线。你可以根据需要设置直线的起点和终点坐标 `(x1, y1)` 和 `(x2, y2)`。当 `RunningPage` 需要重新绘制时，这段代码会被执行。

请确保在 `RunningPage` 类中添加了一个 `paintEvent` 函数的声明，类似于下面这样：

protected:
    void paintEvent(QPaintEvent *event) override;
*/