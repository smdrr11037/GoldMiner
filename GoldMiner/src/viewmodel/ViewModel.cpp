#include "ViewModel.h"

ViewModel::ViewModel(QObject *parent = nullptr){
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1))/FrameNumber;
    m_pTimer = new QTimer();
    m_pTimer->setInterval(ms.count());
    connect(m_pTimer, &QTimer::timeout, this, &ViewModel::frameElapsedEmit);
    m_pTimer->start(); // 需要修改成接收信号决定开始或者结束


}


void ViewModel::frameElapsedEmit(){
    m_frameNumber++;
    emit void frameElapsed();
}