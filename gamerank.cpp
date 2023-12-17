#include "gamerank.h"
#include <QFont>
#include <QIcon>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlTableModel>
#include <QTableView>
#include <QHeaderView>
#include <QTextCodec>

gameRank::gameRank(QWidget *parent) :
    QWidget(parent)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
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
    //���а�logo
    this->title = new QLabel(this);
    this->title->setText("�ɻ���ս���а�");
    this->title->setFont(QFont("Jokerman", 28, 75));
    this->title->move(100,80);
    //����
    //�û���
    this->nameLab = new QLabel(this);
    this->nameLab->setText("�û���");
    this->nameLab->move(110,150);
    this->nameLab->setFont(QFont("Jokerman", 14, 50));

    //�÷ֱ�ǩ
    this->scoreLab = new QLabel(this);
    this->scoreLab->setText("����");
    this->scoreLab->move(280,150);
    this->scoreLab->setFont(QFont("Jokerman", 14, 50));

    //���ع���ѡ�����
    QFont font1("Snap ITC",20,75);
    this->backToMenuBtn = new QPushButton(this);
    this->backToMenuBtn->setText("����");
    this->backToMenuBtn->setFont(font1);
    this->backToMenuBtn->setFixedSize(260,60);
    this->backToMenuBtn->move(100,700);
    this->backToMenuBtn->setStyleSheet("QPushButton{border-radius:15px;border:2px solid grey}"
                                       "QPushButton:pressed{border:5px solid grey}");

    //�����ݿ������ݶ�ȡ����
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QTableView *tableView = new QTableView(this);
    model->setQuery("select * from score order by score DESC");
    tableView->setModel(model);
    ////���óɲ��ɱ༭
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->move(40,200);
    //����tableview��С
    tableView->setMinimumSize(400,400);
    //ȥ��������
    tableView->setShowGrid(false);
    //�����п�
    tableView->setColumnWidth(0,240);
    tableView->setColumnWidth(1,240);
    //�����и�
    tableView->setRowHeight(0,40);
    tableView->setRowHeight(1,40);
    tableView->setRowHeight(2,40);
    tableView->setRowHeight(3,40);
    tableView->setRowHeight(4,40);
    tableView->setRowHeight(5,40);
    tableView->setRowHeight(6,40);
    tableView->setRowHeight(7,40);
    tableView->setRowHeight(8,40);
    tableView->setRowHeight(9,40);

    //ȥ����߿�
    tableView->setFrameShape(QFrame::NoFrame);
    tableView->setAlternatingRowColors(true);  // alternative colors
    //
    tableView->horizontalHeader()->resizeSection(0,150);
    tableView->verticalHeader()->setStyleSheet("QHeaderView::section {  background-color:skyblue;color: black;padding-left: 4px;border: 1px solid #6c6c6c}");   //�������еı߿����������ɫģʽ��
    //��ͷ��������
    tableView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    tableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);

    tableView->horizontalHeader()->hide();
    //��������
//    tableView->setSortingEnabled(true);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);   //����ѡ���ģʽΪ��ѡ��

//    tableView->setSelectionBehavior(QAbstractItemView::NoSelection);    //����ѡ����Ϊʱÿ��ѡ��һ��
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

//    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:lightblue;color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");    //���ñ�ͷ���壬��ɫ��ģʽ
//    tableView->setStyleSheet("QTableView { color: white;gridline-color: black;background-color: grey; alternate-background-color: rgb(64, 64, 64);selection-color: white;selection-background-color: rgb(77, 77, 77);border: 2px groove gray;border-radius: 0px;padding: 2px 4px;}");


    connect(backToMenuBtn,SIGNAL(clicked()),this,SLOT(backToSlot()));

}

void gameRank::backToSlot()
{
    emit backToSignal();
}
