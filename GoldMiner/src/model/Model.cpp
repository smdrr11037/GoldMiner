#include "Model.h"


Model::Model(QObject *parent)
{
    
}

Model::~Model()
{
    delete m_hook;
    delete m_player;
}

void Model::updateHook()
{
    assert(!(m_hook->getIsRetracting()&&m_hook->getIsExtending()));
    if(!m_hook->getIsRetracting() && !m_hook->getIsExtending()){
        updateHookAngle(2.0);
    }
    else if(m_hook->getIsExtending()){
        int dx = -(int)(MOVEMENT_PER_FRAME * cos(DEGREES_TO_RADIANS(m_hook->getAngle())));
        int dy = (int)(MOVEMENT_PER_FRAME * sin(DEGREES_TO_RADIANS(m_hook->getAngle())));
        updateHookPosition(dx, dy);
    }
    else if(m_hook->getIsRetracting()){
        int dx = (int)(MOVEMENT_PER_FRAME * cos(DEGREES_TO_RADIANS(m_hook->getAngle())));
        int dy = -(int)(MOVEMENT_PER_FRAME * sin(DEGREES_TO_RADIANS(m_hook->getAngle())));
        updateHookPosition(dx, dy);  
    }  

    qDebug() << "updateHook";
    emit stateChanged(m_blocks, *m_hook, *m_player);
}

void Model::startExtending()
{
    extendHook();
}

void Model::exitGame()
{
    m_gameState = GameState::GameOver;

    qDebug() << "Model state change to nextLevel";
    emit pageChanged(m_gameState);
}

void Model::startGame()
{
    m_gameState = GameState::Running;
    m_level = 1;
    init();
    qDebug() << "Model state change to start";
    emit pageChanged(m_gameState);
}

void Model::init()
{
    m_score = 0;
    targetScore = 1000;
    generateBlocks();
    m_hook = new Hook(Position(0, 0), 0.0);
    m_player = new Player();
}

/**
 * @brief 钩子伸长 (x, y) 长度
 */
void Model::updateHookPosition(int x, int y)
{
    m_hook->updatePosition(x, y);
}

/**
 * @brief 钩子旋转 angle 角度
 */
void Model::updateHookAngle(double angle)
{
    m_hook->updateAngle(angle);
}

void Model::extendHook()
{
    m_hook->startExtending();
}

void Model::retractHook()
{
    m_hook->stopExtending();
    m_hook->startRetracting();
}

bool Model::checkCollision()
{
    Position pHook = m_hook->getPosition();
    for(auto block: m_blocks)
    {
        Position p = block.getPosition() - pHook;
        
    }
}

bool Model::checkOutOfBound()
{

}
void Model::generateBlocks()
{

}