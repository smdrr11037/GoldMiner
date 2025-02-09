#include "RunningPage.h"  
#include <QVBoxLayout>  
#include <QPixmap>

RunningPage::RunningPage(QWidget* parent) : QWidget(parent)
{
    // SWEAT
    QString sweatImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/sweat.png";;
    QPixmap sweatImage(sweatImagePath);
    sweatLabel = new QLabel(this);
    sweatLabel->setPixmap(sweatImage);
    sweatLabel->setGeometry(OX + 135, OY - 240, sweatImage.width(), sweatImage.height());
    sweatLabel->hide();

    // HOOK
    QString hookImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/hook.png";
    QPixmap hookImage(hookImagePath);
    hookLabel = new QLabel(this);
    hookLabel->setPixmap(hookImage);
    hookLabel->setGeometry(HOOK_OX, HOOK_OY, hookImage.width(), hookImage.height());
    QTransform transform;
    transform.translate(0, 0); // 设置旋转中心点   
    transform.rotate(0); // 设置旋转角度  
    hookLabel->setPixmap(hookImage.transformed(transform));
    
    //SCORE
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setStyleSheet("font-family: Arial; font-size: 50px; font-weight: bold; color: black;");

    //GOAL  实际需要传入当前level的难度对应目标分数
    targetLabel = new QLabel("Target Points: 100", this);
    targetLabel->setStyleSheet("font-family: Arial; font-size: 50px; font-weight: bold; color: red;");

    timeLabel = new QLabel("Time: 60 s", this);
    timeLabel->setStyleSheet("font-family: Arial; font-size: 50px; font-weight: bold; color: black;");

    //BUTTON  
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

    //ROPE
    startPoint = QPoint(OX, OY-65);
    endPoint = QPoint(OX, OY);
    // 调用 update() 函数触发重绘  
    update();
    //键盘响应绑定
    setFocusPolicy(Qt::StrongFocus);
}

void RunningPage::exitButtonClicked()
{
    // 发射信号，通知游戏退出  
    emit exitGame();
}

void RunningPage::clearBlocks() {
    for (auto& blockLabel : displayedBlocks) {
        blockLabel->hide();  // 隐藏 QLabel  
        blockLabel->deleteLater();  // 释放 QLabel 对象  
    }
    displayedBlocks.clear();  // 清空存储的 QLabel  
}

