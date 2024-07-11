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
const double HOOK_OX = OX-77;
const int HOOK_OY = OY-56;
class RunningPage : public QWidget
{
    Q_OBJECT

public:
    explicit RunningPage(QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
    void refreshPage();
    void setGameData(std::shared_ptr<GameData> gameData);
signals:
    void exitGame(); // 退出游戏的信号  
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
    QLabel* hookLabel;        // 钩子显示的标签  
    QVBoxLayout* layout;      // 用于管理视图的布局  
    QLabel* sweatLabel;
    QPoint startPoint;
    QPoint endPoint;
    void clearBlocks();
    std::vector<QLabel*> displayedBlocks;  // 存储显示的 QLabel
    double rotationAngle = 45;
    std::shared_ptr<GameData> m_gameData;
};

#endif