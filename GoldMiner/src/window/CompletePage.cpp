#include "CompletePage.h"  
#include <QVBoxLayout>  

CompletePage::CompletePage(CounterViewModel* viewModel, QWidget* parent) : QWidget(parent), m_viewModel(viewModel)
{
    // ���ñ���ͼƬ  
    QString imagePath = "image/victory_background.jpg"; // ��������ʤ��ҳ��ı���ͼƬ·��  
    setStyleSheet("QWidget { background-image: url(" + imagePath + "); }");

    // ������ʾ��Ϸʤ������ı�ǩ  
    victoryImageLabel = new QLabel(this);
    // ����ʤ������ͼƬ  
    QPixmap victoryImage("image/victory_image.png"); // ��������ʤ�������ͼƬ·��  
    victoryImageLabel->setPixmap(victoryImage);
    victoryImageLabel->setAlignment(Qt::AlignCenter);

    // ����������һ�ذ�ť  
    nextLevelButton = new QPushButton("��һ��", this);

    // ���Ӱ�ť�ĵ���źŵ��ۺ���  
    connect(nextLevelButton, &QPushButton::clicked, this, &CompletePage::nextLevelButtonClicked);

    // �������ֹ�����  
    layout = new QVBoxLayout(this);
    layout->addWidget(victoryImageLabel);
    layout->addWidget(nextLevelButton);
}

void CompletePage::nextLevelButtonClicked()
{
    // �����źţ�֪ͨ������һ��  
    emit nextLevel();
}