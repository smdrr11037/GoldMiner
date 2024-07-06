#include "RunningPage.h"  
#include <QVBoxLayout>  

RunningPage::RunningPage(GameViewModel* viewModel, QWidget* parent) : QWidget(parent), m_viewModel(viewModel)
{
    // ���ñ���ͼƬ  
    QString imagePath = "image/running_background.jpg"; // ����ҳ��ı���ͼƬ·��  
    setStyleSheet("QWidget { background-image: url(" + imagePath + "); }");

    // ����������ʾ��ǩ  
    scoreLabel = new QLabel("Score: 0", this);

    // ��������Ŀ����ʾ��ǩ  ʵ����Ҫ���뵱ǰlevel���Ѷȶ�ӦĿ�����
    targetLabel = new QLabel("Target Points: 100", this);

    // �����˳���ť  
    exitButton = new QPushButton("�˳���Ϸ", this);

    // �����˳���ť�ĵ���źŵ��ۺ���  
    connect(exitButton, &QPushButton::clicked, this, &RunningPage::exitButtonClicked);

    // �������ֹ�����  
    layout = new QVBoxLayout(this);
    layout->addWidget(scoreLabel);
    layout->addWidget(targetLabel);
    layout->addWidget(exitButton);
}

void RunningPage::exitButtonClicked()
{
    // �����źţ�֪ͨ��Ϸ�˳�  
    emit exitGame();
}