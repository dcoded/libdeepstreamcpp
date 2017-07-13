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

connection::~connection()
{
	close();
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
		console->error("unable to send message: '{}', error: {}", 
			message, 
			ec.message());
	}
    return !ec;
}