#ifndef ROLE_H
#define ROLE_H

#include <QObject>
#include <QPoint>
#include <QImage>
//属性：位置和移动

class Role : public QObject
{
    Q_OBJECT
public:
    explicit Role(QObject *parent = nullptr);

    //对映在地图上面的映射行列
    int mRow;
    int mCol;
    //画图的位置
    QPoint mPaintPos;
    QImage mImg,mImg2,mImg3,mImg4;

    void move(int _dRow,int _dCol,int mode_num);//方向移动函数
    void Paint_self(QPainter * _p,QPoint _pos,int mode_num);//绘制自己的函数

signals:
};

#endif // ROLE_H
