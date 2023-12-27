FROM ubuntu:22.04

RUN apt update
RUN apt install -y \
    build-essential \
    cmake \
    gdb \
    git \
    googletest \
    googletest-tools \
    lcov \
    libarmadillo-dev \
    libgmock-dev \
    libgtest-dev \
    python3-all

ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME
RUN useradd --uid $USER_UID --gid $USER_GID -m $USERNAME

USER $USERNAME
