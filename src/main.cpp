#include <spdlog/spdlog.h>

#include <endpoint.hpp>


int main(int argc, char* argv[])
{

    // Console logger with color
    auto console = spdlog::stdout_color_mt("console");
    console->info("Starting deepstream client.");

    endpoint server("ws://echo.websocket.org");

    auto conn = server.connect();
    while(!conn.send("hello world"));
    sleep(5);
    conn.close();

    return 0;
}