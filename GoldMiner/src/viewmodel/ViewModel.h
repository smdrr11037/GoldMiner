// 需要实现的
// 监听 view 层的事件，并传递给 model 层
#ifndef GMVIEWMODEL_H
#define GMVIEWMODEL_H

#include <QObject>
#include <QTimer>
#include <chrono>

#include "../common/GoldMinerDef.h"
#include "../model/Model.h"

class ViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ViewModel(QObject *parent = nullptr);
    virtual ~ViewModel(){};

signals:
// To View
    void winGame();
    void loseGame();
    void stateChanged(const std::vector<Block> &blocks, const Hook &hook, const Player &player);

public slots:
    void handleTimeOut();
    // from View
    void handleStartGame();
    void handleExitGame();
    void handlePlayAgain();
    void handleNextLevel();
    void handlePressKey();

    // from Model
    void updateState(const std::vector<Block>& blocks, const Hook& hook, const Player &player);
private:
    Model *m_model;
};



#endif