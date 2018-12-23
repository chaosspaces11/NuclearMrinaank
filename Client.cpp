//
// Created by yr12 on 20/9/18.
//

#include <boost/bind.hpp>
#include "Client.h"
#include <iostream>
#include <istream>
#include <boost/array.hpp>

Client::Client(std::string address, std::string port) : address_(address), port_(port), io_service_(),
                                                        socket_(io_service_)
{
    start_connection();
    io_service_.run();
}

void Client::start_connection()
{
    tcp::resolver resolver(io_service_);
    tcp::resolver::query query(address_, port_);
    resolver.async_resolve(query, boost::bind(&Client::resolve_handler, this,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::iterator()));

}

void Client::resolve_handler(const boost::system::error_code &ec, tcp::resolver::iterator it)
{
    if (!ec)
    {
        socket_.async_connect(*it,boost::bind(&Client::connect_handler, this,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::endpoint()));
    }
}

void Client::connect_handler(const boost::system::error_code &ec, tcp::endpoint &endpoint)
{
    if (!ec)
    {
        boost::asio::streambuf buf;
        boost::asio::async_read_until(socket_, buf, "\n", boost::bind(&Client::read_handler, this,
                                                                      boost::asio::placeholders::error,
                                                                      boost::asio::placeholders::bytes_transferred()));
        std::string result;
        std::istream is(&buf);
        is >> result;
        std::cerr << result;
    }
}

void Client::read_handler(const boost::system::error_code &ec,
                          std::size_t bytes_transferred)
{
    if (!ec)
    {
        boost::asio::streambuf buf;
        boost::asio::async_read_until(socket_, buf, "\n",
                                      boost::bind(&Client::read_handler, this,
                                                  boost::asio::placeholders::error,
                                                  boost::asio::placeholders::bytes_transferred()));
        std::string result;
        std::istream is(&buf);
        is >> result;
        std::cerr << result;
    }
}

int main()
{
    Client client("localhost", "9001");

    return 0;
}

