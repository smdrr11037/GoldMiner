#include "ViewModel.h"

ViewModel::ViewModel(QObject *parent)
{
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1))/FrameNumber;
    m_pTimer = new QTimer();
    m_pTimer->setInterval(ms.count());
    connect(m_pTimer, &QTimer::timeout, this, &ViewModel::frameElapsedEmit);
}


//slot function

void ViewModel::handleStartGame()
{
    m_pTimer->start();
    emit startGame();
}
void ViewModel::handleExitGame()
{
    m_pTimer->stop();
    emit exitGame();
}
void ViewModel::frameElapsedEmit()
{
    emit frameElapsed();
}
void ViewModel::updateState(std::vector<Block>& blocks, Hook& hook, Player &player)
{
    emit stateChanged(blocks, hook, player);
}
void ViewModel::updatePage(GameState &GameState)
{
    emit pageChanged(GameState);
}