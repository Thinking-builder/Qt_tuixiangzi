#include "mainscene.h"
#include "ui_mainscene.h"
#include <mystartbtn.h>
#include <QPainter>
#include <QTimer>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置固定大小
    setFixedSize(700,700);
    setWindowIcon(QIcon(":/Ele/MapImg/icon_1.png")); //可能是因为Mac系统的问题 没法显示图标
    setWindowTitle(" - 推箱子 -");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });


    //开始按钮：
    MyStartBtn* beginBtn = new MyStartBtn(":/Ele/MapImg/begin.png");
    beginBtn->setParent(this);
    beginBtn->move(this->width()*0.5 - beginBtn->width()*0.5,this->height()*0.4);

    //构建选择模式的窗口
    chooseModeS = new ChooseModeScene;

    connect(chooseModeS,&ChooseModeScene::chooseSceneBack,[=](){
        this->show();
        chooseModeS->hide();
    });

    connect(beginBtn,&QPushButton::clicked,[=](){
        //制作按钮弹起特效：
        beginBtn->zoom1();
        beginBtn->zoom2();

        //进入到选择模式中
        QTimer::singleShot(700,this,[=](){
            this->hide();
            //需要延时操作 显示自己的动画效果
            chooseModeS->show();
        });

        //监听选择关卡的返回信号



    });

}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Ele/MapImg/Scene.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
