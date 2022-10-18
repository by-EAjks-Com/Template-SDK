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

PROJECT(TemplateGPULibrary VERSION ${TemplateSDK_VERSION} LANGUAGES CXX CUDA)

CONFIGURE_FILE(
    ${PROJECT_SOURCE_DIR}/include-api/byEAjksCom/Libraries/Template/GPU/Version.h.in
    ${PROJECT_BINARY_DIR}/include-api/byEAjksCom/Libraries/Template/GPU/Version.h
    @ONLY)

FILE(GLOB_RECURSE TemplateGPULibraryHeaders ${PROJECT_SOURCE_DIR}/include-api/byEAjksCom/Libraries/Template/GPU/*.h ${PROJECT_SOURCE_DIR}/include/byEAjksCom/Libraries/Template/GPU/*.h)
FILE(GLOB_RECURSE TemplateGPULibrarySources ${PROJECT_SOURCE_DIR}/src/byEAjksCom/Libraries/Template-GPU.cpp ${PROJECT_SOURCE_DIR}/src/byEAjksCom/Libraries/Template/GPU/*.cpp ${PROJECT_SOURCE_DIR}/src/byEAjksCom/Libraries/Template/GPU/*.cu)

# Let's define the static version of the library.

ADD_LIBRARY(
    StaticTemplateGPULibrary
        STATIC
            ${TemplateGPULibraryHeaders}
            ${TemplateGPULibrarySources})

TARGET_INCLUDE_DIRECTORIES(
    StaticTemplateGPULibrary
        INTERFACE $<INSTALL_INTERFACE:include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        PRIVATE   $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

TARGET_COMPILE_DEFINITIONS(
    StaticTemplateGPULibrary
        PUBLIC    TEMPLATE_GPU_LIBRARY_IS_STATIC
        PRIVATE   COMPILING_TEMPLATE_GPU_LIBRARY
        PRIVATE   $<$<CONFIG:Debug>:SPDLOG_DEBUG_ON>
        PRIVATE   SPDLOG_TRACE_ON)

TARGET_COMPILE_OPTIONS(
    StaticTemplateGPULibrary
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CUDA>>:-Xcompiler=-fvisibility=hidden>)

TARGET_LINK_LIBRARIES(
    StaticTemplateGPULibrary
        PRIVATE   $<$<CXX_COMPILER_ID:GNU>:pthread>
        PRIVATE   spdlog::spdlog_header_only)

SET_TARGET_PROPERTIES(
    StaticTemplateGPULibrary
        PROPERTIES
            CUDA_RUNTIME_LIBRARY STATIC
            CUDA_SEPARABLE_COMPILATION ON
            POSITION_INDEPENDENT_CODE ON
            OUTPUT_NAME "Template-GPU")

# Let's define the shared version of the library.

ADD_LIBRARY(
    SharedTemplateGPULibrary
        SHARED
            ${TemplateGPULibraryHeaders}
            ${TemplateGPULibrarySources})

TARGET_INCLUDE_DIRECTORIES(
    SharedTemplateGPULibrary
        INTERFACE $<INSTALL_INTERFACE:include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        PRIVATE   $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

TARGET_COMPILE_DEFINITIONS(
    SharedTemplateGPULibrary
        PUBLIC    TEMPLATE_GPU_LIBRARY_IS_SHARED
        PRIVATE   COMPILING_TEMPLATE_GPU_LIBRARY
        PRIVATE   $<$<CONFIG:Debug>:SPDLOG_DEBUG_ON>
        PRIVATE   SPDLOG_TRACE_ON)

TARGET_COMPILE_OPTIONS(
    SharedTemplateGPULibrary
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CUDA>>:-Xcompiler=-fvisibility=hidden>)

TARGET_LINK_LIBRARIES(
    SharedTemplateGPULibrary
        PRIVATE   $<$<CXX_COMPILER_ID:GNU>:pthread>
        PRIVATE   spdlog::spdlog_header_only)

SET_TARGET_PROPERTIES(
    SharedTemplateGPULibrary
        PROPERTIES
            CUDA_RUNTIME_LIBRARY SHARED
            CUDA_SEPARABLE_COMPILATION ON
            POSITION_INDEPENDENT_CODE ON
            OUTPUT_NAME "Template-GPU"
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR})

# Let's define where the C++ headers,
# and the static/shared libraries are installed.

INSTALL(
    FILES ${PROJECT_BINARY_DIR}/include-api/byEAjksCom/Libraries/Template/GPU/Version.h
    DESTINATION include/byEAjksCom/Libraries/Template/GPU
    COMPONENT sdk)

INSTALL(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include-api/byEAjksCom/Libraries/Template/GPU
    DESTINATION include/byEAjksCom/Libraries
    COMPONENT sdk
    FILES_MATCHING
    PATTERN "*.h")

INSTALL(
    TARGETS StaticTemplateGPULibrary
            SharedTemplateGPULibrary
    ARCHIVE
        DESTINATION lib/static
        COMPONENT sdk
    LIBRARY
        DESTINATION lib/shared
        COMPONENT runtime
    RUNTIME
        DESTINATION lib/shared
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
                ${TemplateGPULibraryHeaders}
                ${TemplateGPULibrarySources}
        OUTPUT  ${PROJECT_BINARY_DIR}/doc/api/html/index.html
        COMMAND ${DOXYGEN_EXECUTABLE} ARGS ${PROJECT_BINARY_DIR}/doc/api/Doxyfile
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc/api)

    ADD_CUSTOM_TARGET(
        TemplateGPUApiDocumentation ALL
            DEPENDS ${PROJECT_BINARY_DIR}/doc/api/html/index.html
            VERBATIM)

    INSTALL(
        DIRECTORY ${PROJECT_BINARY_DIR}/doc/api/html
        DESTINATION doc/api/byEAjksCom/Libraries/Template/GPU
        COMPONENT sdk)

ENDIF()
