//  Template-SDK, by-EAjks.Com C++ Development Best Practices
//  Copyright (c) 2022-2024 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

// Standard C-->C++ Headers
#include <cmath>
#include <cstdint>

// Standard C++/STL Headers
#include <memory>

// Dependency Headers
#include <spdlog/spdlog.h>

// Additional Template-SDK Headers
#include "byEAjksCom/Libraries/Template/CPU/PreprocessorMacros.h"
#include "byEAjksCom/Libraries/Template/CPU/ObjectIF.h"

namespace byEAjksCom::Libraries::Template::CPU {

/// @brief This class implements ...
class TEMPLATE_CPU_DLL_HIDDEN ObjectBase
:   public virtual ObjectIF
{
public:

    /// @brief Constructs a new instance of the ObjectBase class.
    /// @param[in] logger The SpdLog logger used by the calling function.
    explicit
    ObjectBase(
        ::std::shared_ptr<::spdlog::logger> logger)
    :   logger { ::std::move(logger) }
    {
        this->logger->debug("entering ObjectBase::CTOR()");
    }

    /// Avoids implicit generation of the copy constructor.
    explicit
    ObjectBase(
        const ObjectBase & other)
    = delete;

    /// Avoids implicit generation of the move constructor.
    explicit
    ObjectBase(
        ObjectBase && other)
    noexcept = delete;

    /// @brief Destructs the instance of the ObjectBase class.
    virtual
    ~ObjectBase()
    noexcept
    {
        this->logger->debug("entering ObjectBase::DTOR()");

        this->logger = nullptr;
    }

    /// Avoids implicit generation of the copy assignment.
    auto
    operator=(
        const ObjectBase & other)
    -> ObjectBase & = delete;

    /// Avoids implicit generation of the move assignment.
    auto
    operator=(
        ObjectBase && other)
    noexcept -> ObjectBase & = delete;

protected:

    /// @brief Runs.
    virtual
    auto
    Run()
    -> void override
    {
        this->logger->debug("entering ObjectBase::Run()");
    }

    ::std::shared_ptr<::spdlog::logger> logger { nullptr };
};

} // byEAjksCom::Libraries::Template::CPU
