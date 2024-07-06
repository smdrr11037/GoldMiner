#include "app.h"
GameAPP::GameAPP(){
    //window.resize(1024, 1024); // 设置初始大小，这里假设图片的分辨率为 800x600  
    //window.setWindowTitle("Gold Miner"); // 设置窗口标题
}
GameAPP::~GameAPP(){
}
void GameAPP::run(){
    // 启动程序
    window.show();
}