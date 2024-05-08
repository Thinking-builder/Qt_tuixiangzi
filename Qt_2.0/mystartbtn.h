#ifndef MYSTARTBTN_H
#define MYSTARTBTN_H

#include <QPushButton>

class MyStartBtn : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyStartBtn(QWidget *parent = nullptr);
    //重新构造函数 - 参数1 正常按钮图片，参数2 按下效果图片
    MyStartBtn(QString normalImg,QString pressImg = "");

    QString normalImgPath;
    QString pressImgPath;

    //弹起特效：
    void zoom1(); //向下跳
    void zoom2(); //向上跳

    //补充美术效果：重写按下和抬起的效果
    void mousePressEvent(QMouseEvent * e);

    void mouseReleaseEvent(QMouseEvent *e);

signals:
};

#endif // MYSTARTBTN_H
