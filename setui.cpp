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
    this->setWindowTitle("�ɻ���ս");
    //
    this->setAutoFillBackground(true);
    this->setWindowIcon(QIcon("image/icon72x72.png"));//���ó���logo
    //���ô��ڴ�С
    this->setFixedSize(480,852);
    //ȥ������
//    this->setWindowFlags(Qt::FramelessWindowHint);
    //���ر���ͼƬ
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
    this->title->setText("��Ϸ����");
    this->title->setFont(QFont("Jokerman", 28, 75));
    this->title->move(160,150);
    //�������ְ�ť
    this->musicOnOff = new QPushButton(this);
    this->musicOnOff->setText("��������: ��");
    this->musicOnOff->setFont(font);
    this->musicOnOff->setFixedSize(260,60);
    this->musicOnOff->move(100,260);

    //����������ť
    this->gameGuide = new QPushButton(this);
    this->gameGuide->setText("��������: ��");
    this->gameGuide->setFont(font);
    this->gameGuide->setFixedSize(260,60);
    this->gameGuide->move(100,360);

    //��Ϸ�Ѷ�
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
    this->gameLevel->setText("��ģʽ");
    this->gameLevel->setFont(QFont("Jokerman", 18, 75));
    this->gameLevel->move(175,460);

    this->backBtn = new QPushButton(this);
    this->backBtn->setText("����");
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
        qDebug()<<"��������: ��";
        this->musicOnOff->setText("��������: ��");
        bgm->stop();
       ifMusicOn=0;
    }
    else
    {
        qDebug()<<"��������: ��";
        this->musicOnOff->setText("��������: ��");
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
        this->gameLevel->setText("��ģʽ");
        break;
        case 2:
        this->gameLevel->setText("��ͨģʽ");
        break;
        case 3:
        this->gameLevel->setText("����ģʽ");
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
        this->gameLevel->setText("��ģʽ");
        break;
        case 2:
        this->gameLevel->setText("��ͨģʽ");
        break;
        case 3:
        this->gameLevel->setText("����ģʽ");
        break;
    }
}

void setUi::gameGuideOnOffSlot()
{
    if(ifguideOn == 0)
    {
        qDebug()<<"��������: ��";
        this->gameGuide->setText("��������: ��");
       ifguideOn=1;
    }
    else
    {
        qDebug()<<"��������: ��";
        this->gameGuide->setText("��������: ��");
        ifguideOn=0;
    }

}
void setUi::sbackToMenuSlot()
{
    emit sbackToMenuSingal();
}

