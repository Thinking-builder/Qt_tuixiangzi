#ifndef CLIENT_H
#define CLIENT_H

#include "net_game.h"
#include <QLabel>
#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    Net_game* netGame = NULL;

    ~Client();

private slots:
    void on_connectToH_clicked();

    void on_sendBtn_clicked();

    void on_disconnectbtn_clicked();




private:
    Ui::Client *ui;
    QTcpSocket* m_tcp;
    QLabel* m_status;
};

#endif // CLIENT_H
