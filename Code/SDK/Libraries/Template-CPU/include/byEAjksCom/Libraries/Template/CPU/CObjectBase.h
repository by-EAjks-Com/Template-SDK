//  Template SDK, by-EAjks.Com FPGA/C++ Development Best Practices
//  Copyright (C) 2022 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
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
#include "byEAjksCom/Libraries/Template/CPU/IObject.h"

namespace byEAjksCom {
namespace Libraries {
namespace Template {
namespace CPU {

//! \brief This class implements ...
class TEMPLATE_CPU_DLL_HIDDEN CObjectBase
:   public virtual IObject
{
public:

    //! \brief Constructs a new instance of the CObjectBase class.
    //! \param[in] logger The SpdLog logger used by the calling function.
    explicit
    CObjectBase(
        ::std::shared_ptr<::spdlog::logger> logger)
    noexcept
    :   logger(::std::move(logger))
    {
        this->logger->debug("entering CObjectBase::CTOR()");
    }

    //! Avoids implicit generation of the copy constructor.
    explicit
    CObjectBase(
        const CObjectBase & other)
    = delete;

    //! Avoids implicit generation of the move constructor.
    explicit
    CObjectBase(
        CObjectBase && other)
    = delete;

    //! \brief Destructs the instance of the CObjectBase class.
    virtual
    ~CObjectBase()
    noexcept
    {
        this->logger->debug("entering CObjectBase::DTOR()");

        this->logger = nullptr;
    }

    //! Avoids implicit generation of the copy assignment.
    CObjectBase &
    operator=(
        const CObjectBase & other)
    = delete;

    //! Avoids implicit generation of the move assignment.
    CObjectBase &
    operator=(
        CObjectBase && other)
    = delete;

protected:

    //! \brief Runs.
    virtual
    void
    Run()
    override
    {
        this->logger->debug("entering CObjectBase::Run()");
    }

    ::std::shared_ptr<::spdlog::logger> logger { nullptr };
};

} // ::CPU
} // ::Template
} // ::Libraries
} // ::byEAjksCom
