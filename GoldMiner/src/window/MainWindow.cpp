#include "MainWindow.h"  
#include <QVBoxLayout>
#include <QMainWindow>  

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    startPage = new StartPage(this);
    runningPage = new RunningPage(this);
    completePage = new CompletePage(this);

    setCentralWidget(startPage);

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

// 处理“开始”按钮点击的槽函数  
void MainWindow::handleStartButtonClicked(GameState gameState)
{
    if (gameState == GameState::Running) {
        setCentralWidget(runningPage);
    }

    // 发射信号通知 viewmodel 层  
    emit StartToRunGame(GameState::Running);
}

// 处理 游戏中“退出”按钮点击的槽函数  
void MainWindow::handleExitButtonClicked()
{
    //暂定直接返回开始界面
    setCentralWidget(startPage);

    // 发射信号通知 viewmodel 层  
    emit RunToExit(GameState::GameOver);
}

// 处理 游戏结束后comp界面“下一关”按钮点击后，进入下一关RunningPage的槽函数  
void MainWindow::handleNextLevelButtonClicked()
{
    setCentralWidget(runningPage);

    // 发射信号通知 viewmodel 层  
    emit CompleteToNextRun(GameState::Running);
}