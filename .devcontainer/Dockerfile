# Use the base devcontainer image
FROM mcr.microsoft.com/devcontainers/base:noble

# Install any necessary dependencies
RUN apt-get update && \
    apt-get install -y software-properties-common && \
    add-apt-repository ppa:zhangsongcui3371/fastfetch && \
    apt-get install -y fastfetch
