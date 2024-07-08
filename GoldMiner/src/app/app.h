// 组装各个部分
#ifndef APP_H
#define APP_H
#include <QWidget>
#include <QObject>
#include "../model/Model.h"
#include "../viewmodel/ViewModel.h"
// #include "../window/CompletePage.h"
// #include "../window/StartPage.h"
#include "../window/MainWindow.h"
#include "../viewmodel/ViewModel.h"

class GameAPP
{
private:
    MainWindow m_window;
    Model m_model;
    ViewModel m_viewModel;
public:
    GameAPP();
    ~GameAPP();
    void run();
};

#endif // APP_H