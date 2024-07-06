#ifndef MAINWINDOW_H  
#define MAINWINDOW_H  

#include <QMainWindow>  
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "StartPage.h"  
#include "RunningPage.h"  
#include "CompletePage.h"
#include "../common/GoldMinerDef.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow(){}

//�ڲۺ�������Ҫ������ź�
signals:
    void StartToRunGame(GameState gameState);
//signals:���Ӧ���Ǳ��ģ�鴫�����źţ��жϼ�ʱ�������Ƿ�ͨ��
//    void RunToCompleteGame(GameState gameState);
signals:
    void RunToExit(GameState gameState);
signals:
    void CompleteToNextRun(GameState gameState);

//��ʵ�ֲۺ���
private slots:
    void handleStartButtonClicked(GameState gameState);
private slots:
    void handleExitButtonClicked();
private slots:
    void handleNextLevelButtonClicked();        //�����ɴ���������һ��

private:
    StartPage* startPage;
    RunningPage* runningPage;
    CompletePage* completePage;
};

#endif // MAINWINDOW_H 