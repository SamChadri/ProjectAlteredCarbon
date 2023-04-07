FROM ubuntu:bionic

WORKDIR /usr/src/app

RUN apt-get update -y &&\
    apt-get install build-essential -y

COPY . .


CMD ["/bin/bash"]




