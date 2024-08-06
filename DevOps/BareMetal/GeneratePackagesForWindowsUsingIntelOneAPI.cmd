@echo off
::  Template-SDK, by-EAjks.Com C++ Development Best Practices
::  Copyright (c) 2022-2024 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
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

rmdir /s/q GeneratePackagesForWindowsUsingIntelOneAPI
mkdir      GeneratePackagesForWindowsUsingIntelOneAPI
pushd      GeneratePackagesForWindowsUsingIntelOneAPI

call "C:\Program Files (x86)\Intel\oneAPI\setvars.bat"
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

C:\Tools\cmake-3.30.0-windows-x86_64\bin\cmake.exe ^
    -G "NMake Makefiles" ^
    -D CMAKE_C_COMPILER=icx ^
    -D CMAKE_CXX_COMPILER=icpx ^
    -D CMAKE_BUILD_TYPE=Release ^
    -D CMAKE_TOOLCHAIN_FILE=C:\Tools\VCPKG\scripts\buildsystems\vcpkg.cmake ^
    -D PYBIND11_FINDPYTHON=ON ^
    ..\..\..\Code

nmake package

popd
