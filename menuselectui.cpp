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
    this->setWindowTitle("�ɻ���ս");
    this->setWindowIcon(QIcon("image/icon72x72.png"));//���ó���logo
    this->setAutoFillBackground(true);
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

    //���ز˵�����
    menuUi();
    //������Ϸ��������
    this->instruct = new helpUi(this);
    this->instruct->hide();
    //������Ϸ���ý���
    this->gameSet = new setUi(this);
    this->gameSet->hide();
    //�������а����
    this->rank = new gameRank(this);
    this->rank->hide();

    //ҳ�����вۺ�������
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

    //����title
    this->title = new QLabel(this);
    this->title->setPixmap(QPixmap("image/name.png"));
    this->title->move(25,60);
    //��ʼ��Ϸ��ť
    this->startBtn = new QPushButton(btnSelect);
    this->startBtn->setText("��ʼ��Ϸ");
    this->startBtn->setFont(font);
    this->startBtn->setFixedSize(260,60);

    //���ð�ť
    this->setBtn = new QPushButton(btnSelect);
    this->setBtn->setText("����");
    this->setBtn->setFont(font);
    this->setBtn->setFixedSize(260,60);

    //���а�ť
    this->rankBtn = new QPushButton(btnSelect);
    this->rankBtn->setText("���а�");
    this->rankBtn->setFont(font);
    this->rankBtn->setFixedSize(260,60);

    //��Ϸ������ť
    this->helpBtn = new QPushButton(btnSelect);
    this->helpBtn->setText("����");
    this->helpBtn->setFont(font);
    this->helpBtn->setFixedSize(260,60);

    //�˳���ť
    this->exitBtn = new QPushButton(btnSelect);
    this->exitBtn->setText("�˳���Ϸ");
    this->exitBtn->setFont(font);
    this->exitBtn->setFixedSize(260,60);
    //��ֱ����
    btnSelect->move(100,250);
    QVBoxLayout *btn_select = new QVBoxLayout(btnSelect);
    btn_select->addWidget(startBtn);
    btn_select->addWidget(setBtn);
    btn_select->addWidget(rankBtn);
    btn_select->addWidget(helpBtn);
    btn_select->addWidget(exitBtn);
    btn_select->setSpacing(20);
    btnSelect->setLayout(btn_select);

    //�ж���Ϸ�Ƿ����
    this->timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(gameOverSlot()));
    timer1->start(50);


}

//�ж���Ϸ����
void menuSelectUi::gameOverSlot()
{
    //��Ϸ������־λ
    if(gameOverFlag)
    {
        qDebug()<<"��Ϸ����";
        this->gameover = new gameOver(this);
        connect(gameover,SIGNAL(backToSignal()),this,SLOT(gameOverReturnSlot()));
        delete this->game;
        gameover->show();
        timer1->stop();
    }
}

void menuSelectUi::gameOverReturnSlot()
{
    qDebug()<<"����˷���";
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
        QMessageBox::question(this, "Tip","���ȵ�¼",QMessageBox::Ok);
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
//    //����              ����                OK��ť
//    QMessageBox message(QMessageBox::Question, "Tip","ȷ�Ϸ��أ�",QMessageBox::Yes | QMessageBox::No,this);
    if (QMessageBox::Yes ==  QMessageBox::question(this, "Tip","ȷ�Ϸ��أ�",QMessageBox::Yes | QMessageBox::No))
    {
        emit exitBtnSignal();
    }
    else
    {
        return;
    }
}



