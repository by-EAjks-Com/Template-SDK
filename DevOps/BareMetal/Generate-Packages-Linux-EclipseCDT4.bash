#!/bin/bash
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

rm    -rf Generate-Packages-Linux-EclipseCDT4
mkdir -p  Generate-Packages-Linux-EclipseCDT4
pushd     Generate-Packages-Linux-EclipseCDT4

cmake \
    -G "Eclipse CDT4 - Unix Makefiles" \
    -D CMAKE_ECLIPSE_VERSION=4.24 \
    -D CMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
    -D CMAKE_C_COMPILER=gcc \
    -D CMAKE_CXX_COMPILER=g++ \
    -D CMAKE_BUILD_TYPE=Debug \
    -D PYBIND11_FINDPYTHON=ON \
    -D EAJKS_BUILD_FDK=OFF \
    -D EAJKS_BUILD_SDK=ON \
    ../../../Code

make package

popd
