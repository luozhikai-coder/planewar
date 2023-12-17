#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
#include <QPushButton>
#include "item_my_plane.h"
#include "item_my_bullet.h"
#include "item_enemy_plane.h"
#include "item_enemy_bullet.h"
#include "item_prop.h"
#include "gameover.h"
#include <QTime>
#include <QSound>
#include <Phonon/AudioOutput>
#include <Phonon/MediaObject>

class gameView : public QGraphicsView
{
    Q_OBJECT
public:
    gameView(QWidget *parent = 0);
    QGraphicsScene * pScene;                //场景
    item_my_plane * pItem;                //飞机图元
    QList<item_my_bullet *> my_bullet;  //子弹链表

    QList<item_enemy_plane *>  enemy_plane; //敌机链表
    QList<item_enemy_bullet *> enemy_bullet;//敌机子弹链表

    QList<item_prop *> prop;    //道具

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

//    void enemy_plane_produce();
//    void enemy_plane_move();

    bool key_r;  //按键状态
    bool key_u;
    bool key_l;
    bool key_d;
    bool key_s;
    bool key_b;
    QTimer * timer1;
    QTimer * timer2;
    QTimer * timer3;
    QTimer * timer4;
    QTimer * timer5;
    QTimer * timer6;
    QTimer * timer7;
public slots:
    void plane_move();
    void bullet_produce();
    void my_bullet_move();
//    void enemy_bullet_move();
    void prop_produce();
//    void prop_move();
    void gameStop();
    void enemy_produce();
    void updateScore();

private:
    QLabel *score;
    QLabel *bombcount;
    QPushButton *gameStopBtn;
    QPushButton *bomb;
    gameOver * gameover;
    bool m_bIsGameStart;
    bool m_bIsGameOver;
    bool m_bIsMoving;

};

#endif // GAME_VIEW_H
