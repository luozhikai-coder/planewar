#ifndef HELPUI_H
#define HELPUI_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QIcon>
#include <QFont>
#include <QPushButton>
class helpUi : public QWidget
{
    Q_OBJECT
public:
    explicit helpUi(QWidget *parent = 0);
    
signals:
    void backToMenuSingal();
public slots:
    void backToMenuSlot();
private:
    QLabel *title;
    QLabel *instruction;
    QPushButton *backBtn;
};

#endif // HELPUI_H
