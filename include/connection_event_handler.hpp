#pragma once

#include <spdlog/spdlog.h>

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

class connection_event_handler {

    using asio_client = websocketpp::config::asio_client;
    using client      = websocketpp::client <asio_client>;

    public: void on_open(client* client , websocketpp::connection_hdl hdl);
    public: void on_error(client* client, websocketpp::connection_hdl hdl);
    public: void on_close(client* client, websocketpp::connection_hdl hdl);
    public: void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);
};