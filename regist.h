#ifndef REGIST_H
#define REGIST_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QFormLayout>
#include <QMessageBox>
#include <QFont>
#include <QRegExpValidator>
#include <QComboBox>
#include <QTcpSocket>
#include <QTimer>
//��ͷ
typedef struct pub_head
{
        int fun;//������ 0���� 1:��¼
}HEAD_T;
//�����
typedef struct login_t
{
        char username[25];
        char passwd[25];
        char question[255];
        char answer[255];
        int score;
}LOGIN_M;
//Ӧ���
typedef struct login_res
{
        int flag;   //1���ӳɹ�����¼�ɹ�   0 ʧ��
        char username[25];
        char time[30];
}LOGIN_S; //����������
class regist : public QWidget
{
    Q_OBJECT
public:
    explicit regist(QWidget *parent = 0);
    void reLayout();
    QTimer *timer;
signals:

    void backSignal();
public slots:
    void backToLogin();
    void registBtnSlot();
    void readDataSlot();
private:
    QLabel *retitle;
    QLabel *reg_name_label;
    QLabel *gamename_label;
    QLabel *reg_pwd_label;
    QLabel *reg_rpwd_label;
    QLabel *tip_label;
    QLabel *answer_label;
    QLineEdit *reg_name_edit;
    QLineEdit *gamename_edit;
    QLineEdit *reg_pwd_edit;
    QLineEdit *reg_ppwd_edit;
    QComboBox *questionSelect;
    QLineEdit *answer_edit;
    QPushButton *reg_button;
    QPushButton *back_button;
    
    QWidget * Parent;
};

#endif // REGIST_H
