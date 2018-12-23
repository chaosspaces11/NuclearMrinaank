//
// Created by yr12 on 17/9/18.
//

#include "NetworkConnection.h"
#include <istream>
#include <iostream>

std::string makeMessageString()
{
    return std::string("Hello!!!\n");
}

NetworkConnection::pointer NetworkConnection::create(boost::asio::io_context &io_context, Server *parentServer)
{
    return pointer(new NetworkConnection(io_context, parentServer));
}

tcp::socket &NetworkConnection::socket()
{
    return socket_;
}

void NetworkConnection::start()
{
    message_ = makeMessageString();

    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             boost::bind(&NetworkConnection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void NetworkConnection::sendMessage()
{
    message_ = makeMessageString();

    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             boost::bind(&NetworkConnection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

std::string NetworkConnection::recieveMessage()
{
    boost::asio::streambuf buf;
    boost::asio::async_read_until(socket_, buf, "\n", boost::bind(&NetworkConnection::handle_read, shared_from_this(),
                                                                  boost::asio::placeholders::error,
                                                                  boost::asio::placeholders::bytes_transferred()));
    std::string result;
    std::istream is(&buf);
    is >> result;
    std::cerr <<result;
    return result;
}

NetworkConnection::NetworkConnection(boost::asio::io_context &io_context, Server *parent) : socket_(io_context),
                                                                                            parentServer(parent)
{
}



