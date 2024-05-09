#include "client.h"
#include "ui_client.h"

#include <QMessageBox>
Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    ui->port->setText("8899");
    ui->ip->setText("127.0.0.1");
    setWindowTitle("客户端");
    ui->disconnectbtn->setDisabled(true);

    m_tcp = new QTcpSocket(this);

    netGame = new Net_game;

    connect(m_tcp,&QTcpSocket::readyRead,this,[=](){
        QByteArray data = m_tcp->readAll();
        ui->record->append("服务器端： "+data);


        if(data[0] == '#')//这里偷了个小懒~ 可以有更好的方法
        {
            netGame->show();


        }
        if(data[0] == '!' && data[7] == '1')
        {
            QMessageBox::warning(this,"失败","你失败了");
            netGame->hide();
        }
    });

    connect(m_tcp,&QTcpSocket::disconnected,this,[=](){
        //QString mesg = "服务器已经断开和你的连接……";
        //m_tcp->write(mesg.toUtf8());
        m_tcp->close();
        m_tcp->deleteLater(); //delete;
        m_status->setPixmap(QPixmap(":/Ele/cuowu.png").scaled(20,20));
        ui->record->append(" - 服务器已经断开和你的连接……");

    });

    connect(m_tcp,&QTcpSocket::connected,this,[=](){
        m_status->setPixmap(QPixmap(":/Ele/dui.png").scaled(20,20));
        ui->record->append(" - 已经成功连接到服务器……");
        ui->connectToH->setDisabled(true);
        ui->disconnectbtn->setEnabled(true);
    });


    //状态栏目
    m_status = new QLabel;
    m_status->setPixmap(QPixmap(":/Ele/cuowu.png").scaled(20,20));
    ui->statusbar->addWidget(new QLabel("连接状态："));
    ui->statusbar->addWidget(m_status);

    //监听信号：

}

Client::~Client()
{
    delete ui;
}

void Client::on_connectToH_clicked()
{
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    m_tcp->connectToHost(QHostAddress(ip),port);

}


void Client::on_sendBtn_clicked()
{
    QString mesg = ui->msg->toPlainText();
    m_tcp->write(mesg.toUtf8());
    ui->record->append("客户端： "+mesg);
    ui->msg->clear();
}


void Client::on_disconnectbtn_clicked()
{
    QString mesg = "[系统自动]客户端已经断开和服务器的连接……";
    m_tcp->write(mesg.toUtf8());
    m_tcp->close();
    ui->connectToH->setDisabled(false);
    ui->disconnectbtn->setEnabled(false);

}
