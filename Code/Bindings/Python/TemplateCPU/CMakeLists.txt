#   Template SDK, by-EAjks.Com FPGA/C++ Development Best Practices
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

FILE(GLOB_RECURSE TemplateCPUPythonBindingHeaders ${PROJECT_SOURCE_DIR}/include/*.h)
FILE(GLOB_RECURSE TemplateCPUPythonBindingSources ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Let's define the Python binding of the C++ shared library.

PYBIND11_ADD_MODULE(
    TemplateCPUPythonBinding
        MODULE
            ${TemplateCPUPythonBindingHeaders}
            ${TemplateCPUPythonBindingSources})

TARGET_COMPILE_DEFINITIONS(
    TemplateCPUPythonBinding
        PRIVATE $<$<CONFIG:Debug>:SPDLOG_DEBUG_ON>
        PRIVATE SPDLOG_TRACE_ON)

TARGET_COMPILE_OPTIONS(
    TemplateCPUPythonBinding
        PRIVATE $<$<AND:$<CXX_COMPILER_ID:IntelLLVM>,$<COMPILE_LANGUAGE:CXX>>:-Wno-tautological-constant-compare>)

TARGET_LINK_LIBRARIES(
    TemplateCPUPythonBinding
        PRIVATE pybind11::headers
        PRIVATE spdlog::spdlog_header_only
        PRIVATE TemplateCPUSharedLibrary)

SET_TARGET_PROPERTIES(
    TemplateCPUPythonBinding
        PROPERTIES
            INTERPROCEDURAL_OPTIMIZATION ON
            CXX_VISIBILITY_PRESET default
            VISIBILITY_INLINES_HIDDEN ON
            OUTPUT_NAME ${PROJECT_NAME})

# Let's define where the python binding is installed.

INSTALL(
    TARGETS
        TemplateCPUPythonBinding
    LIBRARY
        DESTINATION bindings/python/${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}
        COMPONENT runtime
    RUNTIME
        DESTINATION bindings/python/${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}
        COMPONENT runtime)
