# weather-cpp
A weather app to help you get a quick insight of the weather around you

## Get the API Key

Create an account and get an API key from [weatherbit](https://www.weatherbit.io/).

Fill in the .env file using the .env.template file.

## Install dependencies

- [json](https://github.com/nlohmann/json?tab=readme-ov-file)
- [httplib](https://github.com/yhirose/cpp-httplib/tree/master)
- [googletest](https://github.com/google/googletest/tree/main)

## Run the app

```
docker compose build
docker compose up
```

### How to call the API

here are examples of how to call to the API:
`curl "http://localhost:8080/weather/current?location=Lyon"`

`curl "http://localhost:8080/weather/forecast?location=Lyon"`

## Run the tests

```
cd test
cmake -S . -B build
cmake --build build
cd build && ctest
```

