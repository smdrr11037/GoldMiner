#include "CounterModel.h"

CounterModel::CounterModel(QObject *parent) : QObject(parent), m_count(0) {}

int CounterModel::count() const {
    return m_count;
}

void CounterModel::increment() {
    m_count++;
    emit countChanged(m_count);
}
