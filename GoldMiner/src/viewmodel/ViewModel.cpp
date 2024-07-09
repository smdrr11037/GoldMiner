#include "ViewModel.h"
#include <QDebug>
ViewModel::ViewModel(QObject *parent)
{
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1))/FRAME_NUMBER;
    m_pTimer = new QTimer();
    m_pTimer->setInterval(ms.count());
    connect(m_pTimer, &QTimer::timeout, this, &ViewModel::frameElapsedEmit);
}


// slot function
void ViewModel::frameElapsedEmit()
{
    emit frameElapsed();
}
// from view
void ViewModel::handleStartGame()
{
    emit startGame();
}
void ViewModel::handleExitGame()
{
    emit exitGame();
}
void ViewModel::handlePlayAgain()
{
    emit playAgain();
}
void ViewModel::handlePressKey()
{
    emit pressKey();
}
void ViewModel::handleNextLevel()
{
    emit nextLevel();
}
// from model
void ViewModel::updateState(const std::vector<Block>& blocks, const Hook& hook, const Player &player)
{
    emit stateChanged(blocks, hook, player);
}
void ViewModel::updatePage(const GameState &GameState)
{
    if(GameState != GameState::Running)
    {
        qDebug() << "game over";
        m_pTimer->stop();
    }
    else{
        qDebug() << "game running";
        m_pTimer->start();
    }
    emit pageChanged(GameState);
}