#pragma once

#include "connection.hpp"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <spdlog/spdlog.h>

typedef websocketpp::client <websocketpp::config::asio_client> client;

class endpoint {
	public: explicit endpoint(const std::string uri);
	public: connection&& connect();

	public: ~endpoint();

	private: std::string uri_;
	private: websocketpp::client <websocketpp::config::asio_client> client_;
	private: websocketpp::lib::shared_ptr<websocketpp::lib::thread> thread_;

};