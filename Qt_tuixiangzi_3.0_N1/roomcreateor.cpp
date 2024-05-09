#include "roomcreateor.h"

#include <MyStartBtn.h>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <QPushButton>
#include <QTimer>

RoomCreateor::RoomCreateor(QWidget *parent)
    : QMainWindow{parent}
{
    //配置模式选择的场景
    setFixedSize(QSize(400,400));
    setWindowTitle("推箱子 - 双人模式房间创建与连接");

    //创建菜单栏
    QMenuBar * bar = menuBar() ;
    setMenuBar (bar);

    //创建开始菜单
    QMenu* startMenu = bar->addMenu("开始");

    //创建退出 菜单项
    QAction* quitAction = startMenu->addAction("退出");

    //点击退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QPushButton *btn1 = new QPushButton;
    btn1->setParent(this);
    btn1->setFixedSize(100,50);
    btn1->setText("创建房间");
    btn1->move(80,200);

    QPushButton *btn2 = new QPushButton;
    btn2->setFixedSize(100,50);
    btn2->setParent(this);
    btn2->setText("加入房间");
    btn2->move(220,200);

    MyStartBtn *backbtn = new MyStartBtn(":/Ele/MapImg/back1.png",":/Ele/MapImg/bakc2.png");
    backbtn->setParent(this);
    backbtn->move(this->width()*0.93 - backbtn->width()*0.93,this->height()*0.8);

    connect(backbtn,&QPushButton::clicked,[=](){
        //上一个场景监听这个发出的信号,并且实现延时效果
        QTimer::singleShot(1000,this,[=](){
            emit this->chooseSceneBack();
        });

    });
    user = new Client;
    roomer = new Sever;

    connect(btn1,&QPushButton::clicked,[=](){
        //跳转到服务器界面
        this->hide();
        roomer->show();

    });
    connect(btn2,&QPushButton::clicked,[=](){
        //跳转到客户端界面
        this->hide();
        user->show();
    });

    connect(roomer,&Sever::endGame,[=](){
        roomer->netGame->hide();
        user->netGame->hide();
    });

}

void RoomCreateor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Ele/MapImg/ModeScene.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
