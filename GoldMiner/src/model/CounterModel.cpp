#include "CounterModel.h"

CounterModel::CounterModel(QObject *parent) : QObject(parent), m_count(0) {}

int CounterModel::count() const
{
    return m_count;
}

void CounterModel::increment()
{
    m_count++;
    emit countChanged(m_count); // emit关键字用于发出信号，并将当前计数器值 m_count 作为参数传递
}
