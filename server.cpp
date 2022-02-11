#include "server.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    if (listen(QHostAddress::Any, 1234) ) {
        qDebug() << "Server started successfully!";
    }
    else {
        qDebug() << "Server was not started! Error!";
    }
}

void Server::incomingConnection(qintptr socketDescr)
{
//    socket = this->nextPendingConnection();
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescr);

    QTcpSocket::SocketError err = socket->error();
    QString str = socket->errorString();
    bool check = socket->isValid();

    socket->write("Hello from server!\n\n" );
    qDebug() << "Client connected with id "<<socketDescr;

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotServerReadReady);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

}


void Server::slotServerReadReady()
{
    while(socket->bytesAvailable() > 0) {
        QByteArray data = socket->readAll();
        socket->write(data);
        qDebug() << data;
    }

}


void Server::slotClientDisconected()
{
    socket->close();
}
