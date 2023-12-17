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
    //���Ǳ���ĳ�������ͼ�غ�
    pScene->setSceneRect(0, 0,480,852);
    // Ϊ��ͼ���ó���
    this->setScene(pScene);


    //�������־λ
    key_r = false;
    key_l = false;
    key_u = false;
    key_d = false;
    key_s = false;
    key_b = false;

    //�����Ʊ�־λ
    m_bIsGameStart=false;
    m_bIsGameOver=false;
    m_bIsMoving=false;

    //��Ϸ��ͣ��ť
    this->gameStopBtn = new QPushButton(this);
    this->gameStopBtn->setIcon(QIcon("image/game_pause_pressed.png"));
    this->gameStopBtn->setIconSize(QSize(52,45));
    this->gameStopBtn->setFlat(true);
    this->gameStopBtn->setFocusPolicy(Qt::NoFocus);
    this->gameStopBtn->move(20,20);
    //�÷�
    this->score = new QLabel(this);
    this->score->setText("Score:0");
    this->score->setFont(QFont("Jokerman", 16, 75));
    this->score->setGeometry(80,25,200,30);
//    this->score->move(80,25);
    //ը������
    this->bomb = new QPushButton(this);
    this->bomb->setIcon(QIcon("image/bomb.png"));
    this->bomb->setIconSize(QSize(63,53));
    this->bomb->setFlat(true);
    this->bomb->setFocusPolicy(Qt::NoFocus);
    this->bomb->move(10,this->height()-80);

    //��������
    this->bombcount = new QLabel(this);
    this->bombcount->setText("X 0");
    this->bombcount->setFont(QFont("Jokerman", 16, 75));
    this->bombcount->setGeometry(80,this->height()-80,200,30);
    //�ҷŷɻ�
    pItem = new item_my_plane("image/hero.gif",this->pScene,PLANE_TYPE_MY1);
    //���ó�ʼ��λ��
    pItem->setPos(this->width()/2-60,700);

    //�ȴ�����
    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(plane_move()));
    timer1->start(15);
    gameOverFlag = false;
    //�����ӵ�
    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(bullet_produce()));
    timer2->start(70);


    //�з��ɻ�
    timer4 = new QTimer(this);
    connect(timer4,SIGNAL(timeout()),this,SLOT(enemy_produce()) );
    timer4->start(1000);

    //������߲���
    timer5 = new QTimer(this);
    connect(timer5,SIGNAL(timeout()),this,SLOT(prop_produce()) );
    timer5->start(5000);

    //��Ϸ��ͣ��ť
    connect(gameStopBtn,SIGNAL(clicked()),this,SLOT(gameStop()));

    //��ϷͼԪ�ƶ�
    timer6 = new QTimer(this);
    connect(timer6,SIGNAL(timeout()),this->pScene,SLOT(advance()));
    timer6->start(100);

//    // ��Ϸ����
//    timer3 = new QTimer(this);
//    connect(timer3,SIGNAL(timeout()),this,SLOT(gameOverSlot()) );
//    timer3->start(50);
    //���·���
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
        if(pos.x()>this->width()-100)  //�����ұ߽�
        {
            posnow.rx()=this->width()-100;
        }
        else if(pos.x()<2)       //������߽�
        {
            posnow.rx()=2;
        }
        else
        {
            posnow.rx() =pos.x();
        }
        if(pos.y()<10)       //�����ϱ߽�
        {
            posnow.ry()=10;
        }
        else if (pos.y()>this->height()-124)  //�����±߽�
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

//���·����͵�����
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
//�����������
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
    QTime time;//���������
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    switch(gameMode)
    {
        //��ģʽ,�̶��ɻ�����3
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
        //��ͨģʽ,�̶��ɻ�����5
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
        //����ģʽ,�̶��ɻ�����10
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

//��Ϸ��ͣ
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
    if(key_l == true)//���ƶ�
    {
        if(pItem->x()-displacement >0)
        {
            pItem->moveBy(-displacement,0);
        }
    }
    else if(key_r == true) //���ƶ�
    {
        if(pItem->x()+displacement <480-100)
        {
            pItem->moveBy(displacement,0);
        }
    }
    else if(key_u == true) //���ƶ�
    {
        if(pItem->y() - displacement > 10)
        {
            pItem->moveBy(0,-displacement);
        }
    }
    else if(key_d == true)//���ƶ�
    {
        if(pItem->y() + displacement < 852-124)
        {
            pItem->moveBy(0,displacement);
        }
    }
}

//�ҷ��ӵ�
void gameView::bullet_produce()
{
    static int time;
    if(key_s == true)
    {
        switch(bulletFlag)
        {
        case 0:
        {
            //����״̬���ӵ�
            item_my_bullet *my_bullet = new item_my_bullet("image/bullet2.png",this->pScene);
            my_bullet->setPos(pItem->x()+pItem->getQpixmap().width()/2-4,pItem->y()-20);
//            my_bullet.append(new item_my_bullet("image/bullet2.png",this->pScene));
//            my_bullet.back()->setPos(pItem->x()+pItem->getQpixmap().width()/2-4,pItem->y()-20); //���ó�ʼ��λ��
        }
        break;
        case 1:
        {
            //�Ե����ߺ��ӵ��ӱ�������һ��ʱ������»ص�ԭ״̬
            if(time++<=50)
            {
                item_my_bullet *my_bullet_up = new item_my_bullet("image/bullet1.png",this->pScene);
                item_my_bullet *my_bullet_up1 = new item_my_bullet("image/bullet1.png",this->pScene);
                my_bullet_up->setPos(pItem->x()+pItem->getQpixmap().width()/2+10,pItem->y()-20);
                my_bullet_up1->setPos(pItem->x()+pItem->getQpixmap().width()/2-18,pItem->y()-20);
//                my_bullet.append(new item_my_bullet("image/bullet1.png",this->pScene));
//                my_bullet.append(new item_my_bullet("image/bullet1.png",this->pScene));
//                my_bullet.first()->setPos(pItem->x()+pItem->getQpixmap().width()/2+10,pItem->y()-20);
//                my_bullet.back()->setPos(pItem->x()+pItem->getQpixmap().width()/2-18,pItem->y()-20); //���ó�ʼ��λ��

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

//�ҷ��ӵ��ƶ�
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
        //���ù����ʽ
        setCursor(Qt::BlankCursor);
        this->m_bIsMoving=true;
        // const int MaxDistance=100*100;
        //����������ͷɻ�����ľ���
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



