#include "app.h"
GameAPP::GameAPP(){
    m_viewModel = new ViewModel();
    m_window = new MainWindow();
    //:m_model(),m_viewModel())
    // 用 QObject::connect 实现 view 和 view model 层的数据绑定

    //:m_model(),m_viewModel())
    m_window->setGameData(m_viewModel->getGameData());
    // 游戏胜负
    QObject::connect(m_viewModel, &ViewModel::winGame, m_window, &MainWindow::handleWinGame);
    QObject::connect(m_viewModel, &ViewModel::loseGame, m_window, &MainWindow::handleLoseGame);
    // 游戏中，每帧提醒后端刷新
    QObject::connect(m_window, &MainWindow::timeOut, m_viewModel, &ViewModel::handleTimeOut);
    // 提醒数据更新，重新绘制（传递参数版本）
    QObject::connect(m_viewModel, &ViewModel::stateChanged, m_window, &MainWindow::updateState);
    // 点击了 Start Game 按钮
    QObject::connect(m_window, &MainWindow::startGame, m_viewModel, &ViewModel::handleStartGame);
    // 点击了 Exit Game 按钮，此时后端需要判断 win or lose
    QObject::connect(m_window, &MainWindow::exitGame, m_viewModel, &ViewModel::handleExitGame);
    // 点击 Next Level 按钮，后端需要重置状态，更新 level 等级
    QObject::connect(m_window, &MainWindow::nextLevel, m_viewModel, &ViewModel::handleNextLevel);
    // 点击 Play Again 按钮，后端需要重置状态
    QObject::connect(m_window, &MainWindow::playAgain, m_viewModel, &ViewModel::handlePlayAgain);
    // 玩家按下键盘，伸长钩子
    QObject::connect(m_window, &MainWindow::pressKey, m_viewModel, &ViewModel::handlePressKey);
}
GameAPP::~GameAPP(){
    delete m_window;
    delete m_viewModel;
}
void GameAPP::run(){
    // 启动程序
    m_window->show();
}