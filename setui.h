#ifndef SETUI_H
#define SETUI_H

#include <QWidget>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>
#include <QFont>
#include <QDebug>
#include <QSound>
class setUi : public QWidget
{
    Q_OBJECT
public:
    explicit setUi(QWidget *parent = 0);
    void setui();

signals:
    void sbackToMenuSingal();
public slots:
    void musicOnOffSlot();
    void gameGuideOnOffSlot();
    void sbackToMenuSlot();
    void leftBtnSlot();
    void rightBtnSlot();
private:
    QLabel *title;
    QPushButton* musicOnOff;
    QPushButton* gameGuide;
    QPushButton* leftBtn;
    QPushButton* rightBtn;
    QLabel* gameLevel;
    QPushButton* backBtn;
};

#endif // SETUI_H
