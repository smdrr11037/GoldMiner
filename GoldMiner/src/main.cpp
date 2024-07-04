#include <QApplication>
#include "view/CounterView.h"
#include "viewmodel/CounterViewModel.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CounterViewModel viewModel;
    CounterView view(&viewModel);
    view.show();

    return app.exec();
}
