#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QObject>
#include <QPainter>

enum MapElement{
    Road = 0,
    Wall = 1,
    Box,
    Point,
    InPoint,
};

class GameMap:public QObject
{
    Q_OBJECT
public:
    explicit GameMap(QObject *parent = nullptr);


    void Clear();
    void Paint(QPainter *p,QPoint _Pos);

    bool initByFile(QString FileName);
    int mRow;
    int mCol;
    int **mPArr;
    //~GameMap();
signals:

public slots:
};

#endif // GAMEMAP_H
