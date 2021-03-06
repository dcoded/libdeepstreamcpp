#pragma once

#include "connection_event_handler.hpp"
#include "log.hpp"
#include "mailbox.hpp"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

class connection : public connection_event_handler {

    using asio_client = websocketpp::config::asio_client;
    using client      = websocketpp::client <asio_client>;
    using endpoint    = websocketpp::endpoint<websocketpp::connection<asio_client>, asio_client>;

    public: explicit connection(
        const client* client,
        const websocketpp::connection_hdl hdl, 
        const std::string uri);

    public: ~connection();

    public: bool send(const std::string message);
    public: bool close();

    // public: std::promise<void> await_connection();
    // public: std::promise<void> 

    private: endpoint* endpoint_;
    private: const websocketpp::connection_hdl hdl_;
    private: const std::string uri_;

    private: mailbox<std::string> inbox_;
    private: mailbox<std::string> outbox_;
};