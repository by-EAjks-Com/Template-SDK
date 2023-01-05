#   Template SDK, by-EAjks.Com FPGA/C++ Development Best Practices
#   Copyright (C) 2022-2023 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
