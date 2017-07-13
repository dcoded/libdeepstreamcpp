#include <connection.hpp>

connection::connection(
	const client* client, 
	const websocketpp::connection_hdl hdl, 
	const std::string uri)
:	endpoint_(dynamic_cast<endpoint*> (const_cast<::connection::client*>(client)))
,	hdl_(hdl)
,	uri_(uri)
{
}

bool connection::close()
{
	websocketpp::lib::error_code ec;
	endpoint_->close(hdl_, websocketpp::close::status::going_away, "", ec);
	return !ec;
}

bool connection::send(const std::string message)
{
	auto console = spdlog::get("console");
	console->info("send message: {}", message);

	websocketpp::lib::error_code ec;
	endpoint_->send(hdl_, message, websocketpp::frame::opcode::text, ec);
	if (ec)
	{
		console->error(
			"unable to send message: '{}', error: {}", 
			message, 
			ec.message());
	}
    return !ec;
}




void connection_event_handler::on_open(
	client* client, 
	websocketpp::connection_hdl hdl)
{
	auto conn   = client->get_con_from_hdl(hdl);
    auto server = conn->get_response_header("Server");

	auto console = spdlog::get("console");
	console->info("connection opened on server: {}", server);

}

void connection_event_handler::on_error(
	client* client, 
	websocketpp::connection_hdl hdl)
{
	auto conn = client->get_con_from_hdl(hdl);
	auto ec   = conn->get_ec();

	if (ec)
	{
		auto console = spdlog::get("console");
		console->error("connection event error {}", ec.message());
	}
}

void connection_event_handler::on_close(
	client* client, 
	websocketpp::connection_hdl hdl)
{
	auto conn   = client->get_con_from_hdl(hdl);
    auto server = conn->get_response_header("Server");

	auto console = spdlog::get("console");
	console->info("connection closed on server: {}", server);
}

void connection_event_handler::on_message(
	websocketpp::connection_hdl hdl, 
	client::message_ptr msg)
{
	auto console = spdlog::get("console");
	console->info("recv message: {}", msg->get_payload());


	// if (msg->get_opcode() == websocketpp::frame::opcode::text) {
 //        m_messages.push_back(msg->get_payload());
 //    } else {
 //        m_messages.push_back(websocketpp::utility::to_hex(msg->get_payload()));
 //    }
}













