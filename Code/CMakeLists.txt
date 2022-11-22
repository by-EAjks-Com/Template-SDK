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

CMAKE_MINIMUM_REQUIRED(VERSION 3.22.1)

STRING(TIMESTAMP TemplateSDK_VERSION "1.0.0.%s" UTC)

PROJECT(TemplateSDK VERSION ${TemplateSDK_VERSION} LANGUAGES NONE)

IF(NOT DEFINED CMAKE_CXX_STANDARD)
    SET(CMAKE_CXX_STANDARD 20)
    SET(CMAKE_CXX_STANDARD_REQUIRED ON)
    SET(CMAKE_CXX_EXTENSIONS ON)
ENDIF()

IF(NOT DEFINED CMAKE_CUDA_STANDARD)
    SET(CMAKE_CUDA_STANDARD 17)
    SET(CMAKE_CUDA_STANDARD_REQUIRED ON)
    SET(CMAKE_CUDA_EXTENSIONS ON)
    SET(CMAKE_CUDA_ARCHITECTURES 50)
ENDIF()

OPTION(EAJKS_BUILD_FDK "Build the FDK" OFF)
OPTION(EAJKS_BUILD_SDK "Build the SDK" OFF)

IF(${EAJKS_BUILD_FDK})
    ADD_SUBDIRECTORY(FDK)
ENDIF()

IF(${EAJKS_BUILD_SDK})
    ADD_SUBDIRECTORY(SDK)
ENDIF()

INSTALL(
    FILES ${PROJECT_SOURCE_DIR}/AUTHORS.md
          ${PROJECT_SOURCE_DIR}/CHANGELOG.md
          ${PROJECT_SOURCE_DIR}/LICENSE
          ${PROJECT_SOURCE_DIR}/README.md
    DESTINATION .
    COMPONENT runtime)

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_NAME ${PROJECT_NAME})
SET(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SDK Template by EAjks")
SET(CPACK_PACKAGE_VENDOR "by-EAjks.Com")
SET(CPACK_PACKAGE_CONTACT "Andrea and Eric DELAGE <Contact@by-EAjks.Com>")
SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}")

IF(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

    SET(CPACK_PACKAGING_INSTALL_PREFIX "/opt/by-EAjks.Com/${PROJECT_NAME}")

    SET(LINUX_DISTRIBUTION_ID "unknown")

    IF(EXISTS "/etc/os-release")
        FILE(STRINGS "/etc/os-release" LINUX_DISTRIBUTION_ID REGEX "^ID=")
        IF(NOT LINUX_DISTRIBUTION_ID STREQUAL "")
            STRING(REPLACE "ID=" "" LINUX_DISTRIBUTION_ID "${LINUX_DISTRIBUTION_ID}")
            STRING(REPLACE "\""  "" LINUX_DISTRIBUTION_ID "${LINUX_DISTRIBUTION_ID}")
        ENDIF()
    ENDIF()

    MESSAGE("-- The Linux distribution identification is '${LINUX_DISTRIBUTION_ID}'.")

    IF(${LINUX_DISTRIBUTION_ID} MATCHES "debian|ubuntu")
        SET(CPACK_GENERATOR "DEB")
        SET(CPACK_DEB_PACKAGE_ARCHITECTURE "amd64")
        SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libpython3.10")
    ENDIF()

    IF(${LINUX_DISTRIBUTION_ID} MATCHES "centos|redhat")
        SET(CPACK_GENERATOR "RPM")
        SET(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
        SET(CPACK_RPM_PACKAGE_REQUIRES "libpython3.10")
    ENDIF()

    SET(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)

ENDIF()

IF(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

    SET(CPACK_GENERATOR "ZIP")

ENDIF()

INCLUDE(CPack)
