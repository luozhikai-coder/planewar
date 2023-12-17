#include "forgetpwd.h"

forgetPwd::forgetPwd(QWidget *parent) :
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
//    this->setStyleSheet("QPushButton{border-radius:15px;border:2px solid grey}"
//                                      "QPushButton:pressed{border:5px solid grey}");

//    QFont font("Snap ITC",20,75);
//    this->qes_label = new QLabel(this);
//    this->question_label->setText("问题：");
//    this->question_label->setFont(font);
//    this->question_label->move(100,200);
}
