FROM ubuntu:22.04

RUN apt update
RUN apt install -y \
    build-essential \
    cmake \
    cppcheck \
    cpplint \
    gdb \
    git \
    googletest \
    googletest-tools \
    lcov \
    libgmock-dev \
    libgtest-dev \
    python3-all

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME
RUN useradd --uid $USER_UID --gid $USER_GID -m $USERNAME

USER $USERNAME
