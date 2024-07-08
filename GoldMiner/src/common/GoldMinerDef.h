#ifndef GOLD_MINER_DEF_H
#define GOLD_MINER_DEF_H

// 这里是一些全局变量的定义，比如游戏的一些参数，游戏的状态等。
#include <iostream>

struct Position // 金块或者石块的位置
{
    int x;
    int y;
};

class Block // 金块或者石块的结构体
{
public:
    // 这些方法都比较简单且常用，就写成 inline 了
    // 构造函数
    Block(bool isGold, int size, int value, Position position)
        : isGold(isGold), size(size), value(value), position(position) {}

    // 获取是否为金块
    bool isGoldBlock() const
    {
        return isGold;
    }

    /**
     * @brief 获取块的大小
     * 
     */
    int getSize() const
    {
        return size;
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
    void movePosition(int dx, int dy)
    {
        position.x += dx;
        position.y += dy;
    }

    // 输出块信息（调试用）
    void printInfo() const
    {
        std::cout << "Block Info: " << (isGold ? "Gold" : "Stone")
                  << ", Size: " << size
                  << ", Value: " << value
                  << ", Position: (" << position.x << ", " << position.y << ")\n";
    }

private:
    bool isGold;
    Position position;
    int size;
    int value;
};

class Hook // 钩子的类
{
public:
    Hook(Position startPosition) : position(startPosition), isExtending(false) {}
    double getAngle() const {return angle; }
    Position getPosition() const { return position; }
    bool getIsExtending() const { return isExtending; }
    void startExtending() { isExtending = true; }
    void stopExtending() { isExtending = false; }
    void updatePosition(int dx, int dy)
    {
        position.x += dx;
        position.y += dy;
    }

private:
    double angle; // 度数制表示的角度
    bool isExtending;
    Position position;
};

enum class GameState // 游戏所处的页面
{
    Start,
    Running,
    Paused, // 后续可能增加暂停的功能
    Win, // 通关
    GameOver // 失败
};

class IGameObserver // 观察者模式接口，ViewModel可以实现该接口来监听Model的变化
// GPT 写的，我也不知道什么东西
{
public:
    virtual void onGameStateChanged(GameState newState) = 0;
    virtual void onScoreUpdated(int newScore) = 0;
    virtual void onTimeUpdated(int remainingTime) = 0;
};


class Model;// 模型类的前向声明，负责管理游戏的状态

class Player // 玩家类
{
    friend class Model;  // Model 类可以访问 Player 类的私有成员和保护成员
    
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
    
    protected:
        void setScore(int newScore) { m_score = newScore; }
        void setLevel(int newlevel) { m_level = newlevel; }
        void setTime(int newTime) { m_time = newTime; }
        void setTargetScore(int newTargetScore) { targetScore = newTargetScore; }
};

#endif // GOLD_MINER_DEF_H