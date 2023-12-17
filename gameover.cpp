#include "gameover.h"
#include "sqlquery.h"
#include <QFont>
#include <QTextCodec>
extern char username[20];
extern int gamescore;
extern int loginFlag;
gameOver::gameOver(QWidget *parent) :
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
    palette.setBrush(QPalette::Background,QBrush(QPixmap("image/gameover.png")));
    this->setPalette(palette);
    sqlQuery::Instance("myscore.db")->createTable("score");
    qDebug()<<"��¼״̬��"<<loginFlag;
    if(loginFlag)
    {
        if(sqlQuery::Instance("myscore.db")->select("score",username) != NULL)
        {
            sqlQuery::Instance("myscore.db")->updataTable("score",username,gamescore);
        }
        else
        {
            sqlQuery::Instance("myscore.db")->insertTable("score",username,gamescore);
        }
    }
//    this->currentLabel = new QLabel(this);
//    this->currentLabel->setText("���ֵ÷�");
//    this->currentLabel->setFont(QFont("Jokerman", 32, 75));
//    this->currentLabel->move(this->width()/2-90,500);

//    this->historyLabel = new QLabel(this);
//    this->historyLabel->setText("��ʷ���");
//    this->historyLabel->setFont(QFont("Jokerman", 32, 75));
//    this->historyLabel->move(this->width()/2-90,200);
    //�÷ֱ�ǩ
    QString score;
    score = QString("%1").arg(gamescore);
    qDebug()<<"�÷֣�"<<score;
    this->currentScore = new QLabel(this);
    this->currentScore->setText(score);
    this->currentScore->setFont(QFont("Jokerman", 28, 75));
    this->currentScore->move(this->width()/2-40,600);
    //��ʷ��¼��ǩ
    score = sqlQuery::Instance("myscore.db")->select("score",username);
    this->historyScore = new QLabel(this);
    this->historyScore->setText(score);
    this->historyScore->setFont(QFont("Jokerman", 28, 75));
    this->historyScore->move(this->width()/2-40,300);
    //���ذ�ť
    QFont font1("Snap ITC",20,75);
    this->backToMenuBtn = new QPushButton(this);
    this->backToMenuBtn->setText("����");
    this->backToMenuBtn->setFont(font1);
    this->backToMenuBtn->setFixedSize(260,60);
    this->backToMenuBtn->move(100,700);
    this->backToMenuBtn->setStyleSheet("QPushButton{border-radius:15px;border:2px solid grey}"
                                       "QPushButton:pressed{border:5px solid grey}");

    connect(backToMenuBtn,SIGNAL(clicked()),this,SLOT(backToSlot()));

}

void gameOver::backToSlot()
{
    emit backToSignal();
}
