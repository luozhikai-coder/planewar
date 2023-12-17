#include "game_widget.h"
#include <windows.h>
#include <QMovie>
extern int ifguideOn;
extern bool gameOverFlag;
game_widget::game_widget(QWidget *parent) :
    QWidget(parent)
{

    this->setWindowTitle("飞机大战");
    this->setAutoFillBackground(true);
    this->setWindowIcon(QIcon("image/icon72x72.png"));//设置程序logo
//    this->setWindowFlags(Qt::FramelessWindowHint);       //去标题栏
    this->setAttribute(Qt::WA_TranslucentBackground,true);//背景透明
    this->setFixedSize(480,852);                         //设置窗口大小 不可改变
    //加载游戏背景音乐
//    this->gamebgm = new QSound("music/menubg.wav");
//    this->gamebgm->play();
//    this->gamebgm->setLoops(-1);


    qDebug()<<ifguideOn;
    //界面滚动动画机
    this->setStyleSheet("QWidget{background-color:transparent}");
    QLabel * Label3 = new QLabel(this);
    Label3->setStyleSheet("QLabel{border-image:url(image/background.png);}");
    QLabel * Label4 = new QLabel(this);
    Label4->setStyleSheet("QLabel{border-image:url(image/background.png);}");
    QLabel * Label5 = new QLabel(this);
    Label5->setStyleSheet("QLabel{border-image:url(image/background.png);}");

    QPropertyAnimation * animation1 = new QPropertyAnimation(Label4, "geometry",this);//动画
    animation1->setDuration(7000);
    animation1->setKeyValueAt(0,QRect(0,-852,480,852));
    animation1->setKeyValueAt(1,QRect(0,852,480,852));

    QPropertyAnimation * animation2 = new QPropertyAnimation(Label3, "geometry",this);//动画
    animation2->setDuration(7000);
    animation2->setKeyValueAt(0,QRect(0,-1704,480,852));
    animation2->setKeyValueAt(1,QRect(0,0,480,852));

    QPropertyAnimation * animation3 = new QPropertyAnimation(Label5, "geometry",this);//动画
    animation3->setDuration(3500);
    animation3->setKeyValueAt(0,QRect(0,0,480,852));
    animation3->setKeyValueAt(1,QRect(0,852,480,852));

    QParallelAnimationGroup * group_1 = new QParallelAnimationGroup;
    group_1->addAnimation(animation1);
    group_1->addAnimation(animation2);
    group_1->addAnimation(animation3);
    group_1->start();
    group_1->setLoopCount(-1);
    //新手引导是否关闭
    if(ifguideOn == 1)
    {
        this->timer1 = new QTimer(this);
        connect(timer1,SIGNAL(timeout()),this,SLOT(timeCount()));
        timer1->start(1000);
        this->timeTitle = new QLabel(this);
        this->timeTitle->setText("倒计时!");
        this->timeTitle->setFont(QFont("Jokerman", 28, 75));
        this->timeTitle->move(180,150);

        this->title = new QLabel(this);
        this->title->move(this->width()/2-20,this->height()/2-100);
        this->title->setText("3");
        this->title->setFont(QFont("Jokerman", 32, 75));
//        this->title->setPixmap(QPixmap("image/num3.png"));
    }
    //新手引导标志位
    this->flag = 0;



}



//倒计时的实现
void game_widget::timeCount()
{
    static int time;
    qDebug()<<"time:::::"<<time;

    switch(++time)
    {
        case 1:
//        this->title->setPixmap(QPixmap("image/num2.png"));
        this->title->setText("2");
        break;
        case 2:
//        this->title->setPixmap(QPixmap("image/num1.png"));
        this->title->setText("1");
        break;
//        case 3:
//        this->title->setPixmap(QPixmap("image/num1.png"));
//        break;
//        case 4:
//        QMovie *movie = new QMovie("image/loading.png");
//        this->title->setMovie(movie);
//        movie->start();
//        qDebug()<<"movie start";
//        break;
    }
    if(time == 3)
    {
        timer1->stop();
        time = 0;
//        startFlag = 1;
        delete this->title;
        delete this->timeTitle;
        this->game_view = new gameView(this);
        this->game_view->show();
    }
}

//新手指引
void game_widget::gameGuide()
{
    //下一步
    qDebug()<<"新手引导"<<ifguideOn;
    if(ifguideOn == 0)
    {
        QFont font("Snap ITC",20,75);
        this->nextBtn = new QPushButton(this);
        this->nextBtn->setParent(this);
        this->nextBtn->move(300,500);
        this->nextBtn->setText("下一步");
        this->nextBtn->setFont(font);
        this->nextBtn->setFixedSize(130,40);
        this->nextBtn->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                          "QPushButton:pressed{border:5px solid grey}");

        //游戏规则
        QFont font1("Jokerman", 12, 75);

        this->title = new QLabel(this);
        this->title->setText("新手引导");
        this->title->setFont(QFont("Jokerman", 28, 75));
        this->title->move(160,150);
    //    this->instruction = new QLabel(this);
    //    this->instruction->setText("通过↑、↓、←、→控制飞机的方向\n或者通过长按鼠标左键实现我方飞机的移动\n空格键发射子弹\n游戏中通过吃道具可以实现飞机的升级");
    //    this->instruction->setFont(font1);
    //    this->instruction->move(100,300);

        this->guideText = new QLabel(this);
        this->guideText->setText("通过↑、↓、←、→控制飞机的方向\n或者通过长按鼠标左键实现我方\n飞机的移动");
        this->guideText->setFont(QFont("Jokerman", 18, 75));
    //    this->guideText->setStyleSheet("QLabel{border:2px;border-radius:5px}");
        this->guideText->move(60,300);

        connect(nextBtn,SIGNAL(clicked()),this,SLOT(nextBtnSlot()));
    }

}


void game_widget::nextBtnSlot()
{
    switch(flag)
    {
    case 0:
        this->guideText->setText("空格键发射子弹");
        flag++;
        break;
    case 1:
        flag++;
        this->guideText->setText("游戏中通过吃道具可以实现飞机\n子弹的升级");
        break;
    case 2:
        this->guideText->setText("开始游戏吧！");
        this->nextBtn->setText("完成");
        flag++;
        break;
    case 3:
        this->game_view = new gameView(this);
        this->game_view->show();
        delete this->title;
        delete this->guideText;
        delete this->nextBtn;
        break;
    }


}
