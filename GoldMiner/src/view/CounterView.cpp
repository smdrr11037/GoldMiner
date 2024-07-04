#include "CounterView.h"

CounterView::CounterView(CounterViewModel *viewModel, QWidget *parent) :
    QWidget(parent),
    m_viewModel(viewModel)
{
    countLabel = new QLabel("0", this);
    incrementButton = new QPushButton("Increment", this);
    layout = new QVBoxLayout(this);

    layout->addWidget(countLabel);
    layout->addWidget(incrementButton);
    setLayout(layout);

    connect(incrementButton, &QPushButton::clicked, m_viewModel, &CounterViewModel::increment);
    connect(m_viewModel, &CounterViewModel::countChanged, [this](int newCount) {
        countLabel->setText(QString::number(newCount));
    });
}
