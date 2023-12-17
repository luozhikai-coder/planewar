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
    this->setWindowTitle("�ɻ���ս");
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
    this->setStyleSheet("QLineEdit{border-radius:10px;border:2px solid grey}");
    //���沼��
    loginUi();
    tcpClient = new QTcpSocket();
    ifMusicOn = 1;

    bgm->setLoops(-1);
    bgm->play();
//    timer = new QTimer(this);
//    connect(timer,SIGNAL(timeout()),this,SLOT(musicPlay()));
//    timer->start(1000);
    //���水ť�ۺ���
    connect(btn_close,SIGNAL(clicked()),this,SLOT(btnClose()));
    connect(ConnectToServer,SIGNAL(clicked()),this,SLOT(ActConnect()));
    connect(login_button,SIGNAL(clicked()),this,SLOT(loginCheck()));
    connect(regiset_button,SIGNAL(clicked()),this,SLOT(regists()));
    connect(reg,SIGNAL(backSignal()),this,SLOT(recBack()));
    connect(visitLogin,SIGNAL(clicked()),this,SLOT(visitLoginSlot()));
    connect(menu,SIGNAL(exitBtnSignal()),this,SLOT(menuBack()));
    //socketͨ������
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
    //����title
    this->title = new QLabel(this);
    this->title->setPixmap(QPixmap("image/name.png"));
    this->title->move(25,60);
    //�رմ��ڰ�ť
    this->btn_close = new QPushButton(this);
    this->btn_close->setFixedSize(40,40);
    this->btn_close->move(this->width()-40,0);
    this->btn_close->setStyleSheet("QPushButton:hover{background-image:url(image/btn_close.png)}"
                                    "QPushButton{border:NONE;}");
    //��������
    QRegExp regExp("[1-9][0-9]+$");//������һ��ģʽ
    QRegExpValidator *pattern= new QRegExpValidator(regExp, this);//������һ�����ʽ

    //��������򣬱�ǩ���
    QFont font ("Jokerman", 12, 75);
    this->name_label = new QLabel(inputContent);
    this->name_label->setParent(inputContent);
    this->name_label->setText("�û�����");
    this->name_label->setFont(font);
    //�����ǩ
    this->pwd_label = new QLabel(inputContent);
    this->pwd_label->setParent(inputContent);
    this->pwd_label->setText("��  �룺");
    this->pwd_label->setFont(font);
    //�û��������
    this->name_edit = new QLineEdit(inputContent);
    this->name_edit->setParent(inputContent);
    this->name_edit->setPlaceholderText("�û���/�ǳ�");
    this->name_edit->setFixedSize(250,40);
    this->name_edit->setMaxLength(12);
    this->name_edit->setFont(font);
    //���������
    this->pwd_edit = new QLineEdit(inputContent);
    this->pwd_edit->setParent(inputContent);
    this->pwd_edit->setPlaceholderText("����");
    this->pwd_edit->setEchoMode(QLineEdit::Password);
    this->pwd_edit->setFixedSize(250,40);
    this->pwd_edit->setMaxLength(8);
    this->pwd_edit->setValidator(pattern);
    this->pwd_edit->setFont(font);

    //��¼����������
    inputContent->move(60,this->height()/3);
    QFormLayout *qform = new QFormLayout(inputContent);
    qform->addRow(name_label,name_edit);
    qform->addRow(pwd_label,pwd_edit);
    qform->setSpacing(10);
    inputContent->setLayout(qform);

    //��¼��ť
    this->login_button = new QPushButton(this);
    this->login_button->setParent(this);
    this->login_button->move(90,500);
    this->login_button->setText("��  ¼");
    this->login_button->setFont(font);
    this->login_button->setFixedSize(130,40);
    this->login_button->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");
    //ע�ᰴť
    this->regiset_button = new QPushButton(this);
    this->regiset_button->setParent(this);
    this->regiset_button->move(260,500);
    this->regiset_button->setText("ע  ��");
    this->regiset_button->setFont(font);
    this->regiset_button->setFixedSize(130,40);
    this->regiset_button->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");

    //��ס���롢�Զ���¼
    QCheckBox *pRememberCheckBox = new QCheckBox(this);
    QCheckBox *pAutoLoginCheckBox = new QCheckBox(this);
    pRememberCheckBox->setText("��ס����");
    pRememberCheckBox->move(150,420);
    pAutoLoginCheckBox->setText("�Զ���¼");
    pAutoLoginCheckBox->move(270,420);

    //IP��PORT����
    this->IP = new QLineEdit(netContent);
    this->IP->setFixedSize(150,30);
    this->IP->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    this->IP->setPlaceholderText("IP��ַ");

    this->PORT = new QLineEdit(netContent);
    this->PORT->setFixedSize(150,30);
    this->PORT->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    this->PORT->setPlaceholderText("�˿ں�");

    netContent->move(0,this->height()-100);
    QFormLayout *netForm = new QFormLayout(netContent);
    netForm->addRow("IP",IP);
    netForm->addRow("PORT",PORT);
    netContent->setLayout(netForm);
    this->reg = new regist(this);
    reg->hide();
    menu = new menuSelectUi(this);
    menu->hide();
    //���ӷ�������ť
    this->ConnectToServer = new QPushButton(this);
    this->ConnectToServer->setText("�� ��");
    this->ConnectToServer->setFont(font);
    this->ConnectToServer->setFixedSize(100,30);
    this->ConnectToServer->move(200,this->height()-60);
    this->ConnectToServer->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");

    //����������ʾ
    this->tips = new QLabel(this);
    this->tips->move(10,this->height()-30);
    this->tips->setFixedSize(this->width(),40);
    this->tips->setFont(QFont("Timers" , 8 ,  QFont::Light));

    //�ο͵�¼��ť
    this->visitLogin = new QPushButton(this);
    this->visitLogin->setParent(this);
    this->visitLogin->move(300,this->height()-60);
    this->visitLogin->setText("�ο͵�¼");
    this->visitLogin->setFont(font);
    this->visitLogin->setFixedSize(100,30);
    this->visitLogin->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");

    //��������
    this->forgetPwd_button = new QPushButton(this);
    this->forgetPwd_button->move(405,360);
    this->forgetPwd_button->setText("��������");
    this->forgetPwd_button->setStyleSheet("QPushButton{border:none;font-size:12px}"
                                          "QPushButton:hover{color:red;font-size:14px}");
}

