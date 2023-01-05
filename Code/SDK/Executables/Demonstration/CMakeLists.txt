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

PROJECT(Demonstration VERSION ${TemplateSDK_VERSION} LANGUAGES CXX)

CONFIGURE_FILE(
    ${PROJECT_SOURCE_DIR}/src/Version.h.in
    ${PROJECT_BINARY_DIR}/src/Version.h
    @ONLY)

FILE(GLOB_RECURSE DemonstrationHeaders ${PROJECT_SOURCE_DIR}/src/*.h)
FILE(GLOB_RECURSE DemonstrationSources ${PROJECT_SOURCE_DIR}/src/*.cpp)

ADD_EXECUTABLE(
    Demonstration
        ${DemonstrationHeaders}
        ${DemonstrationSources})

TARGET_INCLUDE_DIRECTORIES(
    Demonstration
        PRIVATE ${PROJECT_BINARY_DIR}/src
        PRIVATE ${PROJECT_SOURCE_DIR}/src)

TARGET_LINK_LIBRARIES(
    Demonstration
        PRIVATE CLI11::CLI11
        PRIVATE spdlog::spdlog_header_only
        PRIVATE SharedTemplateCPULibrary
        PRIVATE SharedTemplateGPULibrary)

SET_TARGET_PROPERTIES(
    Demonstration
        PROPERTIES
            OUTPUT_NAME "Demonstration")

IF(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    ADD_CUSTOM_COMMAND(
        TARGET Demonstration
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Demonstration> $<TARGET_FILE_DIR:Demonstration>
        COMMAND_EXPAND_LISTS)
ENDIF()

INSTALL(
    TARGETS Demonstration
    RUNTIME
        DESTINATION bin
        COMPONENT runtime)
