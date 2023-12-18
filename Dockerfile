FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    libzmq3-dev \
    git \
    cmake

# Установка cppzmq
RUN git clone https://github.com/zeromq/cppzmq.git && \
    cd cppzmq && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make install

WORKDIR /app

COPY . .

RUN make