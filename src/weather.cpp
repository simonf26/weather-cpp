#include "weather.hpp"
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace weather {
    void to_json(nlohmann::json& j, const Response& r) {
        j = nlohmann::json{{"description", r.description},
                          {"temperature", r.temperature},
                          {"wind", r.wind},
                          {"humidity", r.humidity}};
    }

    void to_json(nlohmann::json& j, const ForecastResponse& fr) {
        j = nlohmann::json{{"general_trend", fr.generalTrend},
                          {"temperature_trend", fr.temperatureTrend},
                          {"pressure_trend", fr.pressureTrend},
                          {"wind_average", fr.windAverage}};
    }

    std::pair<std::map<std::string, int>, std::map<std::string, int>> getWeatherDescriptionMaps() {
        std::map<std::string, int> weatherDescriptionMap = {
            {"clear", 0},
            {"cloud", 10},
            {"rain", 20},
            {"snow", 30},
        };
        std::map<std::string, int> adjectivesMap = {
            {"Few", -2},
            {"Light", -2},
            {"Scattered", 1},
            {"Moderate", 1},
            {"Broken", 2},
            {"Overcast", 3},
            {"Heavy", 5},
        };
        return {weatherDescriptionMap, adjectivesMap};
    }

    int getDescriptionGrade(const std::string& description) {
        auto [weatherDescriptionMap, adjectivesMap] = getWeatherDescriptionMaps();
        int main = 0;
        int adjective = 0;

        for (const auto& [key, value] : weatherDescriptionMap) {
            if (description.find(key) != std::string::npos) {
                main = value;
                break;
            }
        }

        for (const auto& [key, value] : adjectivesMap) {
            if (description.find(key) != std::string::npos) {
                adjective = value;
                break;
            }
        }

        return main + adjective;
    }

    std::string getGeneralTrendMessage(int current, int trend) {
        std::string trendMessage = "Stable";
        if (trend - current > 2) {
            trendMessage = "Degrading";
        } else if (trend - current < -2) {
            trendMessage = "Improving";
        }
        return trendMessage;
    }

    std::string getTemperatureTrendMessage(double current, double trend) {
        std::string temperatureTrendMessage = "Stable";
        if (trend - current > 0.5) {
            temperatureTrendMessage = "Rising";
        } else if (trend - current < -0.5) {
            temperatureTrendMessage = "Falling";
        }
        return temperatureTrendMessage;
    }

    std::string getPressureTrendMessage(int current, int trend) {
        std::string pressureTrendMessage = "Stable";
        if (trend - current > 10) {
            pressureTrendMessage = "Rising";
        } else if (trend - current < -10) {
            pressureTrendMessage = "Falling";
        }
        return pressureTrendMessage;
    }

    std::string getWindTrendMessage(double trend) {
        struct Range {
            double maxSpeed;
            std::string message;
        };
        Range ranges[] = {
            {1, "Calm"},
            {5, "Light Air"},
            {11, "Light Breeze"},
            {19, "Gentle Breeze"},
            {28, "Moderate Breeze"},
            {38, "Fresh Breeze"},
            {49, "Strong Breeze"},
            {61, "Near Gale"},
            {74, "Gale"},
            {88, "Strong Gale"},
            {102, "Storm"},
            {117, "Violent Storm"},
        };
        for (const auto& rangeInfo : ranges) {
            if (trend < rangeInfo.maxSpeed) {
                return rangeInfo.message;
            }
        }
        return "Hurricane";
    }

    ForecastResponse writeForecastResponse(const nlohmann::json& weatherbitResponse) {
        auto currentWeather = weatherbitResponse["data"][0];
        int currentDescriptionGrade = getDescriptionGrade(currentWeather["weather"]["description"]);

        int generalTrend = 0;
        double temperatureTrend = 0.0;
        int pressureTrend = 0;
        double windTrend = 0.0;

        for (size_t i = 0; i < 7; ++i) {
            auto weather = weatherbitResponse["data"][i];
            generalTrend += getDescriptionGrade(weather["weather"]["description"]);
            temperatureTrend += weather["temp"].get<double>();
            pressureTrend += weather["rh"].get<int>();
            windTrend += weather["wind_spd"].get<double>();
        }

        generalTrend /= 7;
        temperatureTrend /= 7;
        pressureTrend /= 7;
        windTrend /= 7;

        ForecastResponse forecastResponse = {
            getGeneralTrendMessage(currentDescriptionGrade, generalTrend),
            getTemperatureTrendMessage(currentWeather["temp"].get<double>(), temperatureTrend),
            getPressureTrendMessage(currentWeather["rh"].get<int>(), pressureTrend),
            getWindTrendMessage(windTrend)
        };

        return forecastResponse;
    }

    nlohmann::json GetWeatherBitCurrent(const std::string& location) {
        const char* apiKey = std::getenv("WEATHERBIT_API_KEY");
        if (!apiKey) {
            throw std::runtime_error("WEATHERBIT_API_KEY is not set");
        }

        std::string url = "http://api.weatherbit.io/v2.0/current?city=" + httplib::detail::encode_url(location) + "&key=" + apiKey;
        httplib::Client cli("http://api.weatherbit.io");
        auto res = cli.Get(url.c_str());

        if (!res) {
            throw std::runtime_error("Failed to get response from Weatherbit API");
        }

        return nlohmann::json::parse(res->body);
    }

    nlohmann::json GetWeatherBitForecast(const std::string& location) {
        const char* apiKey = std::getenv("WEATHERBIT_API_KEY");
        if (!apiKey) {
            throw std::runtime_error("WEATHERBIT_API_KEY is not set");
        }

        std::string url = "http://api.weatherbit.io/v2.0/forecast/daily?city=" + httplib::detail::encode_url(location) + "&key=" + apiKey;
        httplib::Client cli("http://api.weatherbit.io");
        auto res = cli.Get(url.c_str());

        if (!res) {
            throw std::runtime_error("Failed to get response from Weatherbit API");
        }

        return nlohmann::json::parse(res->body);
    }

    nlohmann::json GetWeatherBitData(const std::string& responseBody) {
        return nlohmann::json::parse(responseBody);
    }

    void GetCurrentWeather(const httplib::Request& req, httplib::Response& res) {
        if (!req.has_param("location")) {
            res.set_content("Location parameter is required", "text/plain");
            res.status = 400;
            return;
        }

        std::string location = req.get_param_value("location");
        nlohmann::json weatherbitResponse;

        try {
            weatherbitResponse = GetWeatherBitCurrent(location);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            res.set_content(e.what(), "text/plain");
            res.status = 500;
            return;
        }

        if (weatherbitResponse["data"].empty()) {
            std::cout << weatherbitResponse << std::endl;
            res.set_content("City not found", "text/plain");
            res.status = 404;
            return;
        }

        Response response = {
            weatherbitResponse["data"][0]["weather"]["description"],
            weatherbitResponse["data"][0]["temp"],
            weatherbitResponse["data"][0]["wind_spd"],
            weatherbitResponse["data"][0]["rh"]
        };

        res.set_content(nlohmann::json(response).dump(), "application/json");
    }

    void GetForecast(const httplib::Request& req, httplib::Response& res) {
        if (!req.has_param("location")) {
            res.set_content("Location parameter is required", "text/plain");
            res.status = 400;
            return;
        }

        std::string location = req.get_param_value("location");
        nlohmann::json weatherbitResponse;

        try {
            weatherbitResponse = GetWeatherBitForecast(location);
        } catch (const std::exception& e) {
            res.set_content(e.what(), "text/plain");
            res.status = 500;
            return;
        }

        if (weatherbitResponse["data"].empty()) {
            std::cout << weatherbitResponse << std::endl;
            res.set_content("City not found", "text/plain");
            res.status = 404;
            return;
        }

        ForecastResponse forecastResponse = writeForecastResponse(weatherbitResponse);

        res.set_content(nlohmann::json(forecastResponse).dump(), "application/json");
    }
}