// 需要实现的
// 监听 view 层的事件，并传递给 model 层
#ifndef GMVIEWMODEL_H
#define GMVIEWMODEL_H

#include <QObject>
#include <QTimer>
#include <chrono>

#include "../common/GoldMinerDef.h"
#include "../model/Model.h"
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
    void nextLevel();
    void stateChanged(GameState GameState);
    void pageChanged(Hook& hook, std::vector<Block*>& blocks);

public slots:
    void frameElapsedEmit();
    void handleStartGame();
    void handleNextLevel();
    void updateState(GameState GameState);
    void updatePage(Hook& hook, std::vector<Block*>& blocks);

private:
    QTimer *m_pTimer;
};



#endif