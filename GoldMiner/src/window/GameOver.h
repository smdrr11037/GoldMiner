// ß∞‹“≥√Ê
#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "../common/GoldMinerDef.h"

class GameOver : public QWidget
{
    Q_OBJECT

public:
    explicit GameOver(QWidget* parent = nullptr);

signals:
    void replay();

private slots:
    void replayButtonClicked();

private:
    QLabel* overImageLabel;
    QPushButton* replayLevelButton;
    QVBoxLayout* layout;
};

#endif