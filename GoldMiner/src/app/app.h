// 组装各个部分
#ifndef APP_H
#define APP_H
#include <QWidget>
#include <QObject>
// #include "../window/CompletePage.h"
// #include "../window/StartPage.h"
#include "../window/MainWindow.h"
#include "../viewmodel/ViewModel.h"
#include "../model/Model.h"

class GameAPP
{
private:
    std::shared_ptr<MainWindow> m_window;
    std::shared_ptr<ViewModel>  m_viewModel;
    std::shared_ptr<Model> m_model;
public:
    GameAPP();
    ~GameAPP();
    void run();
};

#endif // APP_H