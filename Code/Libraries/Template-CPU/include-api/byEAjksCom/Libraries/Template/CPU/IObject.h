//  Template SDK, by-EAjks.Com FPGA/C++ Development Best Practices
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

// Additional Template-CPU Headers
#include "byEAjksCom/Libraries/Template/CPU/PreprocessorMacros.h"

namespace byEAjksCom {
namespace Libraries {
namespace Template {
namespace CPU {

//! \brief This interface exposes methods and properties to ...
class TEMPLATE_CPU_DLL_EXPORT IObject
{
public:

    //! \brief Constructs a new instance of the IObject interface.
    explicit
    IObject()
    = default;

    //! Avoids implicit generation of the copy constructor.
    explicit
    IObject(
        const IObject & other)
    = delete;

    //! Avoids implicit generation of the move constructor.
    explicit
    IObject(
        IObject && other)
    = delete;

    //! \brief Destructs the instance of the IObject interface.
    virtual
    ~IObject()
    {
    }

    //! Avoids implicit generation of the copy assignment.
    IObject &
    operator=(
        const IObject & other)
    = delete;

    //! Avoids implicit generation of the move assignment.
    IObject &
    operator=(
        IObject && other)
    = delete;

    //! \brief Runs.
    virtual
    void
    Run()
    = 0;
};

} // ::CPU
} // ::Template
} // ::Libraries
} // ::byEAjksCom
