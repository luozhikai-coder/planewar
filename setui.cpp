#include "setui.h"
#include <QTextCodec>
extern int ifMusicOn;
extern int ifguideOn;
extern QSound *bgm;
int gameMode;
setUi::setUi(QWidget *parent) :
    QWidget(parent)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    this->setWindowTitle("飞机大战");
    //
    this->setAutoFillBackground(true);
    this->setWindowIcon(QIcon("image/icon72x72.png"));//设置程序logo
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
    gameMode = 1;
    setui();
}


void setUi::setui()
{
    QFont font("Snap ITC",20,75);
    this->title = new QLabel(this);
    this->title->setText("游戏设置");
    this->title->setFont(QFont("Jokerman", 28, 75));
    this->title->move(160,150);
    //背景音乐按钮
    this->musicOnOff = new QPushButton(this);
    this->musicOnOff->setText("背景音乐: 开");
    this->musicOnOff->setFont(font);
    this->musicOnOff->setFixedSize(260,60);
    this->musicOnOff->move(100,260);

    //新手引导按钮
    this->gameGuide = new QPushButton(this);
    this->gameGuide->setText("新手引导: 开");
    this->gameGuide->setFont(font);
    this->gameGuide->setFixedSize(260,60);
    this->gameGuide->move(100,360);

    //游戏难度
    this->leftBtn = new QPushButton(this);
    this->leftBtn->setText("<");
    this->leftBtn->setFont(QFont("Jokerman", 18, 75));
    this->leftBtn->setFixedSize(50,40);
    this->leftBtn->move(100,460);

    this->rightBtn = new QPushButton(this);
    this->rightBtn->setText(">");
    this->rightBtn->setFont(QFont("Jokerman", 18, 75));
    this->rightBtn->setFixedSize(50,40);
    this->rightBtn->move(310,460);

    this->gameLevel = new QLabel(this);
    this->gameLevel->setText("简单模式");
    this->gameLevel->setFont(QFont("Jokerman", 18, 75));
    this->gameLevel->move(175,460);

    this->backBtn = new QPushButton(this);
    this->backBtn->setText("返回");
    this->backBtn->setFont(font);
    this->backBtn->setFixedSize(260,60);
    this->backBtn->move(100,540);

    connect(backBtn,SIGNAL(clicked()),this,SLOT(sbackToMenuSlot()));

    connect(musicOnOff,SIGNAL(clicked()),this,SLOT(musicOnOffSlot()));
    connect(gameGuide,SIGNAL(clicked()),this,SLOT(gameGuideOnOffSlot()));
    connect(leftBtn,SIGNAL(clicked()),this,SLOT(leftBtnSlot()));
    connect(rightBtn,SIGNAL(clicked()),this,SLOT(rightBtnSlot()));
}

void setUi::musicOnOffSlot()
{
    if(ifMusicOn==1)
    {
        qDebug()<<"背景音乐: 关";
        this->musicOnOff->setText("背景音乐: 关");
        bgm->stop();
       ifMusicOn=0;
    }
    else
    {
        qDebug()<<"背景音乐: 开";
        this->musicOnOff->setText("背景音乐: 开");
        bgm->play();
        ifMusicOn=1;
    }
}
void setUi::leftBtnSlot()
{
    gameMode--;
    if(gameMode<1)
        gameMode = 3;
    switch(gameMode)
    {
        case 1:
        this->gameLevel->setText("简单模式");
        break;
        case 2:
        this->gameLevel->setText("普通模式");
        break;
        case 3:
        this->gameLevel->setText("困难模式");
        break;
    }
}
void setUi::rightBtnSlot()
{
    gameMode++;
    if(gameMode>3)
        gameMode = 1;
    switch(gameMode)
    {
        case 1:
        this->gameLevel->setText("简单模式");
        break;
        case 2:
        this->gameLevel->setText("普通模式");
        break;
        case 3:
        this->gameLevel->setText("困难模式");
        break;
    }
}

void setUi::gameGuideOnOffSlot()
{
    if(ifguideOn == 0)
    {
        qDebug()<<"新手引导: 关";
        this->gameGuide->setText("新手引导: 关");
       ifguideOn=1;
    }
    else
    {
        qDebug()<<"新手引导: 开";
        this->gameGuide->setText("新手引导: 开");
        ifguideOn=0;
    }

}
void setUi::sbackToMenuSlot()
{
    emit sbackToMenuSingal();
}

