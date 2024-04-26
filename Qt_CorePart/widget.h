#ifndef WIDGET_H
#define WIDGET_H

#include "Role.h"
#include <QTimer>
#include <QWidget>
#include <gamemap.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    void Collision(int _dRow,int _dCol,int num);
    void win();
    ~Widget();
    int mode_num = 2;

private:
    Ui::Widget *ui;

    Role* mRole;
    GameMap* mPMap;
    QPainter* mMapPainter;

    //游戏更新定时器：
    QTimer* mtimer;
};
#endif // WIDGET_H
