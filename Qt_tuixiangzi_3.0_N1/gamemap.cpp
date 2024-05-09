#include "gamemap.h"

#include <QFile>
#include <QDebug>

GameMap::GameMap(QObject * parent):QObject(parent)
{
    mRow = 0;
    mCol = 0;
    mPArr = nullptr;
}

void GameMap::Clear()//内存清理函数，清理掉申请的堆空间
{
    if(mPArr != nullptr)
    {
        for(int i = 0;i < mRow;i++)
        {
            delete []mPArr[i];
        }
        delete[] mPArr;
    }
}//内存清理函数

bool GameMap::initByFile(QString FileName)//这里做一个二维地图的基础映射（0，1）
{
    QFile file(FileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    //读取所有内容
    QByteArray arrAll = file.readAll();//注意这是字节数组
    arrAll.replace("\r\n","\n");
    QList<QByteArray>linelist = arrAll.split('\n');//使用链表容器来容纳
    mRow = linelist.size();//确定行数

    // for(int i=0; i<linelist.size(); ++i)
    // {
    //     qDebug() << linelist.at(i);
    // }用作调试观察是否正确分割。。。。
    mPArr = new int*[mRow];

    for(int i = 0;i< mRow;i++)
    {
        QList<QByteArray> colList = linelist[i].split(',');
        mCol = colList.size();//确定列
        mPArr[i] = new int[mCol];//开辟列

        for(int j = 0; j < mCol;j++)
        {
            mPArr[i][j] = colList[j].toInt();
        }
    }

    return true;

}

void GameMap::Paint(QPainter *_p,QPoint _Pos)
{
    for(int i = 0;i<mRow;i++)
    {
        for(int j = 0;j<mCol;j++)
        {
            QString imgUrl;
            switch(mPArr[i][j])
            {
            case 0:imgUrl = ":/Ele/MapImg/road.png";break;
            case 1:imgUrl = ":/Ele/MapImg/wall.png";break;
            case 2:imgUrl = ":/Ele/MapImg/box.png";break;
            case 4:imgUrl = ":/Ele/MapImg/point.png";break;//目前还缺少这张图片
            case 5:imgUrl = ":/Ele/MapImg/inpoint.png";break;//目前还缺少这张图片
            }

            QImage img(imgUrl);
            // qDebug()<<imgUrl<<" - "<<QRect(j*img.width(),i*img.height(),img.width(),img.height());
            _p->drawImage(QRect(_Pos.x()+j*img.width()*0.5,_Pos.y()+i*img.height()*0.5,img.width()*0.5,img.height()*0.5),img);//注意括号！
            //_p->drawImage(_Pos,img);
        }
    }
}
