// 可能需要实现的
// 1. 游戏开始时，生成一定数量的金块和石块，以及钩子
// 2. 每隔一段时间（一帧）更新钩子的状态（旋转）
// 3. 用户点击后，伸长钩子
// 4. 判断钩子是否碰到了金块或石块，或者到达窗口的边界，要收回钩子
// 5. 钩子回收的速度可能与金块或石块的 size 有关（可以后面优化再实现
// 6. 改变钩子和金块的位置可以计算位置变化量，调用 updatePosition 函数更新位置
// 也可以重写位置变化函数等等

#ifndef GMMODEL_H
#define GMMODEL_H
#include <QObject>
#include <QDebug>
#include <vector>
#include <random>
#include "../common/GoldMinerDef.h"

#define EXTENDING_PER_SECOND 250.0f
#define EXTENDING_PER_FRAME (EXTENDING_PER_SECOND/FRAME_NUMBER)
#define RETRACTING_PER_SECOND 425.0f
#define RETRACTING_PER_FRAME (RETRACTING_PER_SECOND/FRAME_NUMBER)

#define SECONDS_PER_SWING 3.1f
#define DEGREE_CHANGE_PER_FRAME (HOOK_ANGLE_RANGE/(SECONDS_PER_SWING*FRAME_NUMBER)) 

#define BLOCK_NUMBER_MIN 5
#define BLOCK_NUMBER_MAX 10
#define BLOCK_Y_MIN 300
#define BLOCK_Y_MAX (SCREEN_Y_BOUND)
#define BLOCK_X_MIN (-SCREEN_X_BOUND)
#define BLOCK_X_MAX (SCREEN_X_BOUND)

const int g_goldValue[3] = {50, 100, 500};
const int g_stoneValue[3] = {33, 60, 90};
const double g_goldSize[3] = { SMALL_GOLD, MIDDLE_GOLD, BIG_GOLD };
const double g_stoneSize[3] = { SMALL_STONE, MIDDLE_STONE, BIG_STONE };

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    virtual ~Model();
    void init();                                // 每关初始化钩子、物块、游戏状态
    void generateBlocks();                      // 生成物块
    void updateHookPosition(double dx, double dy);      // 更新钩子位置
    void updateBlockPosition(double dx, double dy);     // 每帧更新物块位置
    void updateHookAngle(double angle);         // 更新钩子角度
    void extendHook();                          // 固定钩子角度并伸长
    void retractHook();                         // 收回钩子
    Block* checkCollision();                    // 检查碰撞
    bool checkOutOfBound();                     // 检查出界
    void updatePlayerScore();                   // 收回物块时更新分数
    void updatePlayerTime();                    // 每帧更新玩家游戏倒计时
    void updateHook();                          // 每帧更新钩子位置(旋转或伸长或收回)
    void showInfo();

    void checkHookState();      // 检查钩子状态
    void startExtending();      // 开始伸长钩子
    void startGame();           // 开始游戏
    void exitGame();            // 退出游戏
    void playAgain();           // 重试
    void nextLevel();
    std::shared_ptr<GameData> getGameData();

signals:

    void stateChanged();
    void winGame();
    void loseGame();

private:
    void restart();
    int m_frameNumber;
    int m_level;
    Hook *m_hook;                // 钩子
    std::vector<Block> m_blocks; // 存储所有块的集合
    Player *m_player;
    Block *m_collidedBlock;      // 捕获的物块  
    std::shared_ptr<GameData> m_gameData;
};

#endif // COUNTERMODEL_H