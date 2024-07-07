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
    ~MainWindow();

//在槽函数中需要发射的信号
signals:
    void StartToRunGame(GameState gameState);
    void RunToExit(GameState gameState);
    void CompleteToNextRun(GameState gameState);
//signals:这个应该是别的模块传来的信号，判断计时结束后是否通关
//    void RunToCompleteGame(GameState gameState);

//槽函数
private slots:
    void handleStartButtonClicked();
    void handleExitButtonClicked();
    void handleNextLevelButtonClicked();        //后续可带参数？哪一关

private:
    StartPage* startPage;
    RunningPage* runningPage;
    CompletePage* completePage;
};

#endif // MAINWINDOW_H 