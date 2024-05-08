#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include "playscene.h"
#include "Role.h"

#include <QMainWindow>


class chooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseLevelScene(QWidget *parent = nullptr);

    //绘制选择关卡的背景函数
    void paintEvent(QPaintEvent*);


    PlayScene* play = NULL;

signals:
    //写一个可以告诉主场景的我要返回的信号
    void chooseSceneBack();

};

#endif // CHOOSELEVELSCENE_H
