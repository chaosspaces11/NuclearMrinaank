//
// Created by yr12 on 20/9/18.
//

#ifndef NUCLEARMRINAANK_CLIENT_H
#define NUCLEARMRINAANK_CLIENT_H


#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Client
{
public:
    Client(std::string address, std::string port);

private:
    void resolve_handler(const boost::system::error_code &ec, tcp::resolver::iterator it);

    void read_handler(const boost::system::error_code &ec,
                      std::size_t bytes_transferred);

    void connect_handler(const boost::system::error_code &ec, tcp::endpoint &endpoint);

    void start_connection();

    std::string address_;
    std::string port_;
    boost::asio::io_service io_service_;
    tcp::socket socket_;


};


#endif //NUCLEARMRINAANK_CLIENT_H
