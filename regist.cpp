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
    //����title
    this->retitle = new QLabel(this);
    this->retitle->setPixmap(QPixmap("image/name.png"));
    this->retitle->move(25,60);
//    //�û���
//    this->reg_name_label = new QLabel(inputContent);
//    this->reg_name_label->setParent(inputContent);
//    this->reg_name_label->setText("�û���:");
//    this->reg_name_label->setFont(font);

    //��Ϸ�ǳ�
    this->gamename_label = new QLabel(inputContent);
    this->gamename_label->setText("��  ��:");
    this->gamename_label->setFont(font);
    //�����ǩ
    this->reg_pwd_label = new QLabel(inputContent);
    this->reg_pwd_label->setText("��  ��:");
    this->reg_pwd_label->setFont(font);
    //ȷ������
    this->reg_rpwd_label = new QLabel(inputContent);
    this->reg_rpwd_label->setText("ȷ������:");
    this->reg_rpwd_label->setFont(font);

    //������ʾ
    this->tip_label = new QLabel(inputContent);
    this->tip_label->setText("������ʾ:");
    this->tip_label->setFont(font);

    //��
    this->answer_label = new QLabel(inputContent);
    this->answer_label->setText("��  ��:");
    this->answer_label->setFont(font);

//    this->reg_name_edit = new QLineEdit(inputContent);
//    this->reg_name_edit->setPlaceholderText("�û���");
//    this->reg_name_edit->setFixedSize(250,40);
//    this->reg_name_edit->setMaxLength(12);
//    this->reg_name_edit->setFont(font);

    //��Ϸ�ǳ�
    this->gamename_edit = new QLineEdit(inputContent);
    this->gamename_edit->setPlaceholderText("��Ϸ�ǳ�");
    this->gamename_edit->setFixedSize(250,40);
    this->gamename_edit->setFont(font);
    //��������
    QRegExp regExp("[1-9][0-9]+$");//������һ��ģʽ
    QRegExpValidator *pattern= new QRegExpValidator(regExp, this);//������һ�����ʽ
    //���������
    this->reg_pwd_edit = new QLineEdit(inputContent);
    this->reg_pwd_edit->setPlaceholderText("����");
    this->reg_pwd_edit->setEchoMode(QLineEdit::Password);
    this->reg_pwd_edit->setFixedSize(250,40);
    this->reg_pwd_edit->setMaxLength(8);
    this->reg_pwd_edit->setValidator(pattern);
    this->reg_pwd_edit->setFont(font);
    //����ȷ�Ͽ�
    this->reg_ppwd_edit = new QLineEdit(inputContent);
    this->reg_ppwd_edit->setPlaceholderText("ȷ������");
    this->reg_ppwd_edit->setEchoMode(QLineEdit::Password);
    this->reg_ppwd_edit->setFixedSize(250,40);
    this->reg_ppwd_edit->setMaxLength(8);
    this->reg_ppwd_edit->setValidator(pattern);
    this->reg_ppwd_edit->setFont(font);
    //�ܱ�����
    this->questionSelect = new QComboBox(inputContent);
    this->questionSelect->addItem("������ˣ�");
    this->questionSelect->addItem("����ֻ����룿");
    this->questionSelect->addItem("����ϲ�������ǣ�");
    questionSelect->setStyleSheet("QComboBox{"//������ʽ

                                   "font:����;"
                                   "font-size:20px;"
                                   "color:rgb(255,255,255);"
                                   "background-color:transparent;"
                                   "width:209px;"
                                   "height:45px;"
                               "}"
                               "QComboBox::down-arrow{"//����������ʽ

                                   "background-color:transparent;"
                                   "width:36px;"

                                   "height:22px;"
                                   "right:2px;"
                               "}"

                               "QComboBox QAbstractItemView {"//Box����Ŀ
                                   "outline:0px;" //ȥ������
                                "}"

                               "QComboBox::drop-down {"
                                   "subcontrol-origin: padding;"
                                   "subcontrol-position: top right;"
                                   "width: 36px;"
                                "}"
                               );

    //�������
    this->answer_edit = new QLineEdit(inputContent);
    this->answer_edit->setPlaceholderText("�������");
    this->answer_edit->setFixedSize(250,40);
    this->answer_edit->setFont(font);
    //����
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

    //ע�ᰴť
    this->reg_button = new QPushButton(this);
    this->reg_button->setText("ע��");
    this->reg_button->move(90,600);
    this->reg_button->setFont(font);
    this->reg_button->setFixedSize(130,40);
    this->reg_button->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");
    //���ذ�ť
    this->back_button = new QPushButton(this);
    this->back_button->setText("����");
    this->back_button->move(260,600);
    this->back_button->setFont(font);
    this->back_button->setFixedSize(130,40);
    this->back_button->setStyleSheet("QPushButton{border-radius:10px;border:2px solid grey}"
                                      "QPushButton:pressed{border:5px solid grey}");
}

//���ص�¼������
void regist::backToLogin()
{
    //����              ����                OK��ť
    QMessageBox message(QMessageBox::Question, "Tip","ȷ�Ϸ��أ�",QMessageBox::Yes | QMessageBox::No,this);
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


//ע�ᰴť�¼�
void regist::registBtnSlot()
{
    char buff[1024];
    if(gamename_edit->text() == NULL || reg_pwd_label->text() == NULL || reg_ppwd_edit->text() == NULL || answer_edit->text() == NULL)
    {
        QMessageBox::question(this,"Tip","����д����",QMessageBox::Ok);
    }
    if(reg_pwd_edit->text() != reg_ppwd_edit->text())
    {
        QMessageBox::question(this,"Tip","�������벻һ��",QMessageBox::Ok);
        gamename_edit->clear();
        reg_pwd_edit->clear();
        reg_ppwd_edit->clear();
        answer_edit->clear();
        gamename_edit->setFocus();
    }
    qDebug()<<"���ɹ�";
    head.fun=2;
    memcpy(buff,&head,sizeof(HEAD_T));//���ͷ��
    strcpy(sendbuf.username,gamename_edit->text().toStdString().c_str());//�û���
    strcpy(sendbuf.passwd,reg_pwd_edit->text().toStdString().c_str());//����
    strcpy(sendbuf.question,(char *)&questionSelect->currentText());//��ȡ������Ϣ
    strcpy(sendbuf.answer,answer_edit->text().toStdString().c_str());//��
    sendbuf.score = 0;
    memcpy(buff+sizeof(HEAD_T),&sendbuf,sizeof(LOGIN_M));
    //���������������
    tcpClient->write(buff,sizeof(HEAD_T)+sizeof(LOGIN_M));
    timer->start(1000);
}

void regist::readDataSlot()
{
    qDebug()<<recvbuf.flag;

    if(recvbuf.flag == 2)
    {
        QMessageBox::warning(this,"Tip","�û����Ѵ���",QMessageBox::Ok);
        timer->stop();
    }
     else if(recvbuf.flag == 3)
    {
         QMessageBox::warning(this,"Tip","ע��ɹ�",QMessageBox::Ok);
         timer->stop();
    }

}


