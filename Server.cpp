//
// Created by yr12 on 17/9/18.
//

#include "Server.h"
#include <iostream>

Server::Server(boost::asio::io_context &io_context, int port) : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
    start_accept();
}

void Server::start_accept()
{
    NetworkConnection::pointer new_connection =
            NetworkConnection::create(acceptor_.get_executor().context(), this);

    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&Server::handle_accept, this, new_connection,
                                       boost::asio::placeholders::error));
}

void Server::handle_accept(NetworkConnection::pointer new_connection,
                           const boost::system::error_code &error)
{
    if (!error)
    {
        connections.push_back(new_connection);
        new_connection->start();
    }

    start_accept();
}

void NetworkConnection::handle_write(const boost::system::error_code &error,
                                     size_t /*bytes_transferred*/)
{
    if (error)
    {
        parentServer->connections.erase(
                std::remove(parentServer->connections.begin(), parentServer->connections.end(), shared_from_this()),
                parentServer->connections.end());
    }
}

void NetworkConnection::handle_read(const boost::system::error_code &error,
                                     size_t /*bytes_transferred*/)
{
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        Server server(io_context,9001);

        for(int i =0;i<100;i ++)
        {
            io_context.poll();
            std::cerr << std::to_string(server.connections.size());
            for (int i =0; i < server.connections.size();i++)
            {
                server.connections[i]->sendMessage();
                std::string message = server.connections[i]->recieveMessage();
            }
            usleep(2000000);
            io_context.reset();
        }

    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}