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
#include "../common/GoldMinerDef.h"
#include "../viewmodel/ViewModel.h"

#define MOVEMENT_PER_FRAME 150.0f
#define PI 3.1415926f
#define DEGREES_TO_RADIANS(angle) (angle*PI/180.0f)

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    virtual ~Model();
    void init();                 // 每关初始化钩子、物块、游戏状态
    void generateBlocks();       // 生成物块
    void updateHookPosition(int x, int y); // 更新钩子位置
    void updateHookAngle(double angle);    // 更新钩子角度
    void extendHook();           // 固定钩子角度并伸长
    void retractHook();          // 收回钩子
    bool checkCollision();       // 检查碰撞
    bool checkOutOfBound();      // 检查出界


signals:
    void pageChanged(Hook& hook, std::vector<Block*>& blocks);
    void stateChanged(GameState gameState);

public slots:
    void updateHook();          // 每帧更新钩子位置(旋转或伸长或收回)
    void startExtending();      // 开始伸长钩子
    void startGame();           // 开始游戏
    void nextLevel();            // 退出游戏

private:
    int m_score;
    int targetScore;
    Hook *m_hook;                 // 钩子
    std::vector<Block*> m_blocks; // 存储所有块的集合
    GameState m_gameState;       // 游戏状态
    int m_level;                 // 等级
    Player *m_player;
};

#endif // COUNTERMODEL_H