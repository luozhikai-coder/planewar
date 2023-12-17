#include "login.h"
#include "ui_login.h"
#include <QTextCodec>
extern HEAD_T head;
extern LOGIN_M sendbuf;
extern LOGIN_S recvbuf;
QTcpSocket *tcpClient;
int loginFlag;
int ifMusicOn;
int ifguideOn;
QString ip;
qint16 port;
QSound * bgm = new QSound("music/BackgroundMusic.wav");
char username[20];
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    ui->setupUi(this);  
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
    //界面布局
    loginUi();
    tcpClient = new QTcpSocket();
    ifMusicOn = 1;

    bgm->setLoops(-1);
    bgm->play();
//    timer = new QTimer(this);
//    connect(timer,SIGNAL(timeout()),this,SLOT(musicPlay()));
//    timer->start(1000);
    //界面按钮槽函数
    connect(btn_close,SIGNAL(clicked()),this,SLOT(btnClose()));
    connect(ConnectToServer,SIGNAL(clicked()),this,SLOT(ActConnect()));
    connect(login_button,SIGNAL(clicked()),this,SLOT(loginCheck()));
    connect(regiset_button,SIGNAL(clicked()),this,SLOT(regists()));
    connect(reg,SIGNAL(backSignal()),this,SLOT(recBack()));
    connect(visitLogin,SIGNAL(clicked()),this,SLOT(visitLoginSlot()));
    connect(menu,SIGNAL(exitBtnSignal()),this,SLOT(menuBack()));
    //socket通信连接
    connect(tcpClient, SIGNAL(connected()),this,SLOT(connectToServer()));
    connect(tcpClient, SIGNAL(readyRead()),this,SLOT(ReadInformation()));

}

login::~login()
{
    delete ui;

}

//void login::musicPlay()
//{
//    if(ifMusicOn)
//    {
//        bgm->play();
//    }
//    else
//        bgm->stop();
//}

