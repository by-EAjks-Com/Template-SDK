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

// Dependency Headers

// Additional Template-SDK Headers
#include "byEAjksCom/Libraries/Template/CPU/PreprocessorMacros.h"

namespace byEAjksCom::Libraries::Template::CPU {

/// @brief This interface exposes methods and properties to ...
class TEMPLATE_CPU_DLL_EXPORT ObjectIF
{
public:

    /// @brief Constructs a new instance of the ObjectIF interface.
    explicit
    ObjectIF()
    = default;

    /// Avoids implicit generation of the copy constructor.
    explicit
    ObjectIF(
        const ObjectIF & other)
    = delete;

    /// Avoids implicit generation of the move constructor.
    explicit
    ObjectIF(
        ObjectIF && other)
    noexcept = delete;

    /// @brief Destructs the instance of the ObjectIF interface.
    virtual
    ~ObjectIF()
    noexcept
    {
    }

    /// Avoids implicit generation of the copy assignment.
    auto
    operator=(
        const ObjectIF & other)
    -> ObjectIF & = delete;

    /// Avoids implicit generation of the move assignment.
    auto
    operator=(
        ObjectIF && other)
    noexcept -> ObjectIF & = delete;

    /// @brief Runs.
    virtual
    auto
    Run()
    -> void = 0;
};

} // byEAjksCom::Libraries::Template::CPU
