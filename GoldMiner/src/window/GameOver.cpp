#include "GameOver.h"  
#include <QVBoxLayout>  

GameOver::GameOver(QWidget* parent) : QWidget(parent)
{
    // �������水ť  
    replayLevelButton = new QPushButton("Replay This Level", this);
    replayLevelButton->setStyleSheet("background-color: blue; color: white;font-weight: bold;font-family: Arial; font-size: 40px; border-radius: 50px; padding: 30px 100px;");

    // ���Ӱ�ť�ĵ���źŵ��ۺ���  
    connect(replayLevelButton, &QPushButton::clicked, this, &GameOver::replayButtonClicked);

    // �������ֹ�����  
    layout = new QVBoxLayout(this);
    layout->addStretch(1);  // ���һ�����ɣ�����ť�Ƶ��ײ�  
    layout->addWidget(replayLevelButton, 0.8, Qt::AlignCenter);  // ����ť���ڲ��ֵĵײ���ˮƽ����
}

void GameOver::replayButtonClicked()
{
    // �����źţ�֪ͨ������һ��  
    emit replay();
}