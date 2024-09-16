#ifndef WEATHER_HPP
#define WEATHER_HPP

#include <httplib.h>
#include <json.hpp>
#include <string>
#include <map>

namespace weather {
    struct Response {
        std::string description;
        double temperature;
        double wind;
        int humidity;
    };

    struct ForecastResponse {
        std::string generalTrend;
        std::string temperatureTrend;
        std::string pressureTrend;
        std::string windAverage;
    };

    void to_json(nlohmann::json& j, const Response& r);
    void to_json(nlohmann::json& j, const ForecastResponse& fr);

    void GetCurrentWeather(const httplib::Request& req, httplib::Response& res);
    void GetForecast(const httplib::Request& req, httplib::Response& res);

    std::pair<std::map<std::string, int>, std::map<std::string, int>> getWeatherDescriptionMaps();
    int getDescriptionGrade(const std::string& description);
    ForecastResponse writeForecastResponse(const nlohmann::json& weatherbitResponse);
    std::string getGeneralTrendMessage(int current, int trend);
    std::string getTemperatureTrendMessage(double current, double trend);
    std::string getPressureTrendMessage(int current, int trend);
    std::string getWindTrendMessage(double trend);

    nlohmann::json GetWeatherBitCurrent(const std::string& location);
    nlohmann::json GetWeatherBitForecast(const std::string& location);
    nlohmann::json GetWeatherBitData(const std::string& responseBody);
}

#endif // WEATHER_HPP