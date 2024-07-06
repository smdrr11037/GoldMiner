// 组装各个部分
#ifndef APP_H
#define APP_H
#include <QWidget>
// #include "../model/Model.h"
// #include "../viewmodel/ViewModel.h"
// #include "../window/CompletePage.h"
// #include "../window/StartPage.h"

class GameAPP
{
private:
    QWidget window;
public:
    GameAPP();
    ~GameAPP();
    void run();
};

#endif // APP_H