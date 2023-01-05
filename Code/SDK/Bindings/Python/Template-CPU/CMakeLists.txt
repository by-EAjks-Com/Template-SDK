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

PROJECT(TemplateCPUBindingForPython VERSION ${TemplateSDK_VERSION} LANGUAGES CXX)

FILE(GLOB_RECURSE TemplateCPUBindingForPythonHeaders ${PROJECT_SOURCE_DIR}/include/*.h)
FILE(GLOB_RECURSE TemplateCPUBindingForPythonSources ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Let's define the Python binding of the C++ shared library.

PYTHON_ADD_LIBRARY(
    TemplateCPUBindingForPython
        MODULE
            ${TemplateCPUBindingForPythonHeaders}
            ${TemplateCPUBindingForPythonSources})

TARGET_COMPILE_DEFINITIONS(
    TemplateCPUBindingForPython
        PRIVATE $<$<CONFIG:Debug>:SPDLOG_DEBUG_ON>
        PRIVATE SPDLOG_TRACE_ON)

TARGET_LINK_LIBRARIES(
    TemplateCPUBindingForPython
        PRIVATE pybind11::headers
        PRIVATE spdlog::spdlog_header_only
        PRIVATE SharedTemplateCPULibrary)

SET_TARGET_PROPERTIES(
    TemplateCPUBindingForPython
        PROPERTIES
            INTERPROCEDURAL_OPTIMIZATION ON
            CXX_VISIBILITY_PRESET default
            VISIBILITY_INLINES_HIDDEN ON)

# Let's define where the python binding is installed.

INSTALL(
    TARGETS TemplateCPUBindingForPython
    LIBRARY
        DESTINATION bindings/python/${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}
        COMPONENT runtime
    RUNTIME
        DESTINATION bindings/python/${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}
        COMPONENT runtime)
