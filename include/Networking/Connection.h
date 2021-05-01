#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <Networking/Message.h>
#include <Networking/MessageQ.h>
#include <SFML/Network.hpp>

class Connection
{
    std::string address;
    int port_number;

    sf::TcpSocket socket;
    sf::TcpListener listener;

    bool connected;

public:
    Connection(std::string address, int port_number);
    ~Connection();

    void get_connection();
    Message get_next();
};

#endif