//
// Created by yr12 on 17/9/18.
//

#ifndef NUCLEARMRINAANK_NETWORKCONNECTION_H
#define NUCLEARMRINAANK_NETWORKCONNECTION_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

class Server;

class NetworkConnection : public boost::enable_shared_from_this<NetworkConnection>
{
public:
    typedef boost::shared_ptr<NetworkConnection> pointer;

    static pointer create(boost::asio::io_context& io_context, Server* parent);

    tcp::socket& socket();

    void start();

    void sendMessage();
    
    std::string recieveMessage();

private:
    NetworkConnection(boost::asio::io_context& io_context,Server* parent);

    void handle_write(const boost::system::error_code& error, size_t /*bytes_transferred*/);
    
    void handle_read(const boost::system::error_code& error, size_t /*bytes_transferred*/);

    tcp::socket socket_;
    std::string message_;
    Server* parentServer;
};


#endif //NUCLEARMRINAANK_NETWORKCONNECTION_H
