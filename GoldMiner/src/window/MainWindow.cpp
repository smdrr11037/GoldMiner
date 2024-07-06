#include "MainWindow.h"  
#include <QVBoxLayout>
#include <QMainWindow>  
#include<QDebug>    //debug

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    startPage = new StartPage(this);
    runningPage = new RunningPage(this);
    completePage = new CompletePage(this);
    
    this->resize(1024, 1024);
    this->setWindowTitle("Gold Miner Initial Start");
    setCentralWidget(startPage);

    QString imagePath = "D:/Assignment/Grade2.2/c++/GoldMiner/GoldMiner/src/window/image/start_background.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
    

    //===================================================================================
    /*this->resize(1100, 799);
    this->setWindowTitle("This Level Victory");
    setCentralWidget(completePage);

    QString imagePath = "D:/Assignment/Grade2.2/c++/GoldMiner/GoldMiner/src/window/image/victory_background.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
    */
    //===================================================================================

    // MainWindow 构造函数中  
    // 连接 StartPage 的 startGame 信号到 MainWindow 的槽函数  
    connect(startPage, &StartPage::startGame, this, &MainWindow::handleStartButtonClicked);

    // 连接 RunningPage 的 exitGame 信号到 MainWindow 的槽函数  
    connect(runningPage, &RunningPage::exitGame, this, &MainWindow::handleExitButtonClicked);

    // 连接 Complete 的 nextLevel 信号到 MainWindow 的槽函数  
    connect(completePage, &CompletePage::nextLevel, this, &MainWindow::handleNextLevelButtonClicked);

    //TODO : 
    //连接 RunningPage 的 
    //别的模块发来的 “通关” 信号到 MainWindow 的槽函数  
    //connect(completePage, &CompletePage::nextLevel, this, &MainWindow::handleNextLevelButtonClicked);
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
    this->resize(592, 434);
    this->setWindowTitle("Running");
    setCentralWidget(runningPage);
    QString imagePath = "D:/Assignment/Grade2.2/c++/GoldMiner/GoldMiner/src/window/image/running_background.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
    // 发射信号通知 app 层,通知已改变状态完成  
    emit StartToRunGame(GameState::Running);
}

// 处理 游戏中“退出”按钮点击的槽函数  
void MainWindow::handleExitButtonClicked()
{
    this->resize(1100, 799);
    this->setWindowTitle("This Level Victory");
    setCentralWidget(completePage);

    QString imagePath = "D:/Assignment/Grade2.2/c++/GoldMiner/GoldMiner/src/window/image/victory_background.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
    /*this->resize(1024, 1024);
    this->setWindowTitle("Gold Miner Start");
    //暂定直接返回开始界面
    setCentralWidget(startPage);
    QString imagePath = "D:/Assignment/Grade2.2/c++/GoldMiner/GoldMiner/src/window/image/start_background.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
    */
    // 发射信号通知 viewmodel 层  
    emit RunToExit(GameState::Start);

}

// 处理 游戏结束后comp界面“下一关”按钮点击后，进入下一关RunningPage的槽函数  
void MainWindow::handleNextLevelButtonClicked()
{
    this->resize(592, 434);
    this->setWindowTitle("Next Level Running");
    setCentralWidget(runningPage);
    QString imagePath = "D:/Assignment/Grade2.2/c++/GoldMiner/GoldMiner/src/window/image/running_background.jpg";
    setStyleSheet("MainWindow { background-image: url(" + imagePath + "); background-size: cover; }");
    // 发射信号通知 viewmodel 层  
    emit CompleteToNextRun(GameState::Running);
}