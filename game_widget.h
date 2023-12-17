#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QFont>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "game_view.h"
#include <QSound>
#include <QTimer>
#include "gameover.h"
class game_widget : public QWidget
{
    Q_OBJECT
public:
    explicit game_widget(QWidget *parent = 0);
    gameView *game_view;
    void gameGuide();

//    int mapFlag;
    int flag;
    QTimer *timer;
    QTimer *timer1;
signals:
    
public slots:
    void timeCount();
    void nextBtnSlot();
//    void gameOverSlot();
private:
    QSound *gamebgm;
    QLabel *title;
    QLabel *title1;
    QLabel *timeTitle;
    QLabel *guideText;
    gameOver *gameover;
    QPushButton *nextBtn;
    QWidget *Parent;
};

#endif // GAME_WIDGET_H
