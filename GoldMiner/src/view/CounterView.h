#ifndef COUNTERVIEW_H
#define COUNTERVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "../viewmodel/CounterViewModel.h"

class CounterView : public QWidget {
    Q_OBJECT

public:
    explicit CounterView(CounterViewModel *viewModel, QWidget *parent = nullptr);

private:
    CounterViewModel *m_viewModel;
    QLabel *countLabel;
    QPushButton *incrementButton;
    QVBoxLayout *layout;
};

#endif // COUNTERVIEW_H
