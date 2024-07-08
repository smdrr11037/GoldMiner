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
void ViewModel::handleNextLevel()
{
    m_pTimer->stop();
    emit nextLevel();
}
void ViewModel::frameElapsedEmit()
{
    emit frameElapsed();
}
void ViewModel::updatePage(Hook& hook, std::vector<Block*>& blocks)
{
    emit pageChanged(hook, blocks);
}
void ViewModel::updateState(GameState GameState)
{
    emit stateChanged(GameState);
}