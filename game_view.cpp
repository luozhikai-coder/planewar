#include "game_view.h"
#include "qmath.h"
extern QSound *bgm;
int bulletFlag;
int gamescore;
bool gameOverFlag;
extern int gameMode;
extern int bombFlag;
gameView::gameView(QWidget *parent): QGraphicsView(parent)
{

    this->setStyleSheet("background: transparent;border:0px");
    this->setFixedSize(480,852);
    this->setAutoFillBackground(true);
    pScene = new QGraphicsScene();
    //这是必须的场景与视图重合
    pScene->setSceneRect(0, 0,480,852);
    // 为视图设置场景
    this->setScene(pScene);


    //方向键标志位
    key_r = false;
    key_l = false;
    key_u = false;
    key_d = false;
    key_s = false;
    key_b = false;

    //鼠标控制标志位
    m_bIsGameStart=false;
    m_bIsGameOver=false;
    m_bIsMoving=false;

    //游戏暂停按钮
    this->gameStopBtn = new QPushButton(this);
    this->gameStopBtn->setIcon(QIcon("image/game_pause_pressed.png"));
    this->gameStopBtn->setIconSize(QSize(52,45));
    this->gameStopBtn->setFlat(true);
    this->gameStopBtn->setFocusPolicy(Qt::NoFocus);
    this->gameStopBtn->move(20,20);
    //得分
    this->score = new QLabel(this);
    this->score->setText("Score:0");
    this->score->setFont(QFont("Jokerman", 16, 75));
    this->score->setGeometry(80,25,200,30);
//    this->score->move(80,25);
    //炸弹道具
    this->bomb = new QPushButton(this);
    this->bomb->setIcon(QIcon("image/bomb.png"));
    this->bomb->setIconSize(QSize(63,53));
    this->bomb->setFlat(true);
    this->bomb->setFocusPolicy(Qt::NoFocus);
    this->bomb->move(10,this->height()-80);

    //道具数量
    this->bombcount = new QLabel(this);
    this->bombcount->setText("X 0");
    this->bombcount->setFont(QFont("Jokerman", 16, 75));
    this->bombcount->setGeometry(80,this->height()-80,200,30);
    //我放飞机
    pItem = new item_my_plane("image/hero.gif",this->pScene,PLANE_TYPE_MY1);
    //设置初始化位置
    pItem->setPos(this->width()/2-60,700);

    //等待按键
    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(plane_move()));
    timer1->start(15);
    gameOverFlag = false;
    //产生子弹
    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(bullet_produce()));
    timer2->start(70);


    //敌方飞机
    timer4 = new QTimer(this);
    connect(timer4,SIGNAL(timeout()),this,SLOT(enemy_produce()) );
    timer4->start(1000);

    //随机道具产生
    timer5 = new QTimer(this);
    connect(timer5,SIGNAL(timeout()),this,SLOT(prop_produce()) );
    timer5->start(5000);

    //游戏暂停按钮
    connect(gameStopBtn,SIGNAL(clicked()),this,SLOT(gameStop()));

    //游戏图元移动
    timer6 = new QTimer(this);
    connect(timer6,SIGNAL(timeout()),this->pScene,SLOT(advance()));
    timer6->start(100);

//    // 游戏结束
//    timer3 = new QTimer(this);
//    connect(timer3,SIGNAL(timeout()),this,SLOT(gameOverSlot()) );
//    timer3->start(50);
    //更新分数
    timer7 = new QTimer(this);
    connect(timer7,SIGNAL(timeout()),this,SLOT(updateScore()));
    timer7->start(100);
}


void gameView::keyPressEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat())
    {
        if(!key_l && event->key() == Qt::Key_Left)
        {
            qDebug()<<"Key_Left";
            key_l = true;
        }
        else if(!key_u && event->key() == Qt::Key_Up)
        {
            qDebug()<<"Key_Up";
            key_u = true;
        }
        else if(!key_r && event->key() == Qt::Key_Right)
        {
            qDebug()<<"Key_Right";
            key_r = true;
        }
        else if(!key_d && event->key() == Qt::Key_Down)
        {
            qDebug()<<"Key_Down";
            key_d = true;
        }
        else if(event->key() == Qt::Key_B)
        {
            qDebug()<<"Key_B";
            key_b = true;
        }
        else if(event->key() == Qt::Key_Space)
        {
            qDebug()<<"Key_Space";

            key_s = true;
        }
    }

}

