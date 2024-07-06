#include "MainWindow.h"  
#include <QVBoxLayout>
#include <QMainWindow>  

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    startPage = new StartPage(this);
    runningPage = new RunningPage(this);
    completePage = new CompletePage(this);

    setCentralWidget(startPage);

    // MainWindow ���캯����  
    // ���� StartPage �� startGame �źŵ� MainWindow �Ĳۺ���  
    connect(startPage, &StartPage::startGame, this, &MainWindow::handleStartButtonClicked);

    // ���� RunningPage �� exitGame �źŵ� MainWindow �Ĳۺ���  
    connect(runningPage, &RunningPage::exitGame, this, &MainWindow::handleExitButtonClicked);

    // ���� Complete �� nextLevel �źŵ� MainWindow �Ĳۺ���  
    connect(completePage, &CompletePage::nextLevel, this, &MainWindow::handleNextLevelButtonClicked);

    //TODO : 
    //���� RunningPage �� 
    //���ģ�鷢���� ��ͨ�ء� �źŵ� MainWindow �Ĳۺ���  
    //connect(completePage, &CompletePage::nextLevel, this, &MainWindow::handleNextLevelButtonClicked);
}

// ������ʼ����ť����Ĳۺ���  
void MainWindow::handleStartButtonClicked(GameState gameState)
{
    if (gameState == GameState::Running) {
        setCentralWidget(runningPage);
    }

    // �����ź�֪ͨ viewmodel ��  
    emit StartToRunGame(GameState::Running);
}

// ���� ��Ϸ�С��˳�����ť����Ĳۺ���  
void MainWindow::handleExitButtonClicked()
{
    //�ݶ�ֱ�ӷ��ؿ�ʼ����
    setCentralWidget(startPage);

    // �����ź�֪ͨ viewmodel ��  
    emit RunToExit(GameState::GameOver);
}

// ���� ��Ϸ������comp���桰��һ�ء���ť����󣬽�����һ��RunningPage�Ĳۺ���  
void MainWindow::handleNextLevelButtonClicked()
{
    setCentralWidget(runningPage);

    // �����ź�֪ͨ viewmodel ��  
    emit CompleteToNextRun(GameState::Running);
}