//�������ӷ�����
void login::ActConnect()
{
    //��ȡ������ip�Ͷ˿�
    ip = this->IP->text();
    port = this->PORT->text().toInt();
    //�����ͷ�������������
    if(ip != NULL && port >0)
    {
        tcpClient->connectToHost(ip,port);
        this->FirstConnectFlag = 1;
    }
    else
    {
        this->tips->setText("����ʧ�ܣ��볢������...");
        this->IP->clear();
        this->PORT->clear();
        this->IP->setFocus();
        this->FirstConnectFlag = 0;
    }
}

//���ӷ������ɹ�
void login::connectToServer()
{
    if(this->FirstConnectFlag)
        this->tips->setText("�ɹ����ӷ�����");
    else
        this->tips->setText("�������Ϸ�����");
}


//��ȡ������������������
void login::ReadInformation()
{
    //��ȡ�׽����е�����
//    qDebug()<<"11212";
    QByteArray temp = tcpClient->readAll();
    memcpy(&recvbuf,temp.data()+sizeof(HEAD_T),sizeof(LOGIN_S));
    qDebug()<<recvbuf.flag;
    loginFlag = recvbuf.flag;
    //�жϷ���˷��͹���������
    if(loginFlag == 1)
    {
        QMessageBox::question(this,"Tip","��¼�ɹ�",QMessageBox::Ok);
        strcpy(username,this->name_edit->text().toStdString().data());
        this->forgetPwd_button->hide();
        this->ConnectToServer->hide();
        this->visitLogin->hide();
        menu->show();
    }
    else if(loginFlag == 0)
    {
        QMessageBox::question(this,"Tip","�û��������벻��ȷ",QMessageBox::Ok);
        // ������������
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
            //����              ����                OK��ť
            QMessageBox::question(this, "Tip","�������û�������",QMessageBox::Ok);
            name_edit->setFocus();
        }

    }
    else
    {
        //����              ����                OK��ť
      QMessageBox::question(this, "Tip","��֤���ӵ�����",QMessageBox::Ok);
      bgm->stop();
      bgm->play();
      // ������������
      name_edit->clear();
      pwd_edit->clear();
      //��궨λ
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
        //����              ����                OK��ť
      QMessageBox::question(this, "Tip","��֤���ӵ�����",QMessageBox::Ok);
      // ������������
      name_edit->clear();
      pwd_edit->clear();
      //��궨λ
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
