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

std::string AddSubscription(std::string Username, std::string Password)
{
    std::stringstream Query{};
    Query << "POST /Api/User/Subscription/?Email=" << Username << "&Password=" << Password;
    return Query.str();
}

std::string AuthorizeArtist (std::string Username, std::string Password)
{
    std::stringstream Query{};
    Query << "GET /Api/Artist/?Email=" << Username << "&Password=" << Password;
    return Query.str();

}

std::string AddArtist (std::string Username, std::string Password, std::string PhoneNumber)
{
    std::stringstream Query{};
    Query << "PUT /Api/Artist/?Email=" << Username << "&Password=" << Password
          << "&PhoneNumber=" << PhoneNumber;
    return Query.str();
}

std::string DeleteArtist (std::string Username, std::string Password)
{
    std::stringstream Query{};
    Query << "POST /Api/Artist/?Email=" << Username << "&Password=" << Password;
    return Query.str();
}

std::string PendingRequest(std::string Username, std::string Album, std::string Name)
{
    std::stringstream Query{};
    Query << "POST /Api/Artist/Releases/?Email=" << Username
          << "&Album=" << Album << "&Name=" << Name;
    std::cout << Query.str();
    return Query.str();
}


int main(int argc, char *argv[])
{


    QTcpSocket MainSocket{};
    MainSocket.bind(32324); //323234 - artist 32323 - users
    MainSocket.connectToHost(QHostAddress::LocalHost, 32324);
    MainSocket.waitForConnected(-1);
    //QByteArray Message{AddUser("Username9", "1", "1").c_str()};
    //QByteArray Message{DeleteUser("Username9", "1").c_str()}; //AddUser("Username9", "1", "123").c_str()
    //QByteArray Message{AddSubscription("Username9", "1").c_str()};
    //QByteArray Message{AddArtist("Username9", "1", "123").c_str()}; //AddUser("Username9", "1", "123").c_str()
    //QByteArray Message{DeleteArtist("Username9", "1").c_str()};
    QByteArray Message{PendingRequest("Username9", "Demon_Days", "Feels_good_inc").c_str()};
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
