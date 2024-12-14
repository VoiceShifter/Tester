# include <QCoreApplication>
# include <QtNetwork/QTcpSocket>
# include <QtNetwork/QHostAddress>

#include <iostream>
#include <map>
#include <string>
#include <functional>
# include <sstream>

std::string AuthorizeUser (std::string Username, std::string Password)
{
    std::stringstream Query{};
    Query << "GET /Api/User/?Email=" << Username << "&Password=" << Password;
    return Query.str();

}

std::string AddUser (std::string Username, std::string Password, std::string PhoneNumber)
{
    std::stringstream Query{};
    Query << "PUT /Api/User/?Email=" << Username << "&Password=" << Password
          << "&PhoneNumber=" << PhoneNumber;
    return Query.str();
}

std::string DeleteUser (std::string Username, std::string Password)
{
    std::stringstream Query{};
    Query << "POST /Api/User/?Email=" << Username << "&Password=" << Password;
    return Query.str();
}
int main(int argc, char *argv[])
{


    QTcpSocket MainSocket{};
    MainSocket.bind(32323);
    MainSocket.connectToHost(QHostAddress::LocalHost, 32323);
    MainSocket.waitForConnected(-1);
    //QByteArray Message{AddUser("Username9", "1", "123").c_str()};
    QByteArray Message{DeleteUser("Username9", "1").c_str()}; //AddUser("Username9", "1", "123").c_str()
    MainSocket.write(Message);
    MainSocket.flush();
    MainSocket.waitForBytesWritten();
    std::string lMessage{};
    if (MainSocket.waitForReadyRead()) {
        QByteArray data = MainSocket.readAll(); // Read data from the socket
        lMessage = data.toStdString();
        std::cout << lMessage << '\n';
    } else {
        std::cerr << "Failed to read from socket: " << MainSocket.errorString().toStdString() << std::endl;
    }
    _sleep(5000);
    MainSocket.disconnectFromHost();
    MainSocket.waitForDisconnected();
    MainSocket.close();

}
