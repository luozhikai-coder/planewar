#include "regist.h"
#include <QTextCodec>
extern QTcpSocket *tcpClient;
HEAD_T head;
LOGIN_M sendbuf;
LOGIN_S recvbuf;
extern QString ip;
extern qint16 port;
regist::regist(QWidget *parent) :
    QWidget(parent)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    this->setWindowTitle("飞机大战");
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
    this->setStyleSheet("QLineEdit{border-radius:10px;border:2px solid grey}");
    reLayout();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(readDataSlot()));

    connect(back_button,SIGNAL(clicked()),this,SLOT(backToLogin()));
    connect(reg_button,SIGNAL(clicked()),this,SLOT(registBtnSlot()));

}

void regist::reLayout()
{
    QFormLayout *rLayout = new QFormLayout();
    QWidget *inputContent = new QWidget(this);
    QFont font ("Jokerman", 12, 75);
    //设置title
    this->retitle = new QLabel(this);
    this->retitle->setPixmap(QPixmap("image/name.png"));
    this->retitle->move(25,60);
//    //用户名
//    this->reg_name_label = new QLabel(inputContent);
//    this->reg_name_label->setParent(inputContent);
//    this->reg_name_label->setText("用户名:");
//    this->reg_name_label->setFont(font);

    //游戏昵称
    this->gamename_label = new QLabel(inputContent);
    this->gamename_label->setText("昵  称:");
    this->gamename_label->setFont(font);
    //密码标签
    this->reg_pwd_label = new QLabel(inputContent);
    this->reg_pwd_label->setText("密  码:");
    this->reg_pwd_label->setFont(font);
    //确认密码
    this->reg_rpwd_label = new QLabel(inputContent);
    this->reg_rpwd_label->setText("确认密码:");
    this->reg_rpwd_label->setFont(font);

    //密码提示
    this->tip_label = new QLabel(inputContent);
    this->tip_label->setText("密码提示:");
    this->tip_label->setFont(font);

    //答案
    this->answer_label = new QLabel(inputContent);
    this->answer_label->setText("答  案:");
    this->answer_label->setFont(font);

//    this->reg_name_edit = new QLineEdit(inputContent);
//    this->reg_name_edit->setPlaceholderText("用户名");
//    this->reg_name_edit->setFixedSize(250,40);
//    this->reg_name_edit->setMaxLength(12);
//    this->reg_name_edit->setFont(font);

    //游戏昵称
    this->gamename_edit = new QLineEdit(inputContent);
    this->gamename_edit->setPlaceholderText("游戏昵称");
    this->gamename_edit->setFixedSize(250,40);
    this->gamename_edit->setFont(font);
    //控制输入
    QRegExp regExp("[1-9][0-9]+$");//创建了一个模式
    QRegExpValidator *pattern= new QRegExpValidator(regExp, this);//创建了一个表达式
    //密码输入框
    this->reg_pwd_edit = new QLineEdit(inputContent);
    this->reg_pwd_edit->setPlaceholderText("密码");
    this->reg_pwd_edit->setEchoMode(QLineEdit::Password);
    this->reg_pwd_edit->setFixedSize(250,40);
    this->reg_pwd_edit->setMaxLength(8);
    this->reg_pwd_edit->setValidator(pattern);
    this->reg_pwd_edit->setFont(font);
    //密码确认框
    this->reg_ppwd_edit = new QLineEdit(inputContent);
    this->reg_ppwd_edit->setPlaceholderText("确认密码");
    this->reg_ppwd_edit->setEchoMode(QLineEdit::Password);
    this->reg_ppwd_edit->setFixedSize(250,40);
    this->reg_ppwd_edit->setMaxLength(8);
    this->reg_ppwd_edit->setValidator(pattern);
    this->reg_ppwd_edit->setFont(font);
    //密保问题
    this->questionSelect = new QComboBox(inputContent);
    this->questionSelect->addItem("你最爱的人？");
    this->questionSelect->addItem("你的手机号码？");
    this->questionSelect->addItem("你最喜欢的明星？");
    questionSelect->setStyleSheet("QComboBox{"//基本样式

                                   "font:黑体;"
                                   "font-size:20px;"
                                   "color:rgb(255,255,255);"
                                   "background-color:transparent;"
                                   "width:209px;"
                                   "height:45px;"
                               "}"
                               "QComboBox::down-arrow{"//下拉三角样式

                                   "background-color:transparent;"
                                   "width:36px;"

                                   "height:22px;"
                                   "right:2px;"
                               "}"

                               "QComboBox QAbstractItemView {"//Box内条目
                                   "outline:0px;" //去掉虚线
                                "}"

                               "QComboBox::drop-down {"
                                   "subcontrol-origin: padding;"
                                   "subcontrol-position: top right;"
                                   "width: 36px;"
                                "}"
                               );

    //答案输入框
    this->answer_edit = new QLineEdit(inputContent);
    this->answer_edit->setPlaceholderText("请输入答案");
    this->answer_edit->setFixedSize(250,40);
    this->answer_edit->setFont(font);
    //布局
    rLayout->setParent(this);
//    rLayout->addRow(reg_name_label,reg_name_edit);
    rLayout->addRow(gamename_label,gamename_edit);
    rLayout->addRow(reg_pwd_label,reg_pwd_edit);
    rLayout->addRow(reg_rpwd_label,reg_ppwd_edit);
    rLayout->addRow(tip_label,questionSelect);
    rLayout->addRow(answer_label,answer_edit);
//    rLayout->setContentsMargins(150,200,150,80);
//    rLayout->setAlignment(Qt::AlignCenter);
    inputContent->move(60,this->height()/3);
    inputContent->setLayout(rLayout);

    //注册按钮
    this->reg_button = new QPushButton(this);
    this->reg_button->setText("注册");
    this->reg_button->move(90,600);
    this->reg_button->setFont(font);
    this->reg_button->setFixedSize(130,40);
    this->reg_button->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");
    //返回按钮
    this->back_button = new QPushButton(this);
    this->back_button->setText("返回");
    this->back_button->move(260,600);
    this->back_button->setFont(font);
    this->back_button->setFixedSize(130,40);
    this->back_button->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");
}

