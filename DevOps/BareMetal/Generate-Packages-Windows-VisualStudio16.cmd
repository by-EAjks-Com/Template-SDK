@echo off
::  Template SDK, by-EAjks.Com FPGA/C++ Development Best Practices
::  Copyright (C) 2022 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
::
::  This program is free software: you can redistribute it and/or modify
::  it under the terms of the GNU General Public License as published by
::  the Free Software Foundation, either version 3 of the License, or
::  (at your option) any later version.
::
::  This program is distributed in the hope that it will be useful,
::  but WITHOUT ANY WARRANTY; without even the implied warranty of
::  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
::  GNU General Public License for more details.
::
::  You should have received a copy of the GNU General Public License
::  along with this program.  If not, see <https://www.gnu.org/licenses/>.

rmdir /s/q Generate-Packages-Windows-VisualStudio16
mkdir      Generate-Packages-Windows-VisualStudio16
pushd      Generate-Packages-Windows-VisualStudio16

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

cmake ^
    -G "Visual Studio 17 2022" ^
    -D CMAKE_C_COMPILER=cl ^
    -D CMAKE_CXX_COMPILER=cl ^
    -D CMAKE_BUILD_TYPE=Debug ^
    -D CMAKE_TOOLCHAIN_FILE=C:\Tools\VCPKG\scripts\buildsystems\vcpkg.cmake ^
    -D PYBIND11_FINDPYTHON=ON ^
    -D EAJKS_BUILD_FDK=OFF ^
    -D EAJKS_BUILD_SDK=ON ^
    ..\..\..\Code

msbuild -property:Configuration=Release TemplateSDK.sln

popd
