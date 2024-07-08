#include "MainWindow.h"  
#include <QVBoxLayout>
#include <QMainWindow>  
#include<QDebug>    //debug

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);

    startPage = new StartPage(this);
    runningPage = new RunningPage(this);
    completePage = new CompletePage(this);
    gameOverPage = new GameOver(this);
    
    // 将窗口部件添加到 stacked widget 中  对应index为0, 1, 2, 3
    stackedWidget->addWidget(startPage);
    stackedWidget->addWidget(runningPage);
    stackedWidget->addWidget(completePage);
    stackedWidget->addWidget(gameOverPage);

    //显示开始界面
    stackedWidget->setCurrentIndex(0);
    this->resize(1024, 1024);
    this->setWindowTitle("Gold Miner Initial Start");
    setCentralWidget(stackedWidget);
    /*
    另一种相对路径set方式：
    QDir::setCurrent(QCoreApplication::applicationDirPath()+"/../../../GoldMiner/src/window");
    QString imagePath = "./image/start_background.jpg";
    */
    QString imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/start_background.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");

    // 连接 StartPage 的 startGame 信号到 MainWindow 的槽函数  
    connect(startPage, &StartPage::startGame, this, &MainWindow::handleStartButtonClicked);

    // 连接 RunningPage 的 exitGame 信号到 MainWindow 的槽函数  
    connect(runningPage, &RunningPage::exitGame, this, &MainWindow::handleExitButtonClicked);

    // 连接 Complete 的 nextLevel 信号到 MainWindow 的槽函数  
    connect(completePage, &CompletePage::nextLevel, this, &MainWindow::handleNextLevelButtonClicked);

    // 连接 GameOver 的 Replay 信号到 MainWindow 的槽函数  
    connect(gameOverPage, &GameOver::replay, this, &MainWindow::handlePlayAgainButtonClicked);

    connect(runningPage, &RunningPage::runningPressKey, this, &MainWindow::handlePressKey);
}

MainWindow::~MainWindow() {
    if (startPage) {
        delete startPage;
        startPage = nullptr;
    }
    if (runningPage) {
        delete runningPage;
        runningPage = nullptr;
    }
    if (completePage) {
        delete completePage;
        completePage = nullptr;
    }
}

// 处理“开始”按钮点击的槽函数  
void MainWindow::handleStartButtonClicked()
{
    /*
    this->move(500, 100);
    this->resize(2527, 1862);
    this->setWindowTitle("Running");
    stackedWidget->setCurrentIndex(1);
    QString imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/back2527x1862.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
    */
    // 发射信号通知 app 层,通知已改变状态完成  
    emit startGame();
}

// 处理 游戏中“退出”按钮点击的槽函数  
void MainWindow::handleExitButtonClicked()
{
    /*
    this->move(1250, 500);
    this->resize(1100, 799);
    this->setWindowTitle("This Level Victory");
    stackedWidget->setCurrentIndex(2);

    QString imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/victory_background.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
    */
    /*this->resize(1024, 1024);
    this->setWindowTitle("Gold Miner Start");
    //暂定直接返回开始界面
    setCentralWidget(startPage);
    QString imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/start_background.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
    */
    // 发射信号通知 viewmodel 层  
    emit exitGame();

}

// 处理 游戏结束后comp界面“下一关”按钮点击后，进入下一关RunningPage的槽函数  
void MainWindow::handleNextLevelButtonClicked()
{
    /*
    this->move(500, 100);
    this->resize(2527, 1862);
    this->setWindowTitle("Next Level Running");
    stackedWidget->setCurrentIndex(1);

    QString imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/back2527x1862.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
    */
    // 发射信号通知 viewmodel 层  
    emit nextLevel();
}

// 处理 游戏失败后comp界面“重玩”按钮点击后，进入上一关RunningPage的槽函数  
void MainWindow::handlePlayAgainButtonClicked()
{
    /*
    this->move(500, 100);
    this->resize(2527, 1862);
    this->setWindowTitle("Play Again Running");
    stackedWidget->setCurrentIndex(1);

    QString imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/back2527x1862.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
    */
    // 发射信号通知 viewmodel 层  
    emit playAgain();
}

void MainWindow::handlePressKey()
{
    emit pressKey();
}

//切帧
void MainWindow::updateState(const std::vector<Block>& blocks, const Hook& hook, const Player& player)
{
    runningPage->refreshPage(blocks, hook, player);
}

//需要切换页面的信号
void MainWindow::updatePage(const GameState& gameState)
{
    QString imagePath;
    switch (gameState)
    {
    case(GameState::Start):
        this->resize(1024, 1024);
        this->setWindowTitle("Gold Miner Initial Start");
        stackedWidget->setCurrentIndex(0);
        imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/start_background.jpg";
        setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
        break;
    case(GameState::Running):
        this->move(500, 100);
        this->resize(2527, 1862);
        this->setWindowTitle("Running");
        stackedWidget->setCurrentIndex(1);
        imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/back2527x1862.jpg";
        setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
        break;
    case(GameState::GameOver):
        this->move(1250, 500);
        this->resize(1100, 799);
        this->setWindowTitle("Game Over");
        stackedWidget->setCurrentIndex(3);
        imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/victory_background.jpg";
        setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
        break;
    case(GameState::Win):
        this->move(1250, 500);
        this->resize(1100, 799);
        this->setWindowTitle("This Level Victory");
        stackedWidget->setCurrentIndex(2);
        imagePath = QCoreApplication::applicationDirPath() + "/../../../GoldMiner/src/window/image/victory_background.jpg";
        setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
        break;
    }
}