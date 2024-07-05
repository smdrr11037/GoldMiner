#include "CounterViewModel.h"

CounterViewModel::CounterViewModel(QObject *parent) : QObject(parent)
{
    // 将m_model对象的countChanged信号连接到当前CounterViewModel对象的countChanged信号。
    // 当m_model的countChanged信号被发出时，CounterViewModel的countChanged信号也会被发出
    connect(&m_model, &CounterModel::countChanged, this, &CounterViewModel::countChanged);
    // QObject::connect(sender, signal, receiver, slot_or_signal);
    // sender: 信号的发送者，可以是任意QObject的实例，也可以是信号的发送者的类名
    // signal: 信号的名称，可以是任意信号名称
    // receiver: 信号的接收者，可以是任意QObject的实例，也可以是信号的接收者的类名
    // slot_or_signal: 信号的槽函数，可以是任意的函数指针，也可以是槽函数的名称
    // CounterViewModel 作为中介，可以将 CounterModel 中的变化通知到外部视图
}

int CounterViewModel::count() const
{
    return m_model.count();
}

void CounterViewModel::increment()
{
    m_model.increment();
}
