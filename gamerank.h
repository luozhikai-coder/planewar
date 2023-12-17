#ifndef GAMERANK_H
#define GAMERANK_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFont>
class gameRank : public QWidget
{
    Q_OBJECT
public:
    explicit gameRank(QWidget *parent = 0);
    
signals:
    void backToSignal();
public slots:
    void backToSlot();

private:
    QLabel *title;
    QLabel *nameLab;
    QLabel *scoreLab;
    QPushButton *backToMenuBtn;
};

#endif // GAMERANK_H