//返回登录主界面
void regist::backToLogin()
{
    //标题              内容                OK按钮
    QMessageBox message(QMessageBox::Question, "Tip","确认返回？",QMessageBox::Yes | QMessageBox::No,this);
    if (message.exec()==QMessageBox::Yes)
    {
        timer->stop();
        emit backSignal();
    }
    else
    {
        return;
    }
}


//注册按钮事件
void regist::registBtnSlot()
{
    char buff[1024];
    if(gamename_edit->text() == NULL || reg_pwd_label->text() == NULL || reg_ppwd_edit->text() == NULL || answer_edit->text() == NULL)
    {
        QMessageBox::question(this,"Tip","请填写完整",QMessageBox::Ok);
    }
    if(reg_pwd_edit->text() != reg_ppwd_edit->text())
    {
        QMessageBox::question(this,"Tip","两次密码不一致",QMessageBox::Ok);
        gamename_edit->clear();
        reg_pwd_edit->clear();
        reg_ppwd_edit->clear();
        answer_edit->clear();
        gamename_edit->setFocus();
    }
    qDebug()<<"检测成功";
    head.fun=2;
    memcpy(buff,&head,sizeof(HEAD_T));//检测头部
    strcpy(sendbuf.username,gamename_edit->text().toStdString().c_str());//用户名
    strcpy(sendbuf.passwd,reg_pwd_edit->text().toStdString().c_str());//密码
    strcpy(sendbuf.question,(char *)&questionSelect->currentText());//获取问题信息
    strcpy(sendbuf.answer,answer_edit->text().toStdString().c_str());//答案
    sendbuf.score = 0;
    memcpy(buff+sizeof(HEAD_T),&sendbuf,sizeof(LOGIN_M));
    //向服务器发送数据
    tcpClient->write(buff,sizeof(HEAD_T)+sizeof(LOGIN_M));
    timer->start(1000);
}

void regist::readDataSlot()
{
    qDebug()<<recvbuf.flag;

    if(recvbuf.flag == 2)
    {
        QMessageBox::warning(this,"Tip","用户名已存在",QMessageBox::Ok);
        timer->stop();
    }
     else if(recvbuf.flag == 3)
    {
         QMessageBox::warning(this,"Tip","注册成功",QMessageBox::Ok);
         timer->stop();
    }

}


