#include "menuselectui.h"
#include <QTextCodec>
extern int loginFlag;
extern int ifMusicOn;
extern int ifguideOn;
extern bool gameOverFlag;
extern int gamescore;
extern int startFlag;
extern int bombFlag;
menuSelectUi::menuSelectUi(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle("飞机大战");
    this->setWindowIcon(QIcon("image/icon72x72.png"));//设置程序logo
    this->setAutoFillBackground(true);
    //设置窗口大小
    this->setFixedSize(480,852);
    //去标题栏
//    this->setWindowFlags(Qt::FramelessWindowHint);
    //加载背景图片
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap("image/background.png")));
    this->setPalette(palette);
    this->setStyleSheet("QPushButton{border-radius:15px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");

    //加载菜单界面
    menuUi();
    //加载游戏帮助界面
    this->instruct = new helpUi(this);
    this->instruct->hide();
    //加载游戏设置界面
    this->gameSet = new setUi(this);
    this->gameSet->hide();
    //加载排行榜界面
    this->rank = new gameRank(this);
    this->rank->hide();

    //页面所有槽函数连接
    connect(startBtn,SIGNAL(clicked()),this,SLOT(startBtnSlot()));
    connect(setBtn,SIGNAL(clicked()),this,SLOT(setBtnSlot()));
    connect(rankBtn,SIGNAL(clicked()),this,SLOT(rankBtnSlot()));
    connect(helpBtn,SIGNAL(clicked()),this,SLOT(helpBtnSlot()));
    connect(exitBtn,SIGNAL(clicked()),this,SLOT(exitBtnSlot()));
    connect(instruct,SIGNAL(backToMenuSingal()),this,SLOT(helpReturnSlot()));
    connect(gameSet,SIGNAL(sbackToMenuSingal()),this,SLOT(setReturnSlot()));
    connect(rank,SIGNAL(backToSignal()),this,SLOT(rankReturnSolt()));

}

//
void menuSelectUi::menuUi()
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    QFont font("Snap ITC",20,75);
    QWidget *btnSelect = new QWidget(this);

    //设置title
    this->title = new QLabel(this);
    this->title->setPixmap(QPixmap("image/name.png"));
    this->title->move(25,60);
    //开始游戏按钮
    this->startBtn = new QPushButton(btnSelect);
    this->startBtn->setText("开始游戏");
    this->startBtn->setFont(font);
    this->startBtn->setFixedSize(260,60);

    //设置按钮
    this->setBtn = new QPushButton(btnSelect);
    this->setBtn->setText("设置");
    this->setBtn->setFont(font);
    this->setBtn->setFixedSize(260,60);

    //排行榜按钮
    this->rankBtn = new QPushButton(btnSelect);
    this->rankBtn->setText("排行榜");
    this->rankBtn->setFont(font);
    this->rankBtn->setFixedSize(260,60);

    //游戏帮助按钮
    this->helpBtn = new QPushButton(btnSelect);
    this->helpBtn->setText("帮助");
    this->helpBtn->setFont(font);
    this->helpBtn->setFixedSize(260,60);

    //退出按钮
    this->exitBtn = new QPushButton(btnSelect);
    this->exitBtn->setText("退出游戏");
    this->exitBtn->setFont(font);
    this->exitBtn->setFixedSize(260,60);
    //垂直布局
    btnSelect->move(100,250);
    QVBoxLayout *btn_select = new QVBoxLayout(btnSelect);
    btn_select->addWidget(startBtn);
    btn_select->addWidget(setBtn);
    btn_select->addWidget(rankBtn);
    btn_select->addWidget(helpBtn);
    btn_select->addWidget(exitBtn);
    btn_select->setSpacing(20);
    btnSelect->setLayout(btn_select);

    //判断游戏是否结束
    this->timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(gameOverSlot()));
    timer1->start(50);


}

//判断游戏结束
void menuSelectUi::gameOverSlot()
{
    //游戏结束标志位
    if(gameOverFlag)
    {
        qDebug()<<"游戏结束";
        this->gameover = new gameOver(this);
        connect(gameover,SIGNAL(backToSignal()),this,SLOT(gameOverReturnSlot()));
        delete this->game;
        gameover->show();
        timer1->stop();
    }
}

void menuSelectUi::gameOverReturnSlot()
{
    qDebug()<<"点击了返回";
    gamescore = 0;
    bombFlag = 0;
    delete this->gameover;
    this->show();
}
void menuSelectUi::startBtnSlot()
{
    this->game = new game_widget(this);
    if(ifguideOn == 0)
    {
       game->gameGuide();

    }
    gameOverFlag = false;
    timer1->start();
    game->show();

}
void menuSelectUi::setBtnSlot()
{
    this->gameSet->show();
}
void menuSelectUi::rankBtnSlot()
{
    if(loginFlag)
    {
       this->rank->show();
    }
    else
    {
        QMessageBox::question(this, "Tip","请先登录",QMessageBox::Ok);
    }
}
void menuSelectUi::rankReturnSolt()
{
    this->rank->hide();
    this->show();
}
void menuSelectUi::helpBtnSlot()
{

    instruct->show();
}

void menuSelectUi::helpReturnSlot()
{
    this->instruct->hide();
    this->show();
}

void menuSelectUi::setReturnSlot()
{
    this->gameSet->hide();
    this->show();
}
void menuSelectUi::exitBtnSlot()
{
//    //标题              内容                OK按钮
//    QMessageBox message(QMessageBox::Question, "Tip","确认返回？",QMessageBox::Yes | QMessageBox::No,this);
    if (QMessageBox::Yes ==  QMessageBox::question(this, "Tip","确认返回？",QMessageBox::Yes | QMessageBox::No))
    {
        emit exitBtnSignal();
    }
    else
    {
        return;
    }
}



