#include <connection_event_handler.hpp>


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
}

