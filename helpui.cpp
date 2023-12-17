#include "helpui.h"

helpUi::helpUi(QWidget *parent) :
    QWidget(parent)
{
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
    //游戏规则
    QFont font ("Jokerman", 12, 75);
    //游戏操作指南标签
    this->title = new QLabel(this);
    this->title->setText("游戏操作指南");
    this->title->setFont(QFont("Jokerman", 28, 75));
    this->title->move(120,150);
    this->instruction = new QLabel(this);
    this->instruction->setText("通过↑、↓、←、→控制飞机的方向\n或者通过长按鼠标左键实现我方飞机的移动\n空格键发射子弹\n游戏中通过吃道具可以实现飞机的升级");
    this->instruction->setFont(font);
    this->instruction->move(100,300);
    //返回按钮
    QFont font1("Snap ITC",20,75);
    this->backBtn = new QPushButton(this);
    this->backBtn->setText("返回");
    this->backBtn->setFont(font1);
    this->backBtn->setFixedSize(260,60);
    this->backBtn->move(100,500);

    connect(backBtn,SIGNAL(clicked()),this,SLOT(backToMenuSlot()));
}


void helpUi::backToMenuSlot()
{
    emit backToMenuSingal();
}
