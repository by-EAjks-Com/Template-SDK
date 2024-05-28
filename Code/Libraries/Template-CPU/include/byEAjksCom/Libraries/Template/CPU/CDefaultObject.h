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
#include "byEAjksCom/Libraries/Template/CPU/CObjectBase.h"

namespace byEAjksCom {
namespace Libraries {
namespace Template {
namespace CPU {

//! \brief This class implements ...
class TEMPLATE_CPU_DLL_HIDDEN CDefaultObject final
:   public CObjectBase
{
public:

    //! \brief Constructs a new instance of the CDefaultObject class.
    //! \param[in] logger The SpdLog logger used by the calling function.
    explicit
    CDefaultObject(
        ::std::shared_ptr<::spdlog::logger> logger)
    noexcept
    :   CObjectBase(::std::move(logger))
    {
        this->logger->debug("entering CDefaultObject::CTOR()");
    }

    //! Avoids implicit generation of the copy constructor.
    explicit
    CDefaultObject(
        const CDefaultObject & other)
    = delete;

    //! Avoids implicit generation of the move constructor.
    explicit
    CDefaultObject(
        CDefaultObject && other)
    = delete;

    //! \brief Destructs the instance of the CDefaultObject class.
    virtual
    ~CDefaultObject()
    noexcept
    {
        this->logger->debug("entering CDefaultObject::DTOR()");
    }

    //! Avoids implicit generation of the copy assignment.
    CDefaultObject &
    operator=(
        const CDefaultObject & other)
    = delete;

    //! Avoids implicit generation of the move assignment.
    CDefaultObject &
    operator=(
        CDefaultObject && other)
    = delete;

    //! \brief Runs.
    virtual
    void
    Run()
    override final
    {
        this->logger->debug("entering CDefaultObject::Run()");

        CObjectBase::Run();
    }
};

} // ::CPU
} // ::Template
} // ::Libraries
} // ::byEAjksCom
