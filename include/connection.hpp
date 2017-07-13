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

class connection : public connection_event_handler {

	using asio_client = websocketpp::config::asio_client;
	using client      = websocketpp::client <asio_client>;
	using endpoint    = websocketpp::endpoint<websocketpp::connection<asio_client>, asio_client>;
	
	public: explicit connection(
		const client* client,
		const websocketpp::connection_hdl hdl, 
		const std::string uri);

	public: bool send(const std::string message);
	public: bool close();

	private: bool flush();

	private: endpoint* endpoint_;
	private: const websocketpp::connection_hdl hdl_;
	private: const std::string uri_;
};