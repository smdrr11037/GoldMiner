#include "Model.h"


Model::Model(QObject *parent)
{
    m_level = 1;
    init();
}

Model::~Model()
{
    if(m_hook != nullptr) delete m_hook;
    if(m_player != nullptr) delete m_player;
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
        m_hook->startCatch();
        m_collidedBlock = b;
        retractHook();
        qDebug() << "Hook catch a block!";
    }
    else if(m_hook->getIsRetracting() && m_hook->getPosition().getDistance() <= HOOK_INIT_LENGTH){
        m_hook->stopCatch();
        m_hook->stopRetracting();
        m_hook->reset();
        if(m_collidedBlock != nullptr){
            qDebug() << "Block get!";
            qDebug() << "Gold?" << m_collidedBlock->isGoldBlock();
            qDebug() << "Size" << m_collidedBlock->getSize();
            qDebug() << "Value" << m_collidedBlock->getValue();
            qDebug() << "Position (" << m_collidedBlock->getPosition().x << ',' << m_collidedBlock->getPosition().y << ')'; 

            updatePlayerScore();
            for(auto it_block=m_blocks.begin(); it_block != m_blocks.end(); it_block++){
                if(&*it_block == m_collidedBlock){
                    m_blocks.erase(it_block);
                    break;
                }
            }
            qDebug() << m_blocks.size() << "block left"; 
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
        emit winGame();
        qDebug() << "Win the game";
    }
    else{
        emit loseGame();
        qDebug() << "Game Over";
    }
    m_collidedBlock = nullptr;
    m_blocks.clear();
    // delete m_hook;
    // delete m_player;
    // m_hook = nullptr;
    // m_player = nullptr;
}

void Model::startGame()
{
    restart();
    qDebug() << "Game Running";
}

void Model::playAgain()
{
    restart();
    qDebug() << "Game Running";
}

void Model::nextLevel()
{
    m_level++;
    restart();
    qDebug() << "Game Running";
}

//成员函数

void Model::init()
{
    generateBlocks();
    qDebug() << "Block number:" << m_blocks.size();
    for(auto block: m_blocks){
        qDebug() << "----------";
        qDebug() << "Gold?" << block.isGoldBlock();
        qDebug() << "Size" << block.getSize();
        qDebug() << "Value" << block.getValue();
        qDebug() << "Position (" << block.getPosition().x << ',' << block.getPosition().y << ')'; 
    }

    m_hook = new Hook(HOOK_ANGLE_MIN);
    m_player = new Player(0, 45, m_level, 300);
    m_frameNumber = 0;
    m_collidedBlock = nullptr;
    m_gameData = std::make_shared<GameData>(GameData{&m_blocks, m_hook, m_player});
}

void Model::restart()
{
    m_hook->stopExtending();
    m_hook->setAngle(HOOK_ANGLE_MIN);
    m_hook->updatePosition();

    m_player->setScore(0);
    //m_player->setTime(45);
    m_player->setTime(50 - m_level*5);
    if (m_player->getTime() < 15) {
        m_player->setTime(15);
    }
    m_player->setLevel(m_level);
    //m_player->setTargetScore(300);
    m_player->setTargetScore(300+100*m_level);

    m_blocks.clear();
    generateBlocks();
    qDebug() << "Block number:" << m_blocks.size();
    for(auto block: m_blocks){
        qDebug() << "----------";
        qDebug() << "Gold?" << block.isGoldBlock();
        qDebug() << "Size" << block.getSize();
        qDebug() << "Value" << block.getValue();
        qDebug() << "Position (" << block.getPosition().x << ',' << block.getPosition().y << ')'; 
    }
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
    if(!m_hook->getIsExtending() && !m_hook->getIsRetracting()){
        qDebug() << "Hook extending!";
        m_hook->startExtending();
    }
}

void Model::retractHook()
{
    assert(m_hook->getIsExtending() && !m_hook->getIsRetracting());
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
        //updateHookAngle(DEGREE_CHANGE_PER_FRAME);
        double ratateSpeed = DEGREE_CHANGE_PER_FRAME + (double)m_level*0.5;
        updateHookAngle(ratateSpeed);
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
            double rate = m_collidedBlock->getSize() / g_goldSize[0] * 1.5;
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

    emit stateChanged();
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
    // Position p(100.0f, 600.0f);
    // Block a(true, GOLD_LARGE_SIZE, GOLD_LARGE_VALUE, p);
    // m_blocks.push_back(a);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> blockNum(BLOCK_NUMBER_MIN, BLOCK_NUMBER_MAX);
    std::uniform_real_distribution<double> disY(BLOCK_Y_MIN, BLOCK_Y_MAX);
    std::uniform_real_distribution<double> disX(BLOCK_X_MIN, BLOCK_X_MAX);
    std::uniform_int_distribution<int> blockType(0, 1);
    std::uniform_int_distribution<int> blockSize(0, 2);
    int n = blockNum(gen);
    while(m_blocks.size() < n){
        double x = disX(gen);
        double y = disY(gen);
        bool isGold = (blockType(gen) == 1);
        int sizeChoose = blockSize(gen);
        double size = isGold ? g_goldSize[sizeChoose] : g_stoneSize[sizeChoose];
        int value = isGold ? g_goldValue[sizeChoose] : g_stoneValue[sizeChoose];
        if(x > y/tan(DEGREES_TO_RADIANS(HOOK_ANGLE_MIN)) || x < y/tan(DEGREES_TO_RADIANS(HOOK_ANGLE_MAX))) {
            continue;
        }
        Position p(x, y);
        bool flag = true;
        for(auto block: m_blocks){
            double dis = (p-block.getPosition()).getDistance();
            if(dis < (size+block.getSize())) {
                flag = false;
                break;
            }
        }
        if(!flag) continue;
        else{
            Block b(isGold, size, value, p);
            m_blocks.push_back(b);
        }
    }
}

std::shared_ptr<GameData> Model::getGameData()
{
    return m_gameData;
}