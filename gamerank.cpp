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
    //排行榜logo
    this->title = new QLabel(this);
    this->title->setText("飞机大战排行榜");
    this->title->setFont(QFont("Jokerman", 28, 75));
    this->title->move(100,80);
    //排名
    //用户名
    this->nameLab = new QLabel(this);
    this->nameLab->setText("用户名");
    this->nameLab->move(110,150);
    this->nameLab->setFont(QFont("Jokerman", 14, 50));

    //得分标签
    this->scoreLab = new QLabel(this);
    this->scoreLab->setText("分数");
    this->scoreLab->move(280,150);
    this->scoreLab->setFont(QFont("Jokerman", 14, 50));

    //返回功能选择界面
    QFont font1("Snap ITC",20,75);
    this->backToMenuBtn = new QPushButton(this);
    this->backToMenuBtn->setText("返回");
    this->backToMenuBtn->setFont(font1);
    this->backToMenuBtn->setFixedSize(260,60);
    this->backToMenuBtn->move(100,700);
    this->backToMenuBtn->setStyleSheet("QPushButton{border-radius:15px;border:2px solid grey}"
                                       "QPushButton:pressed{border:5px solid grey}");

    //将数据库中数据读取出来
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QTableView *tableView = new QTableView(this);
    model->setQuery("select * from score order by score DESC");
    tableView->setModel(model);
    ////设置成不可编辑
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->move(40,200);
    //设置tableview大小
    tableView->setMinimumSize(400,400);
    //去除网格线
    tableView->setShowGrid(false);
    //设置列宽
    tableView->setColumnWidth(0,240);
    tableView->setColumnWidth(1,240);
    //设置行高
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

    //去除外边框
    tableView->setFrameShape(QFrame::NoFrame);
    tableView->setAlternatingRowColors(true);  // alternative colors
    //
    tableView->horizontalHeader()->resizeSection(0,150);
    tableView->verticalHeader()->setStyleSheet("QHeaderView::section {  background-color:skyblue;color: black;padding-left: 4px;border: 1px solid #6c6c6c}");   //设置纵列的边框项的字体颜色模式等
    //表头不可伸缩
    tableView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    tableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);

    tableView->horizontalHeader()->hide();
    //升序排列
//    tableView->setSortingEnabled(true);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);   //设置选择的模式为单选择

//    tableView->setSelectionBehavior(QAbstractItemView::NoSelection);    //设置选择行为时每次选择一行
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

//    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:lightblue;color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");    //设置表头字体，颜色，模式
//    tableView->setStyleSheet("QTableView { color: white;gridline-color: black;background-color: grey; alternate-background-color: rgb(64, 64, 64);selection-color: white;selection-background-color: rgb(77, 77, 77);border: 2px groove gray;border-radius: 0px;padding: 2px 4px;}");


    connect(backToMenuBtn,SIGNAL(clicked()),this,SLOT(backToSlot()));

}

void gameRank::backToSlot()
{
    emit backToSignal();
}
