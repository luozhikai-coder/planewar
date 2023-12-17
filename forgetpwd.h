#ifndef FORGETPWD_H
#define FORGETPWD_H

#include <QWidget>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QFont>
class forgetPwd : public QWidget
{
    Q_OBJECT
public:
    explicit forgetPwd(QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    QLabel *qes_label;
    QPushButton *revise_button;
    QPushButton *back_button;
};

#endif // FORGETPWD_H
