//  Template SDK, by-EAjks.Com FPGA/C++ Development Best Practices
//  Copyright (C) 2022-2023 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
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

// Additional Template-GPU Headers
#include "byEAjksCom/Libraries/Template/GPU/PreprocessorMacros.h"
#include "byEAjksCom/Libraries/Template/GPU/IObject.h"

namespace byEAjksCom {
namespace Libraries {
namespace Template {
namespace GPU {

//! \brief This interface exposes methods and properties to ...
class TEMPLATE_GPU_DLL_EXPORT IObjectFactory
{
public:

    //! \brief Constructs a new instance of the IObjectFactory interface.
    explicit
    IObjectFactory()
    = default;

    //! Avoids implicit generation of the copy constructor.
    explicit
    IObjectFactory(
        const IObjectFactory & other)
    = delete;

    //! Avoids implicit generation of the move constructor.
    explicit
    IObjectFactory(
        IObjectFactory && other)
    = delete;

    //! \brief Destructs the instance of the IObjectFactory interface.
    virtual
    ~IObjectFactory()
    {
    }

    //! Avoids implicit generation of the copy assignment.
    IObjectFactory &
    operator=(
        const IObjectFactory & other)
    = delete;

    //! Avoids implicit generation of the move assignment.
    IObjectFactory &
    operator=(
        IObjectFactory && other)
    = delete;

    //! \brief Creates an instance.
    //! \return An instance.
    virtual
    ::std::unique_ptr<IObject>
    CreateInstance()
    = 0;
};

} // ::GPU
} // ::Template
} // ::Libraries
} // ::byEAjksCom
