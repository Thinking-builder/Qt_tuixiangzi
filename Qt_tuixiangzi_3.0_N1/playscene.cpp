#include "playscene.h"

#include <MyStartBtn.h>
#include <QFile>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>



PlayScene::PlayScene(int LevelNum)
{
    this->LevelIndex = LevelNum;


    //初始化游戏场景
    mPMap = new GameMap(this);
    //QString fileName = QFileDialog::getOpenFileName(this,"打开地图","./","*.txt");
    QString fileName;
    switch(LevelIndex)
    {
        case 1:
        {
            fileName = ":/Ele/map1.txt";
            break;
        }
        case 2:
        {
            fileName = ":/Ele/map2.txt";
            break;
        }
        case 3:
        {
            fileName = ":/Ele/map3.txt";
            break;
        }
        case 4:
        {
            fileName = ":/Ele/map4.txt";
            break;
        }
        case 5:
        {
            fileName = ":/Ele/map5.txt";
            break;
        }
        case 6:
        {
            fileName = ":/Ele/map6.txt";
            break;
        }
        case 7:
        {
            fileName = ":/Ele/map7.txt";
            break;
        }
        case 8:
        {
            fileName = ":/Ele/map8.txt";
            break;
        }
    }

    mPMap->initByFile(fileName);
    if(!mPMap->initByFile(fileName))
    {
        QMessageBox::warning(this,"警告","地图文件初始化失败");//提醒用户文件配置出现问题
    }

    mMapPainter = new QPainter(this);//创建画笔；
    mRole = new Role(this);
    mtimer = new QTimer(this);
    mtimer->start(100);

    connect(mtimer,&QTimer::timeout,[this](){
        this->update();
    });//定时更新绘图

    setFixedSize(1024,768);//固定窗口大小

    MyStartBtn *backbtn = new MyStartBtn(":/Ele/MapImg/back1.png",":/Ele/MapImg/bakc2.png");
    backbtn->setParent(this);
    backbtn->move(this->width()*0.9 - backbtn->width()*0.9,this->height()*0.88);

    connect(backbtn,&QPushButton::clicked,[=](){
        //上一个场景监听这个发出的信号,并且实现延时效果
        QTimer::singleShot(1000,this,[=](){
            emit this->chooseSceneBack();
        });

    });
}

void PlayScene::paintEvent(QPaintEvent*event)
{
    mMapPainter->begin(this);//设置画布
    QPainter bgPainter(this);

    // bgPainter.drawImage(Qrect(0,0,1024,768),QIMage"/Users/wangyumeng/000 - 学习/010 - 校培养方案/011 作业/Qtcre/Qt_tuixiangzi/MapImg/point.png"");


    //画地图
    mPMap->Paint(mMapPainter,QPoint(100,0));//设置地图的位置

    //画人物

    mRole->Paint_self(mMapPainter,QPoint(100,0),mode_num);

    mMapPainter->end();//结束
}

void PlayScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())//设置人物的键盘事件 - 人物的上下左右移动
    {
    case Qt::Key_W:
    {
        Collision(-1,0,1);
        break;
    }
    case Qt::Key_S:
    {
        Collision(1,0,2);
        break;
    }
    case Qt::Key_A:
    {
        Collision(0,-1,3);
        break;
    }
    case Qt::Key_D:
    {
        Collision(0,1,4);
        break;
    }
    }
    //逻辑碰撞检测函数
}

void PlayScene::Collision(int _dRow, int _dCol,int num)
{
    //判断位置
    int newRow = mRole->mRow + _dRow;
    int newCol = mRole->mCol + _dCol;

    mode_num = num;
    //通过改变地图元素 - 实现逻辑碰撞
    if(mPMap->mPArr[newRow][newCol] == 1)
    {
        return;
    }else if(mPMap->mPArr[newRow][newCol] == 2)//2是箱子的代数
    {
        if(mPMap->mPArr[newRow+_dRow][newCol+_dCol] == 0)
        {
            //改变地图元素
            mPMap->mPArr[newRow+_dRow][newCol+_dCol] = 2;
            mPMap->mPArr[newRow][newCol] = 0;
        }else if(mPMap->mPArr[newRow+_dRow][newCol+_dCol] == 4)
        {
            mPMap->mPArr[newRow+_dRow][newCol+_dCol] = 5;
            mPMap->mPArr[newRow][newCol] = 0;
        }else {
            return;//否则不能推动箱子
        }
    }else if(mPMap->mPArr[newRow][newCol] == 5){
        if(mPMap->mPArr[newRow+_dRow][newCol+_dCol] == 0)
        {
            //改变地图元素
            mPMap->mPArr[newRow+_dRow][newCol+_dCol] = 4;
            mPMap->mPArr[newRow][newCol] = 2;
        }else if(mPMap->mPArr[newRow+_dRow][newCol+_dCol]== 4){
            mPMap->mPArr[newRow+_dRow][newCol+_dCol] = 5;
            mPMap->mPArr[newRow][newCol] = 4;
        }else{
            return;
        }

    }
    mRole->move(_dRow,_dCol,num);
    qDebug()<<"角色将要前往"<<QPoint(newRow,newCol)<<mPMap->mPArr[4][3];
    win();//每次发生一次键盘事件，我们都去检测一次胜利条件
}

void PlayScene::win()//胜利检测函数：没有优化过，可能会出现突然卡住的情况：我们优化的考量是：开局就检测所有4，然后观察这些4是否exist；
{
    for(int i = 0;i<mPMap->mRow;i++)
    {
        for(int j = 0;j<mPMap->mCol;j++)
        {
            if(mPMap->mPArr[i][j] == 4)
            {
                return;
            }
        }
    }
    QMessageBox::warning(this,"胜利！","哥们，您已经完成胜利✌️");
    //上一个场景监听这个发出的信号,并且实现延时效果
    QTimer::singleShot(100,this,[=](){
        emit this->chooseSceneBack();
    });
}

