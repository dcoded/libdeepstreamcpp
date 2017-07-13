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


// typedef websocketpp::client <websocketpp::config::asio_client> client;

// class websocket_endpoint {
// public:
//     websocket_endpoint () {
//         m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
//         m_endpoint.clear_error_channels(websocketpp::log::elevel::all);

//         m_endpoint.init_asio();
//         m_endpoint.start_perpetual();

//         m_thread = websocketpp::lib::make_shared <websocketpp::lib::thread>(&client::run, &m_endpoint);
//     }

//     int connect(std::string const & uri) {
//         websocketpp::lib::error_code ec;

//         client::connection_ptr con = m_endpoint.get_connection(uri, ec);

//         if (ec) {
//             std::cout << "> Connect initialization error: " << ec.message() << std::endl;
//             return -1;
//         }

//         int new_id = m_next_id++;
//         connection_metadata::ptr metadata_ptr = websocketpp::lib::make_shared<connection_metadata>(new_id, con->get_handle(), uri);
//         m_connection_list[new_id] = metadata_ptr;

//         con->set_open_handler(websocketpp::lib::bind(
//             &connection_metadata::on_open,
//             metadata_ptr,
//             &m_endpoint,
//             websocketpp::lib::placeholders::_1
//         ));
//         con->set_fail_handler(websocketpp::lib::bind(
//             &connection_metadata::on_fail,
//             metadata_ptr,
//             &m_endpoint,
//             websocketpp::lib::placeholders::_1
//         ));
//         con->set_close_handler(websocketpp::lib::bind(
//             &connection_metadata::on_close,
//             metadata_ptr,
//             &m_endpoint,
//             websocketpp::lib::placeholders::_1
//         ));

//         m_endpoint.connect(con);

//         return new_id;
//     }

//     void close(int id, websocketpp::close::status::value code, std::string reason) {
//         websocketpp::lib::error_code ec;
        
//         con_list::iterator metadata_it = m_connection_list.find(id);
//         if (metadata_it == m_connection_list.end()) {
//             std::cout << "> No connection found with id " << id << std::endl;
//             return;
//         }
        
//         m_endpoint.close(metadata_it->second->get_hdl(), code, reason, ec);
//         if (ec) {
//             std::cout << "> Error initiating close: " << ec.message() << std::endl;
//         }
//     }
// private:
//     client m_endpoint;
//     websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;
// };