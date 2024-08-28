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

// Additional Template-SDK Headers
#include "byEAjksCom/Libraries/Template/CPU/PrecompiledHeaders.h"
#include "byEAjksCom/Libraries/Template/CPU/PreprocessorMacros.h"
#include "byEAjksCom/Libraries/Template/CPU/ObjectIF.h"

// Dependency Headers

// Standard C++/STL Headers
#include <memory>

// Standard C-->C++ Headers
#include <cmath>
#include <cstdint>

namespace byEAjksCom::Libraries::Template::CPU {

/// @brief This interface exposes methods and properties to ...
class TEMPLATE_CPU_DLL_EXPORT ObjectFactoryIF
{
public:

    /// @brief Constructs a new instance of the ObjectFactoryIF interface.
    explicit
    ObjectFactoryIF()
    noexcept;

    /// Avoids implicit generation of the copy constructor.
    explicit
    ObjectFactoryIF(
        const ObjectFactoryIF & other)
    noexcept = delete;

    /// Avoids implicit generation of the move constructor.
    explicit
    ObjectFactoryIF(
        ObjectFactoryIF && other)
    noexcept = delete;

    /// @brief Destructs the instance of the ObjectFactoryIF interface.
    virtual
    ~ObjectFactoryIF()
    noexcept;

    /// Avoids implicit generation of the copy assignment.
    auto
    operator=(
        const ObjectFactoryIF & other)
    noexcept -> ObjectFactoryIF & = delete;

    /// Avoids implicit generation of the move assignment.
    auto
    operator=(
        ObjectFactoryIF && other)
    noexcept -> ObjectFactoryIF & = delete;

    /// @brief Creates an instance.
    /// @return An instance.
    virtual
    auto
    CreateInstance()
    noexcept -> ::std::unique_ptr<ObjectIF> = 0;
};

} // byEAjksCom::Libraries::Template::CPU
