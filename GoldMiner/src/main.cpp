/**
 * @brief 
 * @date 2024-7-6
 * @author GoldMiner Group
 * @version 1.0
 * @copyright 
 */

/*---- coding: utf-8 ----*/

#include <QApplication>
// 还没实现好
#include "app/app.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameAPP app;
    app.run();
    return a.exec();
}
