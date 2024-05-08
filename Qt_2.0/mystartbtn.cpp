#include "mystartbtn.h"
#include <QMessageBox>
#include <QPropertyAnimation>

MyStartBtn::MyStartBtn(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load (normalImg) ;
    if (!ret)
    {
        QMessageBox::warning(this,"警告","图片文件初始化失败");
        return;
    }

    //设置图片固定大小
    this->setFixedSize(QSize(pix.width (),pix.height()));
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix) ;
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyStartBtn::zoom1()
{
    //创建对象
    QPropertyAnimation * animation = new QPropertyAnimation (this,"geometry");
    //设置动画间隔时间
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}

void MyStartBtn::zoom2()
{
    //创建对象
    QPropertyAnimation * animation = new QPropertyAnimation (this,"geometry");
    //设置动画间隔时间
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}

void MyStartBtn::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath !="")
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath) ;
        if (!ret)
        {
            QMessageBox::warning(this,"警告","图片文件初始化失败");
            return;
        }

        //设置图片固定大小
        this->setFixedSize(QSize(pix.width (),pix.height()));
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix) ;
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //让父类执行其他内容：
    return QPushButton::mousePressEvent(e);
}

void MyStartBtn::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath) ;
        if (!ret)
        {
            QMessageBox::warning(this,"警告","图片文件初始化失败");
            return;
        }

        //设置图片固定大小
        this->setFixedSize(QSize(pix.width (),pix.height()));
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix) ;
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //让父类执行其他内容：
    return QPushButton::mouseReleaseEvent(e);
}
