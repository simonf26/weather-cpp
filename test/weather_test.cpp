#include <gtest/gtest.h>
#include <../include/httplib.h>
#include <iostream>
#include <string>
#include "../include/weather.hpp"

// Fill in the apiKey before testing
// Todo: get the API key from the env file.
const std::string apiKey="";

// Testing weatherbit current
TEST(GetWeatherBitCurrent, Success) {
    std::string city = "Paris";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/current?city=" + city + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitCurrent, NonExistentCity) {
    std::string nonExistentCity = "NonExistentCity";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/current?city=" + nonExistentCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 400);

    std::cout << "Response Status: " << response->status << std::endl;
    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitCurrent, SpecialCharacters) {
    std::string specialCharacterCity = "Cañon";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/current?city=" + specialCharacterCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitCurrent, Lowercase) {
    std::string lowercaseCity = "amiens";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/current?city=" + lowercaseCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitCurrent, Uppercase) {
    std::string uppercaseCity = "BRUXELLES";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/current?city=" + uppercaseCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

// Weatherbit forecast

TEST(GetWeatherBitForecast, Success) {
    std::string city = "Paris";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/forecast/daily?city=" + city + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitForecast, NonExistentCity) {
    std::string nonExistentCity = "NonExistentCity";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/forecast/daily?city=" + nonExistentCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 204);

    std::cout << "Response Status: " << response->status << std::endl;
    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitForecast, SpecialCharacters) {
    std::string specialCharacterCity = "Cañon";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/forecast/daily?city=" + specialCharacterCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitForecast, Lowercase) {
    std::string lowercaseCity = "amiens";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/forecast/daily?city=" + lowercaseCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

TEST(GetWeatherBitForecast, Uppercase) {
    std::string uppercaseCity = "BRUXELLES";

    httplib::Client client("api.weatherbit.io");
    
    auto response = client.Get("/v2.0/forecast/daily?city=" + uppercaseCity + "&key=" + apiKey);

    ASSERT_TRUE(response);
    ASSERT_EQ(response->status, 200);

    std::cout << "Response Body: " << response->body << std::endl;
}

// Test global API

TEST(GetCurrentWeather, Success) {
    std::string city = "Lyon";

    // Set environment variable
    std::string envVarName = "WEATHERBIT_API_KEY";
    std::string envVarValue = apiKey;
    
    // Create a mutable copy of the environment variable string
    char* envVarString = new char[envVarName.size() + envVarValue.size() + 2];
    strcpy(envVarString, envVarName.c_str());
    strcat(envVarString, "=");
    strcat(envVarString, envVarValue.c_str());

    int result = putenv(envVarString); // Use global namespace putenv
    ASSERT_EQ(result, 0); // Check if setting the env var was successful

    httplib::Request req;
    req.path = "/weather/forecast";
    httplib::Params params{
        { "location", city }
    };
    req.params = params;

    httplib::Response res;

    weather::GetCurrentWeather(req, res);

    EXPECT_EQ(res.status, 200);
    EXPECT_FALSE(res.body.empty());

    std::cout << "Response Body: " << res.body << std::endl;
}

TEST(GetCurrentWeather, NonExistentCity) {
    std::string city = "NonExistentCity";

    // Set environment variable
    std::string envVarName = "WEATHERBIT_API_KEY";
    std::string envVarValue = apiKey;
    
    // Create a mutable copy of the environment variable string
    char* envVarString = new char[envVarName.size() + envVarValue.size() + 2];
    strcpy(envVarString, envVarName.c_str());
    strcat(envVarString, "=");
    strcat(envVarString, envVarValue.c_str());

    int result = putenv(envVarString); // Use global namespace putenv
    ASSERT_EQ(result, 0); // Check if setting the env var was successful

    httplib::Request req;
    req.path = "/weather/forecast";
    httplib::Params params{
        { "location", city }
    };
    req.params = params;

    httplib::Response res;

    weather::GetCurrentWeather(req, res);

    EXPECT_EQ(res.status, 404);
    EXPECT_FALSE(res.body.empty());

    std::cout << "Response Body: " << res.body << std::endl;
}

TEST(GetForecast, Success) {
    std::string city = "Lyon";

    // Set environment variable
    std::string envVarName = "WEATHERBIT_API_KEY";
    std::string envVarValue = apiKey;
    
    // Create a mutable copy of the environment variable string
    char* envVarString = new char[envVarName.size() + envVarValue.size() + 2];
    strcpy(envVarString, envVarName.c_str());
    strcat(envVarString, "=");
    strcat(envVarString, envVarValue.c_str());

    int result = putenv(envVarString); // Use global namespace putenv
    ASSERT_EQ(result, 0); // Check if setting the env var was successful

    httplib::Request req;
    req.path = "/weather/forecast";
    httplib::Params params{
        { "location", city }
    };
    req.params = params;

    httplib::Response res;

    weather::GetForecast(req, res);

    EXPECT_EQ(res.status, 200);
    EXPECT_FALSE(res.body.empty());

    std::cout << "Response Body: " << res.body << std::endl;
}
