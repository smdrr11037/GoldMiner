#include <QApplication>
#include "view/CounterView.h"
#include "viewmodel/CounterViewModel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CounterViewModel viewModel;
    CounterView view(&viewModel);
    view.show();
    // 启动主事件循环并等待用户事件
    return app.exec();
}
