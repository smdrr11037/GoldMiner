// 游戏页面
// 需要实现的布局
// 1. 分数显示
// 2. 过关目标
// 3. 退出按钮
// 4. 背景显示
// 5. 金块和石块显示
// 6. 钩子显示
#ifndef RUNNING_PAGE_H
#define RUNNING_PAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "../common/GoldMinerDef.h"
class RunningPage : public QWidget
{
    Q_OBJECT

public:
    explicit RunningPage(QWidget* parent = nullptr);

signals:
    void exitGame(GameState gameState); // 退出游戏的信号  
private slots:
    void exitButtonClicked(); // 退出按钮点击时的槽函数  

private:
    QLabel* scoreLabel;       // 分数显示的标签  
    QLabel* targetLabel;      // 过关目标显示的标签  
    QPushButton* exitButton;  // 退出按钮  
    QLabel* backgroundLabel;  // 背景显示的标签  
    QLabel* blocksLabel;      // 金块和石块显示的标签  
    QLabel* hookLabel;        // 钩子显示的标签  
    QVBoxLayout* layout;      // 用于管理视图的布局  
};

#endif