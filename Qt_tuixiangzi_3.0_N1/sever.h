#ifndef SEVER_H
#define SEVER_H

#include "net_game.h"

#include <QLabel>
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Sever;
}

class Sever : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sever(QWidget *parent = nullptr);
    Net_game* netGame = NULL;

    ~Sever();
signals:
    void endGame();

private slots:
    void on_setListen_clicked();

    void on_pushButton_2_clicked();

    void on_StartGame_clicked();


private:
    Ui::Sever *ui;
    QTcpServer* m_s;
    QTcpSocket* m_tcp;
    QLabel *m_status;
};

#endif // SEVER_H
