#include "helpui.h"

helpUi::helpUi(QWidget *parent) :
    QWidget(parent)
{
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
    //��Ϸ����
    QFont font ("Jokerman", 12, 75);
    //��Ϸ����ָ�ϱ�ǩ
    this->title = new QLabel(this);
    this->title->setText("��Ϸ����ָ��");
    this->title->setFont(QFont("Jokerman", 28, 75));
    this->title->move(120,150);
    this->instruction = new QLabel(this);
    this->instruction->setText("ͨ�������������������Ʒɻ��ķ���\n����ͨ������������ʵ���ҷ��ɻ����ƶ�\n�ո�������ӵ�\n��Ϸ��ͨ���Ե��߿���ʵ�ַɻ�������");
    this->instruction->setFont(font);
    this->instruction->move(100,300);
    //���ذ�ť
    QFont font1("Snap ITC",20,75);
    this->backBtn = new QPushButton(this);
    this->backBtn->setText("����");
    this->backBtn->setFont(font1);
    this->backBtn->setFixedSize(260,60);
    this->backBtn->move(100,500);

    connect(backBtn,SIGNAL(clicked()),this,SLOT(backToMenuSlot()));
}


void helpUi::backToMenuSlot()
{
    emit backToMenuSingal();
}
