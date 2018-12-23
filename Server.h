//
// Created by yr12 on 17/9/18.
//

#ifndef NUCLEARMRINAANK_SERVER_H
#define NUCLEARMRINAANK_SERVER_H

#include "NetworkConnection.h"

using boost::asio::ip::tcp;


class Server
{
public:
    Server(boost::asio::io_context &io_context, int port);
    std::vector<NetworkConnection::pointer> connections;
private:
    void start_accept();
    void handle_accept(NetworkConnection::pointer new_connection, const boost::system::error_code &error);
    tcp::acceptor acceptor_;
};


#endif //NUCLEARMRINAANK_SERVER_H
