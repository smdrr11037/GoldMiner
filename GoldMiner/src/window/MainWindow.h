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
#include <QTimer>
#include <chrono>
#include "StartPage.h"  
#include "RunningPage.h"  
#include "CompletePage.h"
#include "GameOver.h"
#include "../common/GoldMinerDef.h"

const int WindowWidth = 2560;
const int WindowHeight = 1440;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

//在槽函数中需要发射的信号
signals:
    void startGame();
    void exitGame();
    void nextLevel();
    void playAgain();
    void pressKey();
    void timeOut();

//槽函数
private slots:
    void handleStartButtonClicked();
    void handleExitButtonClicked();
    void handleNextLevelButtonClicked();        //后续可带参数？哪一关
    void handlePlayAgainButtonClicked();
    void handlePressKey();          //RunningPage信号
    void handleWinGame();
    void handleLoseGame();
public slots:
    //void updatePage(const GameState& gameState);
    void updateState(const std::vector<Block>& blocks, const Hook& hook, const Player& player);
    //实际需要更多参数void runningRefreshPage(std::vector<Block> blocks, Hook hook, GameState gameState, Player player);

private:
    QStackedWidget* stackedWidget;
    StartPage* startPage;
    RunningPage* runningPage;
    CompletePage* completePage;
    GameOver* gameOverPage;
    QTimer* m_pTimer;
    //GameState m_gameState;       // 游戏状态
};

#endif // MAINWINDOW_H 