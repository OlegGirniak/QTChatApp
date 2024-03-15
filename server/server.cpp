#include "server.h"

server::server()
{
    if(this->listen(QHostAddress::Any, 2222))
    {
        qDebug() << "Server listen";
    }
    else
    {
        qDebug() << "Error";
    }
}


void server::incomingConnection(qintptr socket_descriptor)
{
    QTcpSocket* socket = new QTcpSocket;
    socket->setSocketDescriptor(socket_descriptor);
    connect(socket, &QTcpSocket::readyRead, this, &server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    sockets.push_back(socket);

    qDebug() << "client added";
}

void server::slotReadyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket)
        return;

    QDataStream in(socket);

    in.setVersion(QDataStream::Version::Qt_6_2);

    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "read...";
        QString str;
        in >> str;
        qDebug() << str;
        sendToClient(str);
    }
    else
    {
        qDebug() << "datastream error";
    }
}


void server::sendToClient(QString str)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Version::Qt_6_2);
    out << str;

    for(int i = 0; i < sockets.size(); i++)
    {
        sockets[i]->write(data);
    }
}




