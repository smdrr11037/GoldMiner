#include "app.h"
GameAPP::GameAPP(){
    // 实例化各个部分
    window.resize(250, 150);
    window.setWindowTitle("Simple Qt Application");
}
GameAPP::~GameAPP(){
}
void GameAPP::run(){
    // 启动程序
    window.show();
}