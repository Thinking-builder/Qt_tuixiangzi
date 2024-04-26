#include "widget.h"
#include "ui_widget.h"
#include "gamemap.h"

#include <QFileDialog>
#include <QPainter>
#include <QRect>
#include <QMessageBox>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    mPMap = new GameMap(this);
    //QString fileName = QFileDialog::getOpenFileName(this,"打开地图","./","*.txt");
    QString fileName = ":/Ele/map.txt";
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

}


Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent*event)
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

void Widget::keyPressEvent(QKeyEvent *event)
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

void Widget::Collision(int _dRow, int _dCol,int num)
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

void Widget::win()//胜利检测函数：没有优化过，可能会出现突然卡住的情况：我们优化的考量是：开局就检测所有4，然后观察这些4是否exist；
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
}