void RunningPage::refreshPage()
{
    //先擦除上次显示的金块
    const std::vector<Block>& blocks = *m_gameData->blockVector;
    const Hook& hook = *m_gameData->hook;
    const Player& player = *m_gameData->player;
    this->clearBlocks();
    // BLOCK
    for (const auto& block : blocks) {
        // 根据 block 的信息，创建相应的 QLabel 并设置位置、大小和图片  
        QLabel* blockLabel = new QLabel(this);
        QString blockImagePath;
        if (block.isGoldBlock()) {
            switch (int(block.getSize()))
            {
            case int(SMALL_GOLD):
                blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/Sgold_block.gif";
                break;
            case int(MIDDLE_GOLD):
                blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/newgold.png";
                break;
            case int(BIG_GOLD):
                blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/Bgold_block.gif";
                break;
            default:
                blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/newgold.png";
                break;
            }
        }
        else {
            switch (int(block.getSize()))
            {
            case int(SMALL_STONE):
                blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/Sstone.png";
                break;
            case int(MIDDLE_STONE):
                blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/newstone.png";
                break;
            case int(BIG_STONE):
                blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/Bstone.png";
                break;
            default:
                blockImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/newstone.png";
                break;
            }
        }
        QPixmap blockImage(blockImagePath); 
        blockLabel->setPixmap(blockImage);
        blockLabel->setGeometry(OX + block.getPosition().x - blockImage.width() / 2, OY + block.getPosition().y - blockImage.height() / 2, blockImage.width(), blockImage.height());
        blockLabel->show();
        displayedBlocks.push_back(blockLabel);  // 存储这些 QLabel，以便稍后清除
    }

    // HOOK 
    rotationAngle = hook.getAngle();
    QString hookImagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/hook.png";
    QPixmap hookImage(hookImagePath);
    int w = hookImage.width();
    int h = hookImage.height();
    // 创建一个新的QPixmap，用于旋转后的图像  
    QPixmap rotatedPixmap(w, h);
    rotatedPixmap.fill(Qt::transparent);
    QPainter painter(&rotatedPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 将绘图原点平移到钩子末端  
    painter.translate(w/2, h / 4);
    // 进行旋转  
    painter.rotate(rotationAngle);
    // 将绘图原点移回到左上角  
    painter.translate(-w / 2, -h / 4);
    // 绘制旋转后的图像  
    painter.drawPixmap(0, 0, hookImage);
    painter.end();
    hookLabel->setPixmap(rotatedPixmap);
    hookLabel->setGeometry(HOOK_OX + hook.getPosition().x, HOOK_OY + hook.getPosition().y, w, h);

    //ROPE
    startPoint = QPoint(OX, OY - 65);
    endPoint = QPoint(OX + hook.getPosition().x, OY + hook.getPosition().y);
    update();

    // PLAYER
    scoreLabel->setText("Level: "+ QString::number(player.getLevel())+"   Score: " + QString::number(player.getScore()));
    targetLabel->setText("Target Points: " + QString::number(player.getTargetScore()));
    timeLabel->setText("Time: " + QString::number(player.getTime())+" s");

    // SWEAT
    if (hook.getIsCatch()) {
        sweatLabel->show();
    }
    else {
        sweatLabel->hide();
    }
}

void RunningPage::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Down) {
        // 发射信号通知 app 层按键被按下  
        emit runningPressKey();
        //Debug
        /*
        Position p1(100,200), p2(-450,400), p3(0,850), pH(10,10);
        std::vector<Block> initialBlocks = { Block(true, 0, 0, p1), Block(false, 0, 0, p2), Block(true, 0, 0, p3) };
        // 使用引用来绑定到这个向量  
        std::vector<Block>& blocks = initialBlocks;
        Hook hook = Hook(pH, 45);
        hook.startExtending();
        Player player = Player(0, 20, 1, 10000);
        //emit testSignal(blocks, hook, player);
        this->refreshPage(blocks, hook, player);
        */
    }
    /*
    if (event->key() == Qt::Key_Up) {
        // 发射信号通知 app 层按键被按下  
        emit runningPressKey();
        //Debug
        Position p1(150, 250), p2(-350, 600), p3(850, 850), pH(200, 200);
        std::vector<Block> initialBlocks = { Block(true, 0, 0, p1), Block(false, 0, 0, p2), Block(true, 0, 0, p3) };
        // 使用引用来绑定到这个向量  
        std::vector<Block>& blocks = initialBlocks;
        Hook hook = Hook(pH, 45);
        //hook.startExtending();
        Player player = Player(0, 10, 1, 10000);
        //emit testSignal(blocks, hook, player);
        this->refreshPage(blocks, hook, player);
    }
    if (event->key() == Qt::Key_Right) {
        // 发射信号通知 app 层按键被按下  
        emit runningPressKey();
        //Debug
        Position p1(150, 250), p2(-350, 600), p3(850, 850), pH(300, 300);
        std::vector<Block> initialBlocks = { Block(true, 0, 0, p1), Block(false, 0, 0, p2), Block(true, 0, 0, p3) };
        // 使用引用来绑定到这个向量  
        std::vector<Block>& blocks = initialBlocks;
        Hook hook = Hook(pH, 45);
        //hook.startExtending();
        Player player = Player(0, 10, 1, 10000);
        //emit testSignal(blocks, hook, player);
        this->refreshPage(blocks, hook, player);
    }
    if (event->key() == Qt::Key_Left) {
        // 发射信号通知 app 层按键被按下  
        emit runningPressKey();
        //Debug
        Position p1(150, 250), p2(-350, 600), p3(850, 850), pH(400, 400);
        std::vector<Block> initialBlocks = { Block(true, 0, 0, p1), Block(false, 0, 0, p2), Block(true, 0, 0, p3) };
        // 使用引用来绑定到这个向量  
        std::vector<Block>& blocks = initialBlocks;
        Hook hook = Hook(pH, 135);
        //hook.startExtending();
        Player player = Player(0, 10, 1, 10000);
        //emit testSignal(blocks, hook, player);
        this->refreshPage(blocks, hook, player);
    }
    */
    QWidget::keyPressEvent(event);  // 调用基类的事件处理函数  
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
    
void RunningPage::setGameData(std::shared_ptr<GameData> gameData) {
    // 绑定游戏数据到本页面
    m_gameData = gameData;
}