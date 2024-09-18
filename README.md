# weather-cpp
A weather app to help you get a quick insight of the weather around you

## Run the app

docker compose build
docker compose up

### How to call the API

`curl "http://localhost:8080/weather/current?location=Lyon"`
`curl "http://localhost:8080/weather/forecast?location=Lyon"`

## Run the tests

`cd test`
`cmake -S . -B build`
`cmake --build build`
`cd build && ctest`

