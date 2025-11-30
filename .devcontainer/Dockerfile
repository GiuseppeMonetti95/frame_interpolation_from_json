FROM ubuntu:jammy

SHELL [ "/bin/bash" , "-c" ]

RUN apt update && apt upgrade -y && apt install -y wget libeigen3-dev build-essential git cmake

RUN wget -O /usr/local/include/json.hpp https://github.com/nlohmann/json/releases/download/v3.12.0/json.hpp --no-check-certificate