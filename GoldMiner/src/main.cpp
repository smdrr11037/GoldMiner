﻿#include <QApplication>
#include <QWidget>
// 还没实现好
// #include "app/app.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    // demo：产生一个空白的窗口
    window.resize(250, 150);
    window.setWindowTitle("Simple Qt Application");
    window.show();

    return app.exec();
}
