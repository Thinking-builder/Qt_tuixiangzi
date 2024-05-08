#include "choosemodescene.h"

#include <QMenuBar>
#include <mystartbtn.h>
#include <QPainter>
#include <QTimer>

ChooseModeScene::ChooseModeScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置模式选择的场景
    setFixedSize(QSize(700,700));
    setWindowTitle("推箱子 - 模式选择");

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

    MyStartBtn* ClassicBtn = new MyStartBtn(":/Ele/MapImg/classic.png");
    ClassicBtn->setParent(this);
    ClassicBtn->move(this->width()*0.25 - ClassicBtn->width()*0.25,this->height()*0.4);

    MyStartBtn* TwoBtn = new MyStartBtn(":/Ele/MapImg/two.png");
    TwoBtn->setParent(this);
    TwoBtn->move(this->width()*0.75 - TwoBtn->width()*0.75,this->height()*0.4);

    //构建选择模式的窗口
    chooselevelS = new chooseLevelScene;

    //监听选择关卡的返回信号
    connect(chooselevelS,&chooseLevelScene::chooseSceneBack,[=](){
        this->show();
        chooselevelS->hide();
    });

    connect(ClassicBtn,&QPushButton::clicked,[=](){
        //制作按钮弹起特效：
        ClassicBtn->zoom1();
        ClassicBtn->zoom2();

        //进入到选择模式中
        QTimer::singleShot(700,this,[=](){
            this->hide();
            //需要延时操作 显示自己的动画效果
            chooselevelS->show();


        });


    });

    connect(TwoBtn,&QPushButton::clicked,[=](){
        //制作按钮弹起特效：
        TwoBtn->zoom1();
        TwoBtn->zoom2();

        //进入到选择模式中
        QTimer::singleShot(700,this,[=](){
            this->hide();
            //需要延时操作 显示自己的动画效果
            chooselevelS->show();
        });


    });

    //返回按钮
    MyStartBtn *backbtn = new MyStartBtn(":/Ele/MapImg/back1.png",":/Ele/MapImg/bakc2.png");
    backbtn->setParent(this);
    backbtn->move(this->width()*0.9 - backbtn->width()*0.9,this->height()*0.85);

    connect(backbtn,&QPushButton::clicked,[=](){
        //上一个场景监听这个发出的信号,并且实现延时效果
        QTimer::singleShot(1000,this,[=](){
            emit this->chooseSceneBack();
        });

    });
}

void ChooseModeScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Ele/MapImg/ModeScene.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
