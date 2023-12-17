#ifndef MENUSELECTUI_H
#define MENUSELECTUI_H

#include <QWidget>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSound>
#include <QTimer>
#include <QMessageBox>
#include "game_widget.h"
#include "helpui.h"
#include "setui.h"
#include "gameover.h"
#include "gamerank.h"
#include "timecount.h"
class menuSelectUi : public QWidget
{
    Q_OBJECT
public:
    explicit menuSelectUi(QWidget *parent = 0);
    void menuUi();
//    void mousePressEvent ( QMouseEvent * event );
    QTimer *timer1;
signals:
    void exitBtnSignal();
public slots:
    void startBtnSlot();
    void setBtnSlot();
    void rankBtnSlot();
    void rankReturnSolt();
    void helpBtnSlot();
    void helpReturnSlot();
    void setReturnSlot();
    void exitBtnSlot();
    void gameOverSlot();
    void gameOverReturnSlot();
private:
    QLabel *title;
    QSound *menubgm;
    QPushButton *startBtn;
    QPushButton *setBtn;
    QPushButton *rankBtn;
    QPushButton *helpBtn;
    QPushButton *exitBtn;
    game_widget *game;
    helpUi * instruct;
    setUi * gameSet;
    gameRank *rank;
    gameOver *gameover;


};

#endif // MENUSELECTUI_H
