// 需要实现的
// 监听 view 层的事件，并传递给 model 层
#ifndef GMVIEWMODEL_H
#define GMVIEWMODEL_H

#include <QObject>
#include <QTimer>
#include <chrono>

#include "../common/GoldMinerDef.h"
#include "../common/timer.h"


class ViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ViewModel(QObject *parent = nullptr);
    virtual ~ViewModel(){};

signals:
// To Model
    void frameElapsed();
    void startGame();
    void exitGame();
    void playAgain();
    void nextLevel();
    void pressKey();
// To View
    void pageChanged(const GameState &GameState);
    void stateChanged(const std::vector<Block> &blocks, const Hook &hook, const Player &player);

public slots:
    void frameElapsedEmit();
    // from View
    void handleStartGame();
    void handleExitGame();
    void handlePlayAgain();
    void handleNextLevel();
    void handlePressKey();
    // from Model
    void updatePage(const GameState &GameState);
    void updateState(const std::vector<Block>& blocks, const Hook& hook, const Player &player);
    

private:
    QTimer *m_pTimer;
};



#endif