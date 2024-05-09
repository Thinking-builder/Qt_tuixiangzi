#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <chooselevelscene.h>
#include <choosemodescene.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainScene;
}
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //重写paintEvent文件，实现背景图片
    void paintEvent(QPaintEvent*);

    ChooseModeScene *chooseModeS = NULL;
private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
