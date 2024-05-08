#ifndef CHOOSEMODESCENE_H
#define CHOOSEMODESCENE_H

#include <QMainWindow>
#include <chooselevelscene.h>

class ChooseModeScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseModeScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);

    chooseLevelScene *chooselevelS = NULL;
signals:
    //写一个可以告诉主场景的我要返回的信号
    void chooseSceneBack();
};


#endif // CHOOSEMODESCENE_H
