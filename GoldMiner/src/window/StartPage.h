// 游戏开始界面
// 需要实现的功能：
// 1. 显示游戏背景图片（可以在角落写上图片说明）
// 2. 显示开始游戏按钮
#ifndef START_PAGE_H
#define START_PAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "../viewmodel/ViewModel.h"
// 继承自 QWidget，表示这个类是一个窗口部件
class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(CounterViewModel *viewModel, QWidget *parent = nullptr);

private:
    ViewModel *m_viewModel;
    QPushButton *startButton; // 指向 QPushButton 对象的指针，用于游戏开始的按钮
    QVBoxLayout *layout;      // 指向 QVBoxLayout 对象的指针，用于管理视图的布局
};

#endif // START_PAGE_H