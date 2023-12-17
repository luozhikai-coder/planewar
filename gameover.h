#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
#include <QIcon>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QLabel>
#include <QPushButton>
class gameOver : public QWidget
{
    Q_OBJECT
public:
    explicit gameOver(QWidget *parent = 0);
    
signals:
    void backToSignal();
public slots:
    void backToSlot();
private:
    QLabel *currentLabel;
    QLabel *historyLabel;
    QLabel *currentScore;
    QLabel *historyScore;
    QPushButton *backToMenuBtn;
};

#endif // GAMEOVER_H
