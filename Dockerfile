FROM ubuntu:24.04

RUN apt update
RUN apt install -y \
    build-essential \
    cmake \
    cppcheck \
    cpplint \
    gdb \
    git \
    googletest \
    lcov \
    libgmock-dev \
    libgtest-dev \
    python3-all
