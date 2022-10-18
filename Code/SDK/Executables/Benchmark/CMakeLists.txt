#   Template SDK, by-EAjks.Com FPGA/C++ Development Best Practices
#   Copyright (C) 2022 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
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

PROJECT(Benchmark VERSION ${TemplateSDK_VERSION} LANGUAGES CXX)

CONFIGURE_FILE(
    ${PROJECT_SOURCE_DIR}/src/Version.h.in
    ${PROJECT_BINARY_DIR}/src/Version.h
    @ONLY)

FILE(GLOB_RECURSE BenchmarkHeaders ${PROJECT_SOURCE_DIR}/src/*.h)
FILE(GLOB_RECURSE BenchmarkSources ${PROJECT_SOURCE_DIR}/src/*.cpp)

ADD_EXECUTABLE(
    Benchmark
        ${BenchmarkHeaders}
        ${BenchmarkSources})

TARGET_INCLUDE_DIRECTORIES(
    Benchmark
        PRIVATE ${PROJECT_BINARY_DIR}/src
        PRIVATE ${PROJECT_SOURCE_DIR}/src)

TARGET_LINK_LIBRARIES(
    Benchmark
        PRIVATE CLI11::CLI11
        PRIVATE spdlog::spdlog_header_only
        PRIVATE StaticTemplateCPULibrary
        PRIVATE StaticTemplateGPULibrary)

SET_TARGET_PROPERTIES(
    Benchmark
        PROPERTIES
            OUTPUT_NAME "Benchmark")

INSTALL(
    TARGETS Benchmark
    RUNTIME
        DESTINATION bin
        COMPONENT runtime)
