#include "Role.h"

#include <QPainter>

Role::Role(QObject *parent)
    : QObject{parent}
{
    //初始化人物所在的位置
    mRow = 1;
    mCol = 1;
    mImg2 = QImage(":/Ele/MapImg/player-d.png");
    mImg = QImage(":/Ele/MapImg/player-t.png");
    mImg3 = QImage(":/Ele/MapImg/player-l.png");
    mImg4 = QImage(":/Ele/MapImg/player-r.png");
    //显示位置：
    mPaintPos = QPoint(mCol,mRow)*mImg.width()*0.5;
    //
}

void Role::move(int _dRow,int _dCol,int mode_num)
{
    mRow += _dRow;
    mCol += _dCol;

    if(mode_num == 1)
    {
        mPaintPos = QPoint(mCol,mRow)*mImg.width()*0.5;
    }else if(mode_num == 2)
    {
        mPaintPos = QPoint(mCol,mRow)*mImg2.width()*0.5;
    }else if(mode_num == 3)
    {
        mPaintPos = QPoint(mCol,mRow)*mImg3.width()*0.5;
    }else if(mode_num == 4)
    {
        mPaintPos = QPoint(mCol,mRow)*mImg4.width()*0.5;
    }
}

void Role::Paint_self(QPainter *_p,QPoint _pos,int mode_num)
{
    if(mode_num == 1)_p->drawImage(QRect(+_pos.x()+mPaintPos.x(),_pos.y()+mPaintPos.y(),mImg.width()*0.5,mImg.height()*0.5),mImg);
    if(mode_num == 2)_p->drawImage(QRect(+_pos.x()+mPaintPos.x(),_pos.y()+mPaintPos.y(),mImg2.width()*0.5,mImg2.height()*0.5),mImg2);
    if(mode_num == 3)_p->drawImage(QRect(+_pos.x()+mPaintPos.x(),_pos.y()+mPaintPos.y(),mImg3.width()*0.5,mImg3.height()*0.5),mImg3);
    if(mode_num == 4)_p->drawImage(QRect(+_pos.x()+mPaintPos.x(),_pos.y()+mPaintPos.y(),mImg2.width()*0.5,mImg2.height()*0.5),mImg4);
}
