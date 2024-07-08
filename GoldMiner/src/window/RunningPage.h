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
#include <QCoreApplication>
#include <QTransform>
#include <QKeyEvent>
#include <QPoint>
#include <QPainter>
#include <QPen>
#include "../common/GoldMinerDef.h"

const int OX = 1250;
const int OY = 300;
class RunningPage : public QWidget
{
    Q_OBJECT

public:
    explicit RunningPage(QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
    void refreshPage(const std::vector<Block>& blocks, const Hook& hook, const Player& player);
signals:
    void exitGame(GameState gameState); // 退出游戏的信号  
    void hookKeyDown();                 //下爪信号，emit给app层
    //void testSignal(const std::vector<Block>& blocks, const Hook& hook, const GameState& gameState);
    void runningPressKey();
private slots:
    void exitButtonClicked(); // 退出按钮点击时的槽函数  

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QLabel* scoreLabel;       // 分数显示的标签  
    QLabel* targetLabel;      // 过关目标显示的标签  
    QLabel* timeLabel;        // 过关目标显示的标签  
    QPushButton* exitButton;  // 退出按钮  
    QLabel* backgroundLabel;  // 背景显示的标签  
    QLabel* blocksLabel;      // 金块和石块显示的标签  
    QLabel* hookLabel;        // 钩子显示的标签  
    QVBoxLayout* layout;      // 用于管理视图的布局  
    QPoint startPoint;
    QPoint endPoint;
};

#endif