//ʧ��ҳ��
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
    void replay(); // ������һ�ص��ź�  

private slots:
    void replayButtonClicked(); // ��һ�ذ�ť���ʱ�Ĳۺ���  

private:
    QLabel* overImageLabel;    // ��ʾ��Ϸʤ������ı�ǩ  
    QPushButton* replayLevelButton; // ������һ�ذ�ť  
    QVBoxLayout* layout;           // ���ڹ�����ͼ�Ĳ���  
};

#endif