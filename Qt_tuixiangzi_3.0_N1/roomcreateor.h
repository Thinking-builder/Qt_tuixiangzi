#ifndef ROOMCREATEOR_H
#define ROOMCREATEOR_H

#include <QMainWindow>
#include "client.h"
#include "sever.h"

class RoomCreateor : public QMainWindow
{
    Q_OBJECT
public:
    explicit RoomCreateor(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);

    Client* user = NULL;
    Sever* roomer = NULL;

signals:
    //写一个可以告诉主场景的我要返回的信号
    void chooseSceneBack();
};

#endif // ROOMCREATEOR_H
