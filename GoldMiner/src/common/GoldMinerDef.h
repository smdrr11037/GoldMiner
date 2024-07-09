#ifndef GOLD_MINER_DEF_H
#define GOLD_MINER_DEF_H

// 这里是一些全局变量的定义，比如游戏的一些参数，游戏的状态等。
#include <iostream>
#include <algorithm>
#include <cmath>


#define FRAME_NUMBER 30

#define HOOK_INIT_LENGTH 30.0f
#define HOOK_ANGLE_MAX 135.0f
#define HOOK_ANGLE_MIN 45.0f
#define HOOK_ANGLE_RANGE (HOOK_ANGLE_MAX-HOOK_ANGLE_MIN)

#define PI 3.1415926f
#define SCREEN_X_BOUND 865
#define SCREEN_Y_BOUND 865
#define DEGREES_TO_RADIANS(angle) (angle*PI/180.0f)


enum class BlockSize
{
    Small,
    Middle,
    Large
};


struct Position // 金块或者石块的位置
{
    Position(){ x=0, y=0; }
    Position(double ix, double iy):x(ix), y(iy){}
    Position(const Position &p){
        x = p.x;
        y = p.y;
    }
    ~Position(){};
    Position operator- (const Position &rhs) const
    {
        return Position(x - rhs.x, y - rhs.y);
    }
    bool operator== (const Position &p){
        if(p.x == x && p.y == y){ return true; }
        else { return false; }
    }

    double getDistance() const
    {
        return sqrt(x*x + y*y);
    } 

    double x;
    double y;
};

class Block // 金块或者石块的结构体
{
public:
    // 这些方法都比较简单且常用，就写成 inline 了
    // 构造函数
    Block(){
        isGold = false;
        size = 0.0f;
        value = 0;
    }
    Block(bool isGold, double size, int value, Position position)
        : isGold(isGold), size(size), value(value), position(position) {}

    bool operator== (const Block &block)
    {
        if(block.isGold == isGold && block.size == size && block.value == value && block.getPosition() == position){
            return true;
        }
        else{
            return false;
        }
    }

    // 获取是否为金块
    bool isGoldBlock() const
    {
        return isGold;
    }

    // 获取块的大小（圆的半径）
    double getSize() const
    {
        return size;;
    }

    // 获取块的价值
    int getValue() const
    {
        return value;
    }

    // 获取位置
    Position getPosition() const
    {
        return position;
    }

    // 设置位置
    void setPosition(const Position &newPosition)
    {
        position = newPosition;
    }

    // 移动位置（增量）
    void movePosition(double dx, double dy)
    {
        position.x += dx;
        position.y += dy;
    }

    // 输出块信息（调试用）
    void printInfo() const
    {
        std::cout << "Block Info: " << (isGold ? "Gold" : "Stone")
                  << ", size: " << size
                  << ", Value: " << value
                  << ", Position: (" << position.x << ", " << position.y << ")\n";
    }

private:
    bool isGold;
    Position position;
    double size;
    int value;
};

class Hook // 钩子的类
{
public:
    Hook(Position startPosition, double startAngle, bool isSwingForwarding=true) : position(startPosition), angle(startAngle), isSwingForwarding(isSwingForwarding), isExtending(false) {}
    Hook(double startAngle, bool isSwingForwarding=true):angle(startAngle), isSwingForwarding(isSwingForwarding){
        position.x = HOOK_INIT_LENGTH * cos(DEGREES_TO_RADIANS(startAngle));
        position.y = HOOK_INIT_LENGTH * sin(DEGREES_TO_RADIANS(startAngle));
        isExtending = false;
    }
    double getAngle() const {return angle; }
    Position getPosition() const { return position; }
    bool getIsExtending() const { return isExtending; }
    void startExtending() { isExtending = true; }
    void stopExtending() { isExtending = false; }
    bool getIsRetracting() const { return isRetracting; }
    void startRetracting() { isRetracting = true; }
    void stopRetracting() { isRetracting = false; }
    void updatePosition(double dx, double dy)
    {
        position.x += dx;
        position.y += dy;
    }
    void updatePosition()
    {
        position.x = HOOK_INIT_LENGTH * cos(DEGREES_TO_RADIANS(angle));
        position.y = HOOK_INIT_LENGTH * sin(DEGREES_TO_RADIANS(angle));
    }
    void updateAngle(double theta)
    {
        if(isSwingForwarding){
            angle += theta;
            if(angle > HOOK_ANGLE_MAX){
                assert((angle-HOOK_ANGLE_MAX) < HOOK_ANGLE_RANGE); // 声明 angle 有限，不会突然大于 225°
                angle = 2*HOOK_ANGLE_MAX - angle;
                isSwingForwarding = false;
            }
        }
        else{
            angle -= theta;
            if(angle < HOOK_ANGLE_MIN){
                assert((HOOK_ANGLE_MIN-angle) < HOOK_ANGLE_RANGE ); // 声明 angle 有限，不会突然小于 -45°
                angle = 2*HOOK_ANGLE_MIN - angle;
                isSwingForwarding = true;
            }
        }
    }
    void reset()
    {
        if(isSwingForwarding){
            angle = HOOK_ANGLE_MAX;
            isSwingForwarding = false;
        }
        else{
            angle = HOOK_ANGLE_MIN;
            isSwingForwarding = true;
        }
        updatePosition();
    }

private:
    double angle; // 度数制表示的角度
    bool isExtending;
    bool isRetracting;
    bool isSwingForwarding;
    Position position;
};


class Player // 玩家类
{   
    private:
        int m_score;
        int m_time;
        int m_level;
        int targetScore;// 目标分数
    
    public:
        Player(int score=0, int time=0, int level=1, int targetscore=0) : 
        m_score(score), m_time(time),  m_level(level) ,targetScore(targetscore){}
        int getScore() const { return m_score; }
        int getTime() const { return m_time; }
        int getLevel() const { return m_level; }
        int getTargetScore() const { return targetScore; }
        void setScore(int newScore) { m_score = newScore; }
        void setLevel(int newlevel) { m_level = newlevel; }
        void setTime(int newTime) { m_time = newTime; }
        void setTargetScore(int newTargetScore) { targetScore = newTargetScore; }
};

struct GameData {
    std::vector<Block> blockVector;
    std::shared_ptr<Hook> hook;
    std::shared_ptr<Player> player;
};

// 用法（没写构造函数时
// std::shared_ptr<Hook> hook = std::make_shared<Hook>(Position{0, 0}, 45.0);
// 初始化其他对象 ...
// std::shared_ptr<GameData> gameData = std::make_shared<GameData>(GameData{blocks, hook, player});
// 只需要把 gameData 暴露和获取即可

#endif // GOLD_MINER_DEF_H