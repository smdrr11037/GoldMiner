#ifndef COUNTERVIEW_H
#define COUNTERVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "../viewmodel/CounterViewModel.h"
// 继承自 QWidget，表示这个类是一个窗口部件
class CounterView : public QWidget
{
    Q_OBJECT

public:
    explicit CounterView(CounterViewModel *viewModel, QWidget *parent = nullptr);

private:
    CounterViewModel *m_viewModel;
    QLabel *countLabel;           // 指向 QLabel 对象的指针，用于显示计数值
    QPushButton *incrementButton; // 指向 QPushButton 对象的指针，用于增加计数值的按钮
    QVBoxLayout *layout;          // 指向 QVBoxLayout 对象的指针，用于管理视图的布局
};

#endif // COUNTERVIEW_H
