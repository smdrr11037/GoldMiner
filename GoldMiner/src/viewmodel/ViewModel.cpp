#include "ViewModel.h"
#include <QDebug>
ViewModel::ViewModel(QObject *parent)
{
}

ViewModel::~ViewModel()
{
}

//member function
std::shared_ptr<GameData> ViewModel::getGameData()
{
    return m_model->getGameData();
}
void ViewModel::setModel(std::shared_ptr<Model> model)
{
    m_model = model;
    connect(m_model.get(), &Model::winGame, this, &ViewModel::winGame);
    connect(m_model.get(), &Model::loseGame, this, &ViewModel::loseGame);
    connect(m_model.get(), &Model::stateChanged, this, &ViewModel::updateState);
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
void ViewModel::updateState()
{
    emit stateChanged();
}
