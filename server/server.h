#ifndef SERVER_H
#define SERVER_H
#include<QTcpServer>
#include <QTcpSocket>
#include <QVector>



class server : public QTcpServer
{
    Q_OBJECT;

public:
    server();
    QTcpSocket* socket;

private:
    QVector<QTcpSocket*> sockets;
    QByteArray data;
    void sendToClient(QString str);

public slots:
    void incomingConnection(qintptr socket_descriptor);
    void slotReadyRead();

};

#endif // SERVER_H
