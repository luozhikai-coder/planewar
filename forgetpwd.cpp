#include "forgetpwd.h"

forgetPwd::forgetPwd(QWidget *parent) :
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
//    this->setStyleSheet("QPushButton{border-radius:15px;border:2px solid grey}"
//                                      "QPushButton:pressed{border:5px solid grey}");

//    QFont font("Snap ITC",20,75);
//    this->qes_label = new QLabel(this);
//    this->question_label->setText("���⣺");
//    this->question_label->setFont(font);
//    this->question_label->move(100,200);
}