void login::loginUi()
{
    QWidget *inputContent = new QWidget(this);
    QWidget *netContent = new QWidget(this);
    //设置title
    this->title = new QLabel(this);
    this->title->setPixmap(QPixmap("image/name.png"));
    this->title->move(25,60);
    //关闭窗口按钮
    this->btn_close = new QPushButton(this);
    this->btn_close->setFixedSize(40,40);
    this->btn_close->move(this->width()-40,0);
    this->btn_close->setStyleSheet("QPushButton:hover{background-image:url(image/btn_close.png)}"
                                    "QPushButton{border:NONE;}");
    //控制输入
    QRegExp regExp("[1-9][0-9]+$");//创建了一个模式
    QRegExpValidator *pattern= new QRegExpValidator(regExp, this);//创建了一个表达式

    //设置输入框，标签组件
    QFont font ("Jokerman", 12, 75);
    this->name_label = new QLabel(inputContent);
    this->name_label->setParent(inputContent);
    this->name_label->setText("用户名：");
    this->name_label->setFont(font);
    //密码标签
    this->pwd_label = new QLabel(inputContent);
    this->pwd_label->setParent(inputContent);
    this->pwd_label->setText("密  码：");
    this->pwd_label->setFont(font);
    //用户名输入框
    this->name_edit = new QLineEdit(inputContent);
    this->name_edit->setParent(inputContent);
    this->name_edit->setPlaceholderText("用户名/昵称");
    this->name_edit->setFixedSize(250,40);
    this->name_edit->setMaxLength(12);
    this->name_edit->setFont(font);
    //密码输入框
    this->pwd_edit = new QLineEdit(inputContent);
    this->pwd_edit->setParent(inputContent);
    this->pwd_edit->setPlaceholderText("密码");
    this->pwd_edit->setEchoMode(QLineEdit::Password);
    this->pwd_edit->setFixedSize(250,40);
    this->pwd_edit->setMaxLength(8);
    this->pwd_edit->setValidator(pattern);
    this->pwd_edit->setFont(font);

    //登录输入框表单布局
    inputContent->move(60,this->height()/3);
    QFormLayout *qform = new QFormLayout(inputContent);
    qform->addRow(name_label,name_edit);
    qform->addRow(pwd_label,pwd_edit);
    qform->setSpacing(10);
    inputContent->setLayout(qform);

    //登录按钮
    this->login_button = new QPushButton(this);
    this->login_button->setParent(this);
    this->login_button->move(90,500);
    this->login_button->setText("登  录");
    this->login_button->setFont(font);
    this->login_button->setFixedSize(130,40);
    this->login_button->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");
    //注册按钮
    this->regiset_button = new QPushButton(this);
    this->regiset_button->setParent(this);
    this->regiset_button->move(260,500);
    this->regiset_button->setText("注  册");
    this->regiset_button->setFont(font);
    this->regiset_button->setFixedSize(130,40);
    this->regiset_button->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");

    //记住密码、自动登录
    QCheckBox *pRememberCheckBox = new QCheckBox(this);
    QCheckBox *pAutoLoginCheckBox = new QCheckBox(this);
    pRememberCheckBox->setText("记住密码");
    pRememberCheckBox->move(150,420);
    pAutoLoginCheckBox->setText("自动登录");
    pAutoLoginCheckBox->move(270,420);

    //IP和PORT输入
    this->IP = new QLineEdit(netContent);
    this->IP->setFixedSize(150,30);
    this->IP->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    this->IP->setPlaceholderText("IP地址");

    this->PORT = new QLineEdit(netContent);
    this->PORT->setFixedSize(150,30);
    this->PORT->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    this->PORT->setPlaceholderText("端口号");

    netContent->move(0,this->height()-100);
    QFormLayout *netForm = new QFormLayout(netContent);
    netForm->addRow("IP",IP);
    netForm->addRow("PORT",PORT);
    netContent->setLayout(netForm);
    this->reg = new regist(this);
    reg->hide();
    menu = new menuSelectUi(this);
    menu->hide();
    //连接服务器按钮
    this->ConnectToServer = new QPushButton(this);
    this->ConnectToServer->setText("连 接");
    this->ConnectToServer->setFont(font);
    this->ConnectToServer->setFixedSize(100,30);
    this->ConnectToServer->move(200,this->height()-60);
    this->ConnectToServer->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");

    //网络连接提示
    this->tips = new QLabel(this);
    this->tips->move(10,this->height()-30);
    this->tips->setFixedSize(this->width(),40);
    this->tips->setFont(QFont("Timers" , 8 ,  QFont::Light));

    //游客登录按钮
    this->visitLogin = new QPushButton(this);
    this->visitLogin->setParent(this);
    this->visitLogin->move(300,this->height()-60);
    this->visitLogin->setText("游客登录");
    this->visitLogin->setFont(font);
    this->visitLogin->setFixedSize(100,30);
    this->visitLogin->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");

    //忘记密码
    this->forgetPwd_button = new QPushButton(this);
    this->forgetPwd_button->move(405,360);
    this->forgetPwd_button->setText("忘记密码");
    this->forgetPwd_button->setStyleSheet("QPushButton{border:none;font-size:12px}"
                                          "QPushButton:hover{color:red;font-size:14px}");
}

//主动连接服务器
void login::ActConnect()
{
    //获取服务器ip和端口
    ip = this->IP->text();
    port = this->PORT->text().toInt();
    //主动和服务器建立连接
    if(ip != NULL && port >0)
    {
        tcpClient->connectToHost(ip,port);
        this->FirstConnectFlag = 1;
    }
    else
    {
        this->tips->setText("连接失败，请尝试重连...");
        this->IP->clear();
        this->PORT->clear();
        this->IP->setFocus();
        this->FirstConnectFlag = 0;
    }
}

//连接服务器成功
void login::connectToServer()
{
    if(this->FirstConnectFlag)
        this->tips->setText("成功连接服务器");
    else
        this->tips->setText("已连接上服务器");
}


