# Use an official GCC image as the base image
FROM gcc:latest

# Set the working directory
WORKDIR /app

# Copy the source code into the container
COPY . .
COPY .env ./

# Install dependencies
RUN apt-get update && apt-get install -y cmake libcurl4-openssl-dev

# Build the project
RUN mkdir build && cd build && cmake .. && make

# Expose the port the app runs on
EXPOSE 8080

# Command to run the executable
CMD ["./build/weather"]