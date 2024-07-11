#include "app.h"
GameAPP::GameAPP(){
    m_viewModel = std::make_shared<ViewModel>();
    m_window = std::make_shared<MainWindow>();
    m_model = std::make_shared<Model>();
    //:m_model(),m_viewModel())
    // 用 QObject::connect 实现 view 和 view model 层的数据绑定

    //:m_model(),m_viewModel())
    m_viewModel->setModel(m_model);
    m_window->setGameData(m_viewModel->getGameData());
    // 游戏胜负
    QObject::connect(m_viewModel.get(), &ViewModel::winGame, m_window.get(), &MainWindow::handleWinGame);
    QObject::connect(m_viewModel.get(), &ViewModel::loseGame, m_window.get(), &MainWindow::handleLoseGame);
    // 游戏中，每帧提醒后端刷新
    QObject::connect(m_window.get(), &MainWindow::timeOut, m_viewModel.get(), &ViewModel::handleTimeOut);
    // 提醒数据更新，重新绘制（传递参数版本）
    QObject::connect(m_viewModel.get(), &ViewModel::stateChanged, m_window.get(), &MainWindow::updateState);
    // 点击了 Start Game 按钮
    QObject::connect(m_window.get(), &MainWindow::startGame, m_viewModel.get(), &ViewModel::handleStartGame);
    // 点击了 Exit Game 按钮，此时后端需要判断 win or lose
    QObject::connect(m_window.get(), &MainWindow::exitGame, m_viewModel.get(), &ViewModel::handleExitGame);
    // 点击 Next Level 按钮，后端需要重置状态，更新 level 等级
    QObject::connect(m_window.get(), &MainWindow::nextLevel, m_viewModel.get(), &ViewModel::handleNextLevel);
    // 点击 Play Again 按钮，后端需要重置状态
    QObject::connect(m_window.get(), &MainWindow::playAgain, m_viewModel.get(), &ViewModel::handlePlayAgain);
    // 玩家按下键盘，伸长钩子
    QObject::connect(m_window.get(), &MainWindow::pressKey, m_viewModel.get(), &ViewModel::handlePressKey);
    QObject::connect(m_window.get(), &MainWindow::timeOut, m_viewModel.get(), &ViewModel::handleTimeOut);
}
GameAPP::~GameAPP(){
}
void GameAPP::run(){
    // 启动程序
    m_window->show();
}