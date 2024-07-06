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
