#include <iostream>
#include <httplib.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "weather.hpp"

int main() {
    httplib::Server svr;

    svr.Get("/weather/current", weather::GetCurrentWeather);
    svr.Get("/weather/forecast", weather::GetForecast);

    const char* port = std::getenv("PORT");
    if (port == nullptr) {
        port = "8080";
    }

    std::cout << "Server is running on port " << port << std::endl;

    if (!svr.listen("0.0.0.0", std::stoi(port))) {
        std::cerr << "Server failed to start" << std::endl;
        return 1;
    }

    return 0;
}