//失败页面
#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "../common/GoldMinerDef.h"

class GameOver : public QWidget
{
    Q_OBJECT

public:
    explicit GameOver(QWidget* parent = nullptr);

signals:
    void replay(); // 进入下一关的信号  

private slots:
    void replayButtonClicked(); // 下一关按钮点击时的槽函数  

private:
    QLabel* overImageLabel;    // 显示游戏胜利画面的标签  
    QPushButton* replayLevelButton; // 进入下一关按钮  
    QVBoxLayout* layout;           // 用于管理视图的布局  
};

#endif