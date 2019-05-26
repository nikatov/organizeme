#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "server/server.h"

io_service service;
ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));

void handle_accept(boost::shared_ptr<talk_to_client> client, const boost::system::error_code & err) {
    client->start();
    boost::shared_ptr<talk_to_client> new_client = talk_to_client::new_();
    acceptor.async_accept(new_client->sock(), boost::bind(handle_accept,new_client,_1));
}

int main(int argc, char* argv[]) {
    boost::shared_ptr<talk_to_client> client = talk_to_client::new_();
    acceptor.async_accept(client->sock(), boost::bind(handle_accept,client,_1));
    service.run();
}