void gameView::keyReleaseEvent(QKeyEvent *event)
{
    if ( !event->isAutoRepeat())
    {
        if ( key_l && event->key() == Qt::Key_Left)
        {
            qDebug()<<"keyRelease  Key_Left";
            key_l = false;
        }
        else if ( key_u && event->key() == Qt::Key_Up)
        {
            qDebug()<<"keyRelease Key_Up";
            key_u = false;
        }
        else if (key_d && event->key() == Qt::Key_Down)
        {
            qDebug()<<"keyRelease Key_Down";
            key_d = false;
        }
        else if ( key_r && event->key() == Qt::Key_Right)
        {
            qDebug()<<"keyRelease Key_Right";
            key_r = false;
        }
        else if(key_b && event->key() == Qt::Key_B)
        {
            qDebug()<<"keyRelease Key_B";
            key_b = false;
        }
        else if ( key_s && event->key() == Qt::Key_Space)
        {
            qDebug()<<"keyRelease Key_Space";
            key_s = false;
        }
    }
}
void gameView::mouseMoveEvent(QMouseEvent *event)
{

    QPointF pos = event->pos();
    qDebug()<<"pos"<<pos;
    QPointF posnow;
    if(!m_bIsGameOver && m_bIsMoving)
    {
        if(pos.x()>this->width()-100)  //超出右边界
        {
            posnow.rx()=this->width()-100;
        }
        else if(pos.x()<2)       //超出左边界
        {
            posnow.rx()=2;
        }
        else
        {
            posnow.rx() =pos.x();
        }
        if(pos.y()<10)       //超出上边界
        {
            posnow.ry()=10;
        }
        else if (pos.y()>this->height()-124)  //超出下边界
        {
            posnow.ry()=this->height()-124;
        }
        else
        {
            posnow.ry() =pos.y();
        }
        pItem->setPos(posnow);
    }
}

//更新分数和道具数
void gameView::updateScore()
{
    QString scoreText;
    scoreText = QString("Score:%1").arg(gamescore);
    qDebug()<<scoreText;
    this->score->setText(scoreText);
    QString bombCount;
    bombCount = QString("X %1").arg(bombFlag);
    this->bombcount->setText(bombCount);
}
//道具随机生成
void gameView::prop_produce()
{

    static int time;
    if(time++%50 == 0)
    {
        switch(qrand()%2)
        {
        case 0:
        {
            prop.append(new item_prop("image/prop_type_0.png",this->pScene,PROP_TYPE1));
            prop.back()->setPos(qrand()%400,-1);
        }
        break;
        case 1:
        {
            prop.append(new item_prop("image/prop_type_1.png",this->pScene,PROP_TYPE2));
            prop.back()->setPos(qrand()%400,-1);
        }
        break;
        }
    }
}

void gameView::enemy_produce()
{
    static int count = 20;
    QTime time;//随机数种子
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    switch(gameMode)
    {
        //简单模式,固定飞机数量3
        case 1:
        {
        if(enemy_plane.size()<3)
        {
            switch(qrand()%2)
            {
            case 0:
            {
                enemy_plane.append(new item_enemy_plane("image/enemy0.png",this->pScene,ENEMY1));
            }
            break;
            case 1:
            {
                enemy_plane.append(new item_enemy_plane("image/enemy1.png",this->pScene,ENEMY2));
            }
            break;
            }
        }
        }
        break;
        //普通模式,固定飞机数量5
        case 2:
        {
        if(enemy_plane.size()<5)
        {
            switch(qrand()%2)
            {
            case 0:
            {
                enemy_plane.append(new item_enemy_plane("image/enemy0.png",this->pScene,ENEMY1));
            }
            break;
            case 1:
            {
                enemy_plane.append(new item_enemy_plane("image/enemy1.png",this->pScene,ENEMY2));
            }
            break;
            }
        }
        }
        break;
        //困难模式,固定飞机数量10
        case 3:
        {
        if(enemy_plane.size()<10)
        {
            switch(qrand()%2)
            {
            case 0:
            {
                enemy_plane.append(new item_enemy_plane("image/enemy0.png",this->pScene,ENEMY1));
            }
            break;
            case 1:
            {
                enemy_plane.append(new item_enemy_plane("image/enemy1.png",this->pScene,ENEMY2));
            }
            break;
            }
        }
        }
        break;
    default:
            return;
    }

    count--;
    if(count == 0)
    {
         item_enemy_plane *boss = new item_enemy_plane("image/enemy2.png",this->pScene,ENEMY3);
         count = 20;
    }
}

