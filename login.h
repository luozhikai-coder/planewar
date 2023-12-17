#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QIcon>
#include <QPalette>
#include <QBrush>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QLineEdit>
#include <QFormLayout>
#include <QFont>
#include <QCheckBox>
#include <QTcpSocket>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "regist.h"
#include <menuselectui.h>
#include <QSound>
namespace Ui {
class login;
}



class login : public QWidget
{
    Q_OBJECT
    
public:
    explicit login(QWidget *parent = 0);
    ~login();
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void loginUi();
    QTimer *timer;
public slots:
    void btnClose();
    void ActConnect();
    void connectToServer();
    void ReadInformation();
    void loginCheck();
    void regists();
    void recBack();
    void menuBack();
    void visitLoginSlot();
//    void musicPlay();
private:
    Ui::login *ui;
    QPoint z;
    QLabel *title;
    QPushButton *btn_close;
    QLabel *name_label;
    QLabel *pwd_label;
    QLineEdit *name_edit;
    QLineEdit *pwd_edit;
    QLineEdit *IP;
    QLineEdit *PORT;
    QPushButton *ConnectToServer;
    QCheckBox *pRememberCheckBox;
    QCheckBox *pAutoLoginCheckBox;
    QPushButton *login_button;
    QPushButton *regiset_button;
    QPushButton *visitLogin;
    QPushButton *forgetPwd_button;
    QLabel *tips;


    int FirstConnectFlag;
    menuSelectUi *menu;
    regist *reg;
};

#endif // LOGIN_H
