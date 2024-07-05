#include "CounterView.h"

CounterView::CounterView(CounterViewModel *viewModel, QWidget *parent) : QWidget(parent),
                                                                         m_viewModel(viewModel)
{
    countLabel = new QLabel("0", this);                   // 用于显示计数值，初始文本为 "0"
    incrementButton = new QPushButton("Increment", this); // 按钮文本为 "Increment"
    layout = new QVBoxLayout(this);                       // 垂直排列UI部件

    layout->addWidget(countLabel);
    layout->addWidget(incrementButton);
    setLayout(layout); // 布局设置为 CounterView 的主布局

    // 将 incrementButton 的 clicked 信号连接到 m_viewModel 的 increment 槽函数
    connect(incrementButton, &QPushButton::clicked, m_viewModel, &CounterViewModel::increment);
    // 将 m_viewModel 的 countChanged 信号连接到一个lambda函数。
    // 当 countChanged 信号发出时，lambda函数会被调用，更新 countLabel 的文本为新的计数值 newCount
    connect(m_viewModel, &CounterViewModel::countChanged, [this](int newCount)
            { countLabel->setText(QString::number(newCount)); });
}
