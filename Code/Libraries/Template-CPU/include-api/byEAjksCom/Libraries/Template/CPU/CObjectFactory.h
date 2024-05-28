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
#include <memory>

// Dependency Headers
#include <spdlog/spdlog.h>

// Additional Template-CPU Headers
#include "byEAjksCom/Libraries/Template/CPU/PreprocessorMacros.h"
#include "byEAjksCom/Libraries/Template/CPU/IObjectFactory.h"
#include "byEAjksCom/Libraries/Template/CPU/IObject.h"

namespace byEAjksCom {
namespace Libraries {
namespace Template {
namespace CPU {

//! \brief This class implements ...
class TEMPLATE_CPU_DLL_EXPORT CObjectFactory final
:   public virtual IObjectFactory
{
public:

    //! \brief Constructs a new instance of the CObjectFactory class.
    //! \param[in] logger The SpdLog logger used by the calling function.
    explicit
    CObjectFactory(
        ::std::shared_ptr<::spdlog::logger> logger)
    noexcept;

    //! Avoids implicit generation of the copy constructor.
    explicit
    CObjectFactory(
        const CObjectFactory & other)
    = delete;

    //! Avoids implicit generation of the move constructor.
    explicit
    CObjectFactory(
        CObjectFactory && other)
    = delete;

    //! \brief Destructs the instance of the CObjectFactory class.
    virtual
    ~CObjectFactory()
    noexcept;

    //! Avoids implicit generation of the copy assignment.
    CObjectFactory &
    operator=(
        const CObjectFactory & other)
    = delete;

    //! Avoids implicit generation of the move assignment.
    CObjectFactory &
    operator=(
        CObjectFactory && other)
    = delete;

    //! \brief Creates an instance.
    //! \return An instance.
    virtual
    ::std::unique_ptr<IObject>
    CreateInstance()
    override final;

protected:

    ::std::shared_ptr<::spdlog::logger> logger { nullptr };
};

} // ::CPU
} // ::Template
} // ::Libraries
} // ::byEAjksCom
