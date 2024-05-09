#include "sever.h"
#include "ui_sever.h"

Sever::Sever(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sever)
{
    ui->setupUi(this);

    ui->port->setText("8899");
    setWindowTitle("服务器");

    //创建监听的服务器对象
    m_s = new QTcpServer(this);//?可能会出现问题！

    connect(m_s,&QTcpServer::newConnection,this,[=](){
        m_tcp = m_s->nextPendingConnection();
        m_status->setPixmap(QPixmap(":/Ele/dui.png").scaled(20,20));

        //检测是否可以接受数据
        connect(m_tcp,&QTcpSocket::readyRead,this,[=](){

            QByteArray data = m_tcp->readAll();
            ui->Record->append("客户端： " + data);
        });

        connect(m_tcp,&QTcpSocket::disconnected,this,[=](){
            m_tcp->close();
            m_tcp->deleteLater(); //delete;
            m_status->setPixmap(QPixmap(":/Ele/cuowu.png").scaled(20,20));

        });
    });




    //状态栏目
    m_status = new QLabel;
    m_status->setPixmap(QPixmap(":/Ele/cuowu.png").scaled(20,20));
    ui->statusbar->addWidget(new QLabel("连接状态："));
    ui->statusbar->addWidget(m_status);


}

Sever::~Sever()
{
    delete ui;
}


void Sever::on_setListen_clicked()
{
    unsigned short port = ui->port->text().toUShort();
    m_s->listen(QHostAddress::Any,port);
    ui->setListen->setDisabled(true);
}


void Sever::on_pushButton_2_clicked()
{
    QString msg = ui->Message->toPlainText();
    m_tcp->write(msg.toUtf8());
    ui->Record->append("服务器端： " + msg);
    ui->Message->clear();
}


void Sever::on_StartGame_clicked()
{
    QString mesg = "#[系统自动]游戏即将开始……";
    m_tcp->write(mesg.toUtf8());
    // m_tcp->close();
    // this->hide();
    netGame = new Net_game;

    netGame->setWindowTitle("房主的room");
    netGame->show();
    connect(netGame,&Net_game::whowin,[=](){
        QString mesg = "![系统自动]1房主（服务器端）完成了胜利";
        m_tcp->write(mesg.toUtf8());
        emit this->endGame();
    });
}

