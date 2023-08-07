FROM ubuntu:latest
RUN mkdir /app
COPY . /app
WORKDIR /app
RUN apt update && \
    apt install -y clang gdb cmake valgrind
RUN mkdir build
WORKDIR /app/build
RUN cmake .. && \
    cmake --build .
WORKDIR /app
