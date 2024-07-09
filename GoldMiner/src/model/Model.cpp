#include "Model.h"


Model::Model(QObject *parent)
{
    m_gameState = GameState::Start;
    m_level = 1;
}

Model::~Model()
{
}

// 槽函数

void Model::checkHookState()
{
    Block *b = checkCollision();
    if(m_hook->getIsExtending() && checkOutOfBound()){
        retractHook();
        qDebug() << "Hook out of bound!";
    }
    else if(m_hook->getIsExtending() && b != nullptr){
        m_collidedBlock = b;
        retractHook();
        qDebug() << "Hook catch a block!";
    }
    else if(m_hook->getIsRetracting() && m_hook->getPosition().getDistance() <= HOOK_INIT_LENGTH){
        qDebug() << "Block get daze!";
        m_hook->stopRetracting();
        m_hook->reset();
        if(m_collidedBlock != nullptr){
            updatePlayerScore();
            for(auto it_block=m_blocks.begin(); it_block != m_blocks.end(); it_block++){
                if(&*it_block == m_collidedBlock){
                    m_blocks.erase(it_block);
                    break;
                }
            }
        }
        m_collidedBlock = nullptr;
    }
    updatePlayerTime();
}

void Model::startExtending()
{
    if(!m_hook->getIsExtending() && !m_hook->getIsRetracting()){
        extendHook();
    }
}

void Model::exitGame()
{
    if(m_player->getScore() >= m_player->getTargetScore()) {
        m_gameState = GameState::Win;
        qDebug() << "Model state change to Win";
    }
    else{
        m_gameState = GameState::GameOver;
        qDebug() << "Model state change to GameOver";
    }
    delete m_hook;
    delete m_player;
    emit pageChanged(m_gameState);
}

void Model::startGame()
{
    m_gameState = GameState::Running;
    init();
    qDebug() << "Model state change to Running";
    emit pageChanged(m_gameState);
}

void Model::playAgain()
{
    m_gameState = GameState::Running;
    init();
    qDebug() << "Model state change to Running";
    emit pageChanged(m_gameState);
}

void Model::nextLevel()
{
    m_gameState = GameState::Running;
    m_level++;
    init();
    qDebug() << "Model state change to Running";
    emit pageChanged(m_gameState);
}

//成员函数

void Model::init()
{
    generateBlocks();
    m_hook = new Hook(HOOK_ANGLE_MIN);
    m_player = new Player(0, 25, m_level, 650);
    m_frameNumber = 0;
    m_collidedBlock = nullptr;
}

void Model::updateHookPosition(double dx, double dy)
{
    m_hook->updatePosition(dx, dy);
}

void Model::updateHookAngle(double angle)
{
    m_hook->updateAngle(angle);
}

void Model::extendHook()
{
    qDebug() << "Hook extending!";
    m_hook->startExtending();
}

void Model::retractHook()
{
    m_hook->stopExtending();
    m_hook->startRetracting();
}

Block* Model::checkCollision()
{
    Position pHook = m_hook->getPosition();
    for(auto it_block=m_blocks.begin(); it_block != m_blocks.end(); it_block++)
    {
        Position p = it_block->getPosition() - pHook;
        if(p.getDistance() <= it_block->getSize()){
            return &*it_block;
        }
    }
    return nullptr;

}

bool Model::checkOutOfBound()
{
    Position p = m_hook->getPosition();
    return p.x > SCREEN_X_BOUND || p.x < -SCREEN_X_BOUND || p.y > SCREEN_Y_BOUND;   
}

void Model::updatePlayerScore()
{
    assert(m_collidedBlock != nullptr);
    m_player->setScore(m_player->getScore() + m_collidedBlock->getValue());
}

void Model::updateBlockPosition(double dx, double dy)
{
    assert(m_hook->getIsRetracting() && m_collidedBlock != nullptr);
    m_collidedBlock->movePosition(dx, dy);
}

void Model::updateHook()
{
    assert(!(m_hook->getIsRetracting()&&m_hook->getIsExtending()));
    if(!m_hook->getIsRetracting() && !m_hook->getIsExtending()){
        updateHookAngle(DEGREE_CHANGE_PER_FRAME);
        m_hook->updatePosition();
    }
    else if(m_hook->getIsExtending()){
        double dx = EXTENDING_PER_FRAME * cos(DEGREES_TO_RADIANS(m_hook->getAngle()));
        double dy = EXTENDING_PER_FRAME * sin(DEGREES_TO_RADIANS(m_hook->getAngle()));
        updateHookPosition(dx, dy);
    }
    else if(m_hook->getIsRetracting()){
        double dx, dy;
        if(m_collidedBlock != nullptr){
            double rate = m_collidedBlock->getSize() / GOLD_SMALL_SIZE;
            dx = -RETRACTING_PER_FRAME * cos(DEGREES_TO_RADIANS(m_hook->getAngle())) / rate;
            dy = -RETRACTING_PER_FRAME * sin(DEGREES_TO_RADIANS(m_hook->getAngle())) / rate;
            updateBlockPosition(dx, dy);
        }
        else{
            dx = -RETRACTING_PER_FRAME * cos(DEGREES_TO_RADIANS(m_hook->getAngle()));
            dy = -RETRACTING_PER_FRAME * sin(DEGREES_TO_RADIANS(m_hook->getAngle()));
        }
        updateHookPosition(dx, dy);
    }  

    emit stateChanged(m_blocks, *m_hook, *m_player);
}

void Model::updatePlayerTime()
{
    m_frameNumber++;
    if(m_frameNumber % FRAME_NUMBER == 0) {
        m_player->setTime(m_player->getTime()-1);
        showInfo();
    }
    if(m_player->getTime() == 0){
        exitGame();
        return;
    }
    updateHook();
}

void Model::showInfo()
{
    qDebug() << m_player->getTime() << "s left";
    qDebug() << "Hook Angle:" << m_hook->getAngle();
    qDebug() << "Hook Position:" << m_hook->getPosition().x << " " << m_hook->getPosition().y;
    qDebug() << "Score:" << m_player->getScore();
    qDebug() << "===========";
}

void Model::generateBlocks()
{
    Position p(100.0f, 600.0f);
    Block a(true, GOLD_LARGE_SIZE, GOLD_LARGE_VALUE, p);
    m_blocks.push_back(a);
}