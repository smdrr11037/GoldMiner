// 过关后来到这个界面
// 需要：
// 1. 显示游戏胜利的画面
// 2. 有一个 nextLevel 的按钮，点击后进入下一关
// 后续还可以加入道具购买功能等等
#ifndef COMPLETE_PAGE_H
#define COMPLETE_PAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "../common/GoldMinerDef.h"

class CompletePage : public QWidget
{
    Q_OBJECT

public:
    explicit CompletePage(CounterViewModel* viewModel, QWidget* parent = nullptr);

signals:
    void nextLevel(); // 进入下一关的信号  

private slots:
    void nextLevelButtonClicked(); // 下一关按钮点击时的槽函数  

private:
    CounterViewModel* m_viewModel;
    QLabel* victoryImageLabel;    // 显示游戏胜利画面的标签  
    QPushButton* nextLevelButton; // 进入下一关按钮  
    QVBoxLayout* layout;           // 用于管理视图的布局  
};

#endif