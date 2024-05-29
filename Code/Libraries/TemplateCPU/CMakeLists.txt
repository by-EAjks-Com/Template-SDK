#   Template-SDK, by-EAjks.Com FPGA/C++ Development Best Practices
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

PROJECT(TemplateCPU VERSION ${TemplateSDK_VERSION} LANGUAGES CXX)

CONFIGURE_FILE(
    ${PROJECT_SOURCE_DIR}/include-api/byEAjksCom/Libraries/Template/CPU/Version.h.in
    ${PROJECT_BINARY_DIR}/include-api/byEAjksCom/Libraries/Template/CPU/Version.h
    @ONLY)

FILE(GLOB_RECURSE TemplateCPULibraryHeaders ${PROJECT_SOURCE_DIR}/include-api/byEAjksCom/Libraries/Template/CPU/*.h ${PROJECT_SOURCE_DIR}/include/byEAjksCom/Libraries/Template/CPU/*.h)
FILE(GLOB_RECURSE TemplateCPULibrarySources ${PROJECT_SOURCE_DIR}/src/byEAjksCom/Libraries/TemplateCPU.cpp ${PROJECT_SOURCE_DIR}/src/byEAjksCom/Libraries/Template/CPU/*.cpp)

# Let's define the static version of the library.

ADD_LIBRARY(
    TemplateCPUStaticLibrary
        STATIC
            ${TemplateCPULibraryHeaders}
            ${TemplateCPULibrarySources})

TARGET_INCLUDE_DIRECTORIES(
    TemplateCPUStaticLibrary
        INTERFACE $<INSTALL_INTERFACE:include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        PRIVATE   $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

TARGET_COMPILE_DEFINITIONS(
    TemplateCPUStaticLibrary
        PUBLIC    TEMPLATE_CPU_LIBRARY_IS_STATIC
        PRIVATE   COMPILING_TEMPLATE_CPU_LIBRARY
        PRIVATE   $<$<CONFIG:Debug>:SPDLOG_DEBUG_ON>
        PRIVATE   SPDLOG_TRACE_ON)

TARGET_COMPILE_OPTIONS(
    TemplateCPUStaticLibrary
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CUDA>>:-Wno-deprecated-gpu-targets>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CUDA>>:-Xcompiler=-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:IntelLLVM>,$<COMPILE_LANGUAGE:CXX>>:-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:IntelLLVM>,$<COMPILE_LANGUAGE:CXX>>:-Wno-tautological-constant-compare>)

TARGET_LINK_LIBRARIES(
    TemplateCPUStaticLibrary
        PRIVATE   $<$<CXX_COMPILER_ID:GNU>:pthread>
        PRIVATE   spdlog::spdlog_header_only)

SET_TARGET_PROPERTIES(
    TemplateCPUStaticLibrary
        PROPERTIES
            OUTPUT_NAME ${PROJECT_NAME})

# Let's define the shared version of the library.

ADD_LIBRARY(
    TemplateCPUSharedLibrary
        SHARED
            ${TemplateCPULibraryHeaders}
            ${TemplateCPULibrarySources})

TARGET_INCLUDE_DIRECTORIES(
    TemplateCPUSharedLibrary
        INTERFACE $<INSTALL_INTERFACE:include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        PRIVATE   $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

TARGET_COMPILE_DEFINITIONS(
    TemplateCPUSharedLibrary
        PUBLIC    TEMPLATE_CPU_LIBRARY_IS_SHARED
        PRIVATE   COMPILING_TEMPLATE_CPU_LIBRARY
        PRIVATE   $<$<CONFIG:Debug>:SPDLOG_DEBUG_ON>
        PRIVATE   SPDLOG_TRACE_ON)

TARGET_COMPILE_OPTIONS(
    TemplateCPUSharedLibrary
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CUDA>>:-Wno-deprecated-gpu-targets>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CUDA>>:-Xcompiler=-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:IntelLLVM>,$<COMPILE_LANGUAGE:CXX>>:-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:IntelLLVM>,$<COMPILE_LANGUAGE:CXX>>:-Wno-tautological-constant-compare>)

TARGET_LINK_LIBRARIES(
    TemplateCPUSharedLibrary
        PRIVATE   $<$<CXX_COMPILER_ID:GNU>:pthread>
        PRIVATE   spdlog::spdlog_header_only)

SET_TARGET_PROPERTIES(
    TemplateCPUSharedLibrary
        PROPERTIES
            OUTPUT_NAME ${PROJECT_NAME}
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR})

# Let's define where the C++ headers,
# and the static/shared libraries are installed.

INSTALL(
    FILES ${PROJECT_BINARY_DIR}/include-api/byEAjksCom/Libraries/Template/CPU/Version.h
    DESTINATION include/byEAjksCom/Libraries/Template/CPU
    COMPONENT sdk)

INSTALL(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include-api/byEAjksCom/Libraries/Template/CPU
    DESTINATION include/byEAjksCom/Libraries
    COMPONENT sdk
    FILES_MATCHING
    PATTERN *.h)

INSTALL(
    TARGETS
        TemplateCPUStaticLibrary
        TemplateCPUSharedLibrary
    ARCHIVE
        DESTINATION lib/static
        COMPONENT sdk
    LIBRARY
        DESTINATION lib/shared
        COMPONENT runtime
    RUNTIME
        DESTINATION bin
        COMPONENT runtime)

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")

    # Let's generate the API documentation of the library,
    # and define where the generated API documentation is installed.

    FIND_PACKAGE(Doxygen REQUIRED)

    CONFIGURE_FILE(
        ${PROJECT_SOURCE_DIR}/doc/api/Doxyfile.in
        ${PROJECT_BINARY_DIR}/doc/api/Doxyfile
        @ONLY)

    ADD_CUSTOM_COMMAND(
        COMMENT "Creating HTML documentation"
        DEPENDS ${PROJECT_SOURCE_DIR}/doc/api/Doxyfile.in
                ${TemplateCPULibraryHeaders}
                ${TemplateCPULibrarySources}
        OUTPUT  ${PROJECT_BINARY_DIR}/doc/api/html/index.html
        COMMAND ${DOXYGEN_EXECUTABLE} ARGS ${PROJECT_BINARY_DIR}/doc/api/Doxyfile
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc/api)

    ADD_CUSTOM_TARGET(
        TemplateCPUApiDocumentation ALL
            DEPENDS ${PROJECT_BINARY_DIR}/doc/api/html/index.html
            VERBATIM)

    INSTALL(
        DIRECTORY ${PROJECT_BINARY_DIR}/doc/api/html
        DESTINATION doc/api/byEAjksCom/Libraries/Template/CPU
        COMPONENT sdk)

ENDIF()