//游戏暂停
void gameView::gameStop()
{
    static int flag = 0;
    if(flag == 0)
    {
        timer1->stop();
        timer2->stop();
        timer5->stop();
        timer4->stop();
        timer6->stop();
        bgm->stop();
        flag = 1;
        this->gameStopBtn->setIcon(QIcon("image/game_resume_pressed.png"));
    }
    else
    {
        timer1->start();
        timer2->start();
        timer5->start();
        timer4->start();
        timer6->start();
        bgm->play();
        flag = 0;
        this->gameStopBtn->setIcon(QIcon("image/game_pause_pressed.png"));
    }

}
void gameView::plane_move()
{
    int  displacement = 6;
    if(key_l == true)//左移动
    {
        if(pItem->x()-displacement >0)
        {
            pItem->moveBy(-displacement,0);
        }
    }
    else if(key_r == true) //右移动
    {
        if(pItem->x()+displacement <480-100)
        {
            pItem->moveBy(displacement,0);
        }
    }
    else if(key_u == true) //上移动
    {
        if(pItem->y() - displacement > 10)
        {
            pItem->moveBy(0,-displacement);
        }
    }
    else if(key_d == true)//下移动
    {
        if(pItem->y() + displacement < 852-124)
        {
            pItem->moveBy(0,displacement);
        }
    }
}

//我方子弹
void gameView::bullet_produce()
{
    static int time;
    if(key_s == true)
    {
        switch(bulletFlag)
        {
        case 0:
        {
            //正常状态下子弹
            item_my_bullet *my_bullet = new item_my_bullet("image/bullet2.png",this->pScene);
            my_bullet->setPos(pItem->x()+pItem->getQpixmap().width()/2-4,pItem->y()-20);
//            my_bullet.append(new item_my_bullet("image/bullet2.png",this->pScene));
//            my_bullet.back()->setPos(pItem->x()+pItem->getQpixmap().width()/2-4,pItem->y()-20); //设置初始化位置
        }
        break;
        case 1:
        {
            //吃到道具后子弹加倍，持续一段时间后重新回到原状态
            if(time++<=50)
            {
                item_my_bullet *my_bullet_up = new item_my_bullet("image/bullet1.png",this->pScene);
                item_my_bullet *my_bullet_up1 = new item_my_bullet("image/bullet1.png",this->pScene);
                my_bullet_up->setPos(pItem->x()+pItem->getQpixmap().width()/2+10,pItem->y()-20);
                my_bullet_up1->setPos(pItem->x()+pItem->getQpixmap().width()/2-18,pItem->y()-20);
//                my_bullet.append(new item_my_bullet("image/bullet1.png",this->pScene));
//                my_bullet.append(new item_my_bullet("image/bullet1.png",this->pScene));
//                my_bullet.first()->setPos(pItem->x()+pItem->getQpixmap().width()/2+10,pItem->y()-20);
//                my_bullet.back()->setPos(pItem->x()+pItem->getQpixmap().width()/2-18,pItem->y()-20); //设置初始化位置

            }
            if(time > 50)
            {
                bulletFlag = 0;
                time = 0;
            }
        }
        break;
        }

    }

}

//我方子弹移动
void gameView::my_bullet_move()
{
    for(int j = 0; j < my_bullet.size(); ++j)
    {
        my_bullet[j]->moveBy(0,-50);
    }

    if(my_bullet.size()>20)
    {
        if(my_bullet.at(1)->y()<0)
        {
            delete my_bullet.at(1);
            my_bullet.removeAt(1);
            qDebug()<<"delete my_bullet";
        }
    }
}


void gameView::mousePressEvent(QMouseEvent *event)
{
    QPointF pos=event->pos();
    if(!m_bIsGameOver)
    {
        //设置光标样式
        setCursor(Qt::BlankCursor);
        this->m_bIsMoving=true;
        // const int MaxDistance=100*100;
        //计算鼠标落点和飞机坐标的距离
        // int iDistance=qPow(pItem->pos().x()-pos.x(),2)+qPow(pItem->pos().y()-pos.y(),2);
        //if(iDistance<MaxDistance)
    }
}

void gameView::mouseReleaseEvent(QMouseEvent *event)
{
    if(!m_bIsGameOver)
    {
        setCursor(Qt::ArrowCursor);
        this->m_bIsMoving=false;
    }
}



