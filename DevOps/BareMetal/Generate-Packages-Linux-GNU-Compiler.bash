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

rm    -rf Generate-Packages-Linux-GNU-Compiler
mkdir -p  Generate-Packages-Linux-GNU-Compiler
pushd     Generate-Packages-Linux-GNU-Compiler

. /opt/intel/oneapi/setvars.sh

cmake \
    -G "Unix Makefiles" \
    -D CMAKE_C_COMPILER=gcc \
    -D CMAKE_CXX_COMPILER=g++ \
    -D CMAKE_BUILD_TYPE=Debug \
    -D PYBIND11_FINDPYTHON=ON \
    ../../../Code

make package

popd
