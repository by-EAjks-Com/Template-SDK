#!/bin/bash
#   Template-SDK, by-EAjks.Com C++ Development Best Practices
#   Copyright (c) 2022-2024 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
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

rm    -rf GeneratePackagesForLinuxUsingIntelOneApi
mkdir -p  GeneratePackagesForLinuxUsingIntelOneApi
pushd     GeneratePackagesForLinuxUsingIntelOneApi

. /opt/intel/OneApi/setvars.sh

/tools/cmake-3.30.2-linux-x86_64/bin/cmake \
    -G "Ninja" \
    -D CMAKE_C_COMPILER=icx \
    -D CMAKE_C_COMPILER_AR=xiar \
    -D CMAKE_CXX_COMPILER=icpx \
    -D CMAKE_CXX_COMPILER_AR=xiar \
    -D CMAKE_BUILD_TYPE=Release \
    -D PYBIND11_FINDPYTHON=ON \
    -D TEMPLATE_SDK_VERSION=1.2.3 \
    ../../../Code

ninja package

popd
