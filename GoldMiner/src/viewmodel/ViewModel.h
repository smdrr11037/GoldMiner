// 需要实现的
// 监听 view 层的事件，并传递给 model 层
#ifndef GMVIEWMODEL_H
#define GMVIEWMODEL_H

#include <QObject>
#include <QTimer>
#include <chrono>

#include "../common/GoldMinerDef.h"
#include "../common/timer.h"

#define FrameNumber 30

class ViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ViewModel(QObject *parent = nullptr);
    virtual ~ViewModel(){};

    // void startGame();
    // void pauseGame();
    // void resumeGame();
    // void stopGame();
    // void updateHookPosition(int x, int y);
    // void updateHookRotation(int angle);
    // void updateHookState(HookState state);
    // void updateBlocks(std::vector<Block> blocks);
    // void updateGameState(GameState state);
    // void updateScore(int score);
    // void updateLevel(int level);
    // void updateTargetScore(int targetScore);
signals:
    void frameElapsed();
    void startGame();
    void exitGame();
    void pageChanged(const GameState &GameState);
    void stateChanged(const std::vector<Block> &blocks, const Hook &hook, const Player &player);

public slots:
    void frameElapsedEmit();
    void handleStartGame();
    void handleExitGame();
    void updatePage(GameState &GameState);
    void updateState(std::vector<Block>& blocks, Hook& hook, Player &player);

private:
    QTimer *m_pTimer;
};



#endif