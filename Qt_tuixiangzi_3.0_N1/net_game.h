#ifndef NET_GAME_H
#define NET_GAME_H

#include <QMainWindow>
#include "Role.h"
#include "gamemap.h"

class Net_game : public QMainWindow
{
    Q_OBJECT
public:
    explicit Net_game(QWidget *parent = nullptr);
    //地图加载的硬件函数：
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    void Collision(int _dRow,int _dCol,int num);
    void win();

    int LevelIndex;//记录所选关卡；
    int mode_num = 2;

    Role* mRole;
    GameMap* mPMap;
    QPainter* mMapPainter;

    //游戏更新定时器：
    QTimer* mtimer;



signals:
    //写一个可以告诉主场景的我要返回的信号
    void whowin();
    void chooseSceneBack();
};

#endif // NET_GAME_H
