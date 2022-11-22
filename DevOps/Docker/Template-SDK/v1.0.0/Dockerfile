#   Copyright (C) 2020-2022 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
#   See the file "LICENSE" for the full license governing this code.

ARG IMAGE_REPOSITORY
ARG DEVELOPMENT_IMAGE_NAME
ARG DEVELOPMENT_IMAGE_TAG
ARG RUNTIME_IMAGE_NAME
ARG RUNTIME_IMAGE_TAG

FROM ${IMAGE_REPOSITORY}/${DEVELOPMENT_IMAGE_NAME}:${DEVELOPMENT_IMAGE_TAG} AS build

LABEL maintainer "Andrea and Eric DELAGE <Contact@by-EAjks.Com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Paris

RUN apt-get update && \
    apt-get upgrade --yes && \
    apt-get install --yes --no-install-recommends \
        cmake \
        doxygen \
        graphviz \
        libpython3.10-dev \
        python3.10 && \
    apt-get autoremove --yes && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /src

COPY ./Code .

WORKDIR /build

RUN cmake \
        -G "Unix Makefiles" \
        -D CMAKE_C_COMPILER=gcc \
        -D CMAKE_CXX_COMPILER=g++ \
        -D CMAKE_BUILD_TYPE=Release \
        -D PYBIND11_FINDPYTHON=ON \
        -D EAJKS_BUILD_FDK=OFF \
        -D EAJKS_BUILD_SDK=ON \
        /src && \
    make package

FROM ${IMAGE_REPOSITORY}/${RUNTIME_IMAGE_NAME}:${RUNTIME_IMAGE_TAG} AS deploy

LABEL maintainer "Andrea and Eric DELAGE <Contact@by-EAjks.Com>"

COPY --from=build /build/*.deb /root

RUN apt-get update && \
    apt-get install --yes --no-install-recommends \
        /root/*.deb && \
    apt-get autoremove --yes && \
    rm -f  /root/*.deb && \
    rm -rf /var/lib/apt/lists/*

ENV PATH /opt/by-EAjks.Com/TemplateSDK/bin${PATH:+:${PATH}}
ENV LD_LIBRARY_PATH /opt/by-EAjks.Com/TemplateSDK/lib/shared${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
