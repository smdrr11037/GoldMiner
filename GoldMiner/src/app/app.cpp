#include "app.h"
GameAPP::GameAPP():m_window(nullptr){
    //:m_model(),m_viewModel())
    // 用 connect 实现 view 和 view model 层的数据绑定
    // // 需要转换页面，传递参数 GameState
    // connect(m_viewModel, &ViewModel::pageChanged, m_window, &MainWindow::updatePage);
    // // 游戏中，每帧刷新，传递参数 const vector<Block>& m_block、const &m_hook、const &m_player
    // connect(m_viewModel, &ViewModel::stateChanged, m_window, &MainWindow::updateState);
    // // 点击了 Start Game 按钮
    // connect(m_window, &MainWindow::startGame, m_viewModel, &ViewModel::handleStartGame);
    // // 点击了 Exit Game 按钮，到达 GameOver 页面
    // connect(m_window, &MainWindow::exitGame, m_viewModel, &ViewModel::handleExitGame);
    // // 点击 Next Level 按钮
    // connect(m_window, &MainWindow::nextLevel, m_viewModel, &ViewModel::handelNextLevel);
    // // 点击 Play Again 按钮（游戏失败时
    // connect(m_window, &MainWindow::playAgain, m_viewModel, &ViewModel::handelPlayAgain);
    // // 玩家按下键盘，伸长钩子
    // connect(m_window, &MainWindow::pressKey, m_viewModel, &ViewModel::handelPressKey);
}
GameAPP::~GameAPP(){
}
void GameAPP::run(){
    // 启动程序
    m_window.show();
}