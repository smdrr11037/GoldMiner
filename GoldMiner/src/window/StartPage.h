// 游戏开始界面
// 需要实现的功能：
// 1. 显示游戏背景图片（可以在角落写上图片说明）
// 2. 显示开始游戏按钮
#ifndef START_PAGE_H
#define START_PAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include "../common/GoldMinerDef.h"
// 继承自 QWidget，表示这个类是一个窗口部件
class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);
    /*~StartPage() {
        delete startButton;
        delete layout;
    }*/

signals:
    void startGame(GameState gameState);

private slots:
    void startButtonClicked();

private:
    QPushButton *startButton; // 指向 QPushButton 对象的指针，用于游戏开始的按钮
    QVBoxLayout *layout;      // 指向 QVBoxLayout 对象的指针，用于管理视图的布局
};

//class RoundButton : public QPushButton
//{
//public:
//    RoundButton(const QString& text, QWidget* parent = nullptr) : QPushButton(text, parent) {}
//
//protected:
//    void paintEvent(QPaintEvent* event) override
//    {
//        Q_UNUSED(event);
//        QPainter painter(this);
//        painter.setRenderHint(QPainter::Antialiasing, true);
//        painter.setBrush(QColor("yellow"));
//        painter.setPen(Qt::black);
//        painter.drawEllipse(0, 0, width(), height());
//        painter.drawText(rect(), Qt::AlignCenter, text());
//    }
//};

#endif // START_PAGE_H