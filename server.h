#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);


public slots:
    void incomingConnection(qintptr socketDescr);
    void slotServerReadReady();
    void slotClientDisconected();

private:
    QTcpSocket* socket;
};

#endif // SERVER_H
