#include <spdlog/spdlog.h>

#include <endpoint.hpp>


int main(int argc, char* argv[])
{
    // Console logger with color
    auto console = spdlog::stdout_color_mt("console");
    console->info("Starting deepstream client.");

    endpoint server("ws://echo.websocket.org");

    auto conn = server.connect(); 
    while(!conn.send("ping"));

    sleep(5);

    return 0;
}