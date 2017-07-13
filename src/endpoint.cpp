#include <endpoint.hpp>

endpoint::endpoint(const std::string uri)
:    uri_(uri)
{   
    DEBUG_TRACE;
    auto console = spdlog::get("console");
    console->info("setting up endpoint: {}", uri);
    client_.clear_access_channels(websocketpp::log::alevel::all);
    client_.clear_error_channels(websocketpp::log::elevel::all);

    console->info("starting event loop for endpoint: {}", uri);
    client_.init_asio();
    client_.start_perpetual();
    thread_ = websocketpp::lib::make_shared <websocketpp::lib::thread>(
        &client::run, 
        &client_);
}

endpoint::~endpoint()
{   
    DEBUG_TRACE;
    auto console = spdlog::get("console");
    console->info("taking down endpoint: {}", uri_);
    client_.stop_perpetual();
    thread_->join();
}

connection&& endpoint::connect()
{   
    DEBUG_TRACE;
    auto console = spdlog::get("console");
    console->info("creating connection object");

    websocketpp::lib::error_code ec;

    console->info("getting connection from endpoint");
    auto ws_conn = client_.get_connection(uri_, ec);
    connection conn(&client_, ws_conn->get_handle(), uri_);
    if (!ec)
    {
        console->info("setting connection handlers");

        ws_conn->set_open_handler(websocketpp::lib::bind(
            &connection::on_open,
            &conn,
            &client_,
            websocketpp::lib::placeholders::_1
        ));

        ws_conn->set_fail_handler(websocketpp::lib::bind(
            &connection::on_error,
            &conn,
            &client_,
            websocketpp::lib::placeholders::_1
        ));

        ws_conn->set_close_handler(websocketpp::lib::bind(
            &connection::on_close,
            &conn,
            &client_,
            websocketpp::lib::placeholders::_1
        ));

        ws_conn->set_message_handler(websocketpp::lib::bind(
            &connection::on_message,
            &conn,
            websocketpp::lib::placeholders::_1,
            websocketpp::lib::placeholders::_2
        ));

        console->info("connecting...");
        client_.connect(ws_conn);
    }
    else
    {
        console->error("failed to get connection from endpoint!, {}", ec.message());
    }

    return std::move(conn);
}