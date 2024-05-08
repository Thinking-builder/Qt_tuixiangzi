#include "chooselevelscene.h"

#include <QMenuBar>
#include <mystartbtn.h>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QMessageBox>

chooseLevelScene::chooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置模式选择的场景
    setFixedSize(QSize(700,700));
    setWindowTitle("推箱子 - 经典模式 - 关卡选择");

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

    //返回按钮
    MyStartBtn *backbtn = new MyStartBtn(":/Ele/MapImg/back1.png",":/Ele/MapImg/bakc2.png");
    backbtn->setParent(this);
    backbtn->move(this->width()*0.9 - backbtn->width()*0.9,this->height()*0.85);

    connect(backbtn,&QPushButton::clicked,[=](){
        //上一个场景监听这个发出的信号
        QTimer::singleShot(300,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //创建选择关卡的按钮：
    for(int i = 0;i<8;i++)
    {
        MyStartBtn* menubtn = new MyStartBtn(":/Ele/MapImg/guanka.png");
        menubtn->setParent(this);
        menubtn->move(150+i%4*100,250 + i/4*100);

        connect(menubtn,&QPushButton::clicked,[=](){
            menubtn->zoom1();
            menubtn->zoom2();

            //进入游戏场景
            this->hide();
            play = new PlayScene(i+1);//显示游戏场景

            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->show();
                play->hide();
            });

            play->show();
        });


        QLabel* Label = new QLabel;
        Label->setParent(this);
        Label->setFixedSize(menubtn->width(),menubtn->height());
        Label->setText(QString::number(i+1));
        //设置Label的对齐方式：水平居中和垂直居中
        Label->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        //设置鼠标穿透
        Label->setAttribute(Qt::WA_TransparentForMouseEvents);

        Label->move(150+i%4*100,250 + i/4*100);


    }
}

void chooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Ele/MapImg/ModeScene.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/Ele/MapImg/Select_T.png");
    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
}
