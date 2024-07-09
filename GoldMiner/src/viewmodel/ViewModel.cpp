#include "ViewModel.h"
#include <QDebug>
ViewModel::ViewModel(QObject *parent)
{
    m_model = new Model(nullptr);
    connect(m_model, &Model::winGame, this, &ViewModel::winGame);
    connect(m_model, &Model::loseGame, this, &ViewModel::loseGame);
    connect(m_model, &Model::stateChanged, this, &ViewModel::updateState);
}
// slot function

// from view
void ViewModel::handleTimeOut()
{
    qDebug() << "time out signal";
    m_model->checkHookState();
}
void ViewModel::handleStartGame()
{
    m_model->startGame();
}
void ViewModel::handleExitGame()
{
    m_model->exitGame();
}
void ViewModel::handlePlayAgain()
{
    m_model->playAgain();
}
void ViewModel::handleNextLevel()
{
    m_model->nextLevel();
}
void ViewModel::handlePressKey()
{
    m_model->extendHook();
}

// from model
void ViewModel::updateState(const std::vector<Block>& blocks, const Hook& hook, const Player &player)
{
    qDebug() << "ViewModel: state Changed";
    emit stateChanged(blocks, hook, player);
}
