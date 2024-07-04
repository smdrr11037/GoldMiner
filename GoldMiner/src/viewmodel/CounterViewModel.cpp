#include "CounterViewModel.h"

CounterViewModel::CounterViewModel(QObject *parent) : QObject(parent) {
    connect(&m_model, &CounterModel::countChanged, this, &CounterViewModel::countChanged);
}

int CounterViewModel::count() const {
    return m_model.count();
}

void CounterViewModel::increment() {
    m_model.increment();
}
