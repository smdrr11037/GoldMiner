#ifndef COUNTERVIEWMODEL_H
#define COUNTERVIEWMODEL_H

#include <QObject>
#include "../model/CounterModel.h"
// 继承自 Qt 中所有对象的基类
class CounterViewModel : public QObject
{
    Q_OBJECT // 告诉 Qt 的元对象编译器（moc）为这个类生成额外的代码，以支持信号和槽以及其他元对象功能
    // 定义了一个名为 `count` 的属性
    // `READ` 关键字指定了该属性的读取器方法是 `count()`
    // `NOTIFY` 关键字指定了当该属性改变时会发出 `countChanged` 信号
    Q_PROPERTY(int count READ count NOTIFY countChanged)

        public : explicit CounterViewModel(QObject *parent = nullptr);

    int count() const;

public slots: // `public slots` 关键字定义了一个槽 `increment`，它会被其他信号触发，用于增加计数值
    void increment();

signals: // `signals` 关键字定义了一个信号 `countChanged`，它在计数值改变时发出
    void countChanged(int newCount);

private:
    CounterModel m_model;
};

#endif // COUNTERVIEWMODEL_H
