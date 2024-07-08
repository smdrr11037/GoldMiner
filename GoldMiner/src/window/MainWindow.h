#ifndef MAINWINDOW_H  
#define MAINWINDOW_H  

#include <QMainWindow>  
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QDir>
#include <QCoreApplication> 
#include <vector>
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
    void refreshPageSignal(const std::vector<Block>& blocks, const Hook& hook, const GameState& gameState);

//槽函数
private slots:
    void handleStartButtonClicked();
    void handleExitButtonClicked();
    void handleNextLevelButtonClicked();        //后续可带参数？哪一关
    void handlePassLevelSignal();
    void runningRefreshPage(const std::vector<Block>& blocks, const Hook& hook, const GameState& gameState);
    //实际需要更多参数void runningRefreshPage(std::vector<Block> blocks, Hook hook, GameState gameState, Player player);

private:
    QStackedWidget* stackedWidget;
    StartPage* startPage;
    RunningPage* runningPage;
    CompletePage* completePage;
};

#endif // MAINWINDOW_H 