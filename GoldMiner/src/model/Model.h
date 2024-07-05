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
#include <vector>
#include "../common/GoldMinerDef.h"
class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

signals:

public slots:

private:
    int m_score;
    int targetScore;
    Hook m_hook;                 // 钩子
    std::vector<Block> m_blocks; // 存储所有块的集合
    GameState m_gameState;       // 游戏状态
    int m_level;                 // 等级
};

#endif // COUNTERMODEL_H