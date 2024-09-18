#include <gtest/gtest.h>
#include <../include/httplib.h>
#include <iostream>
#include <string>
#include "../include/weather.hpp"

// Testing weatherbit current
TEST(GetWeatherBitCurrent, Success) {
    std::string apiKey = "01a910b1b73645568da095ec46a05080";
    std::string city = "Paris";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/current?city=" + city + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitCurrent, NonExistentCity) {
    std::string apiKey = "01a910b1b73645568da095ec46a05080";
    std::string nonExistentCity = "NonExistentCity";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/current?city=" + nonExistentCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 400);

    std::cout << "Response Status: " << response->status << std::endl;
    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitCurrent, SpecialCharacters) {
    std::string apiKey = "01a910b1b73645568da095ec46a05080";
    std::string specialCharacterCity = "Cañon";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/current?city=" + specialCharacterCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitCurrent, Lowercase) {
    std::string apiKey = "01a910b1b73645568da095ec46a05080";
    std::string lowercaseCity = "amiens";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/current?city=" + lowercaseCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitCurrent, Uppercase) {
    std::string apiKey = "01a910b1b73645568da095ec46a05080";
    std::string uppercaseCity = "BRUXELLES";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/current?city=" + uppercaseCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

// Weatherbit forecast

TEST(GetWeatherBitForecast, Success) {
    std::string apiKey = "01a910b1b73645568da095ec46a05080";
    std::string city = "Paris";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/forecast/daily?city=" + city + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitForecast, NonExistentCity) {
    std::string apiKey = "01a910b1b73645568da095ec46a05080";
    std::string nonExistentCity = "NonExistentCity";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/forecast/daily?city=" + nonExistentCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 204);

    std::cout << "Response Status: " << response->status << std::endl;
    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitForecast, SpecialCharacters) {
    std::string apiKey = "01a910b1b73645568da095ec46a05080";
    std::string specialCharacterCity = "Cañon";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/forecast/daily?city=" + specialCharacterCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitForecast, Lowercase) {
    std::string apiKey = "01a910b1b73645568da095ec46a05080";
    std::string lowercaseCity = "amiens";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/forecast/daily?city=" + lowercaseCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitForecast, Uppercase) {
    std::string apiKey = "01a910b1b73645568da095ec46a05080";
    std::string uppercaseCity = "BRUXELLES";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/forecast/daily?city=" + uppercaseCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

// Global tests
// TEST(GetCurrentWeather, Success) {
//     std::string apiKey = "01a910b1b73645568da095ec46a05080";
//     std::string city = "Lyon";
//     httplib::Client client("api.weatherbit.io");
//     auto response = client.Get(
//         "/v2.0/current?city=" + city + "&key=" + apiKey);
//     ASSERT_TRUE(response);
//     ASSERT_EQ(response->status, 200);
//     std::cout << response->body << std::endl;
// }

// TEST(GetCurrentWeather, NonExistentCity) {
//     std::string apiKey = "01a910b1b73645568da095ec46a05080";
//     std::string nonExistentCity = "NonExistentCity";
//     httplib::Client client("api.weatherbit.io");
//     auto response = client.Get(
//         "/v2.0/current?city=" + nonExistentCity + "&key=" + apiKey);
//     // Print the response status
//     std::cout << "Response Status: " << response->status << std::endl;
    
//     // Print the response body
//     std::cout << "Response Body: " << response->body << std::endl;
    
//     ASSERT_TRUE(response);
//     ASSERT_EQ(response->status, 400);
// }

// TEST(GetForecast, Success) {
//     std::string apiKey = "01a910b1b73645568da095ec46a05080";
//     std::string city = "Lyon";
//     httplib::Client client("api.weatherbit.io");
//     auto response = client.Get(
//         "/v2.0/forecast/daily?city=" + city + "&key=" + apiKey);
//     ASSERT_TRUE(response);
//     ASSERT_EQ(response->status, 200);
//     std::cout << response->body << std::endl;
// }
TEST(GetForecast, Success) {
    std::string apiKey = "01a910b1b73645568da095ec46a05080";
    std::string city = "Lyon";

    httplib::Request req;
    req.path = "/weather/forecast?location=Lyon";

    httplib::Response res;

    weather::GetForecast(req, res);

    EXPECT_EQ(res.status, 200);
    EXPECT_FALSE(res.body.empty());

    std::cout << "Response Body: " << res.body << std::endl;
}