//读取服务器发过来的数据
void login::ReadInformation()
{
    //获取套接字中的内容
//    qDebug()<<"11212";
    QByteArray temp = tcpClient->readAll();
    memcpy(&recvbuf,temp.data()+sizeof(HEAD_T),sizeof(LOGIN_S));
    qDebug()<<recvbuf.flag;
    loginFlag = recvbuf.flag;
    //判断服务端发送过来的数据
    if(loginFlag == 1)
    {
        QMessageBox::question(this,"Tip","登录成功",QMessageBox::Ok);
        strcpy(username,this->name_edit->text().toStdString().data());
        this->forgetPwd_button->hide();
        this->ConnectToServer->hide();
        this->visitLogin->hide();
        menu->show();
    }
    else if(loginFlag == 0)
    {
        QMessageBox::question(this,"Tip","用户名或密码不正确",QMessageBox::Ok);
        // 清空输入框内容
        name_edit->clear();
        pwd_edit->clear();
        name_edit->setFocus();
    }
}


void login::loginCheck()
{
    if(this->FirstConnectFlag == 1)
    {
        if(this->name_edit->text() != NULL && pwd_edit->text() != NULL)
        {
            head.fun = 1;
            strcpy(sendbuf.username,this->name_edit->text().toStdString().data());
            strcpy(sendbuf.passwd,this->pwd_edit->text().toStdString().data());

            char data[1024];
            memcpy(data,&head,sizeof(HEAD_T));
            memcpy(data+sizeof(HEAD_T),&sendbuf,sizeof(LOGIN_M));
            qDebug()<<sendbuf.username<<" "<<sendbuf.passwd;
            tcpClient->write(data,sizeof(HEAD_T)+sizeof(LOGIN_M));
            memset(&sendbuf,0,sizeof(LOGIN_M));
        }
        else
        {
            //标题              内容                OK按钮
            QMessageBox::question(this, "Tip","请输入用户名密码",QMessageBox::Ok);
            name_edit->setFocus();
        }

    }
    else
    {
        //标题              内容                OK按钮
      QMessageBox::question(this, "Tip","保证连接到网络",QMessageBox::Ok);
      bgm->stop();
      bgm->play();
      // 清空输入框内容
      name_edit->clear();
      pwd_edit->clear();
      //光标定位
      IP->setFocus();
    }

}

void login::mouseMoveEvent ( QMouseEvent * event )
{
    QPoint y = event->globalPos();
    QPoint x = y - this->z;

    this->move(x);
}
void login::mousePressEvent ( QMouseEvent * event )
{
    QPoint y = event->globalPos();
    QPoint x = this->geometry().topLeft();

    this->z = y - x;
}
void login::mouseReleaseEvent ( QMouseEvent * event )
{

}

void login::btnClose()
{
    this->close();
}

void login::regists()
{
    if(this->FirstConnectFlag!=1)
    {
        //标题              内容                OK按钮
      QMessageBox::question(this, "Tip","保证连接到网络",QMessageBox::Ok);
      // 清空输入框内容
      name_edit->clear();
      pwd_edit->clear();
      //光标定位
      IP->setFocus();
    }
    else if(this->FirstConnectFlag == 1)
    {
        this->forgetPwd_button->hide();
        this->ConnectToServer->hide();
        this->visitLogin->hide();
        reg->show();
    }

}

void login::recBack()
{
    this->show();
    this->forgetPwd_button->show();
    this->ConnectToServer->show();
    this->visitLogin->show();
    name_edit->clear();
    pwd_edit->clear();
    IP->clear();
    this->PORT->clear();
    reg->hide();
}
void login::menuBack()
{
    menu->hide();
    this->forgetPwd_button->show();
    this->ConnectToServer->show();
    this->visitLogin->show();
    name_edit->clear();
    pwd_edit->clear();
    IP->clear();
    this->PORT->clear();
    this->show();
}

void login::visitLoginSlot()
{
   loginFlag = 0;
   menu->show();
   this->forgetPwd_button->hide();
   this->ConnectToServer->hide();
   this->visitLogin->hide();
}
