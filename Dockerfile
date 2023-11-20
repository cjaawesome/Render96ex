FROM ubuntu:22.04 as build

RUN apt-get update && \
    apt-get install -y \
        build-essential \
        git \
        libglew-dev \
        libsdl2-dev \
        python3

RUN mkdir /render96ex
WORKDIR /render96ex
ENV PATH="/render96ex/tools:${PATH}"

CMD echo 'Usage: docker run --rm -v ${PWD}:/render96ex render96ex make VERSION=${VERSION:-us} -j4\n' \
         'See https://github.com/Render96/Render96ex/blob/master/README.md for more information'
