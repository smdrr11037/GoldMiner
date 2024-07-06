#include "StartPage.h"  
#include <QVBoxLayout>  

StartPage::StartPage(CounterViewModel* viewModel, QWidget* parent) : QWidget(parent), m_viewModel(viewModel)
{
    // ���ñ���ͼƬ  
    //setStyleSheet("QWidget { background-image: url(:/background.jpg); }");
    QString imagePath = "image/start_background.jpg";
    setStyleSheet("QWidget { background-image: url(" + imagePath + "); }");

    // ������ʼ��Ϸ��ť  
    startButton = new QPushButton("��ʼ��Ϸ", this);

    // ���Ӱ�ť�ĵ���źŵ��ۺ���  
    connect(startButton, &QPushButton::clicked, this, &StartPage::startGame);

    // �������ֹ�����  
    layout = new QVBoxLayout(this);
    layout->addWidget(startButton);
}


void StartPage::startButtonClicked()
{
    // �����źţ�����Ϸ״̬�л�Ϊ Running  
    emit startGame(GameState::Running);
}