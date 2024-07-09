#include "app.h"
GameAPP::GameAPP(){
    m_model = new Model();
    m_viewModel = new ViewModel();
    m_window = new MainWindow();
    //:m_model(),m_viewModel())
    // 用 QObject::connect 实现 view 和 view model 层的数据绑定
    // // 需要转换页面，传递参数 GameState

    //:m_model(),m_viewModel())
    // 用 QObject::connect 实现 view 和 view model 层的数据绑定
    QObject::connect(m_viewModel, &ViewModel::startGame, m_model, &Model::startGame);
    QObject::connect(m_viewModel, &ViewModel::exitGame, m_model, &Model::exitGame);
    QObject::connect(m_viewModel, &ViewModel::playAgain, m_model, &Model::playAgain);
    QObject::connect(m_viewModel, &ViewModel::pressKey, m_model, &Model::startExtending);
    QObject::connect(m_viewModel, &ViewModel::nextLevel, m_model, &Model::nextLevel);
    QObject::connect(m_viewModel, &ViewModel::frameElapsed, m_model, &Model::checkHookState);
    
    QObject::connect(m_model, &Model::stateChanged, m_viewModel, &ViewModel::updateState);
    QObject::connect(m_model, &Model::pageChanged, m_viewModel, &ViewModel::updatePage);
    // // 需要转换页面，传递参数 GameState
    QObject::connect(m_viewModel, &ViewModel::pageChanged, m_window, &MainWindow::updatePage);
    // // 游戏中，每帧刷新，传递参数 const vector<Block>& m_block、const &m_hook、const &m_player
    QObject::connect(m_viewModel, &ViewModel::stateChanged, m_window, &MainWindow::updateState);
    // // 点击了 Start Game 按钮
    QObject::connect(m_window, &MainWindow::startGame, m_viewModel, &ViewModel::handleStartGame);
    // // 点击了 Exit Game 按钮，到达 GameOver 页面
    QObject::QObject::connect(m_window, &MainWindow::exitGame, m_viewModel, &ViewModel::handleExitGame);
    // // 点击 Next Level 按钮
    QObject::connect(m_window, &MainWindow::nextLevel, m_viewModel, &ViewModel::handleNextLevel);
    // // 点击 Play Again 按钮（游戏失败时
    QObject::connect(m_window, &MainWindow::playAgain, m_viewModel, &ViewModel::handlePlayAgain);
    // // 玩家按下键盘，伸长钩子
    QObject::connect(m_window, &MainWindow::pressKey, m_viewModel, &ViewModel::handlePressKey);
}
GameAPP::~GameAPP(){
}
void GameAPP::run(){
    // 启动程序
    m_window->show();
}