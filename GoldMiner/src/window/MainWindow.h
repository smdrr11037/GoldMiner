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
    void setGameData(std::shared_ptr<GameData> gameData);

//在槽函数中需要发射的信号
signals:
    void refreshPageSignal(const std::vector<Block>& blocks, const Hook& hook, const Player& player);
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
    
public slots:
    //void updatePage(const GameState& gameState);
    void handleWinGame();
    void handleLoseGame();
    void updateState();

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