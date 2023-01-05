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

#include "byEAjksCom/Libraries/Template/GPU/CObjectFactory.h"

// Standard C-->C++ Headers
#include <cmath>
#include <cstdint>

// Standard C++/STL Headers
#include <memory>

// Dependency Headers
#include <spdlog/spdlog.h>

// Additional Template-GPU Headers
#include "byEAjksCom/Libraries/Template/GPU/CDefaultObject.h"

namespace byEAjksCom {
namespace Libraries {
namespace Template {
namespace GPU {

CObjectFactory::CObjectFactory(
    ::std::shared_ptr<::spdlog::logger> logger)
noexcept
:   logger(::std::move(logger))
{
    this->logger->debug("entering CObjectFactory::CTOR()");
}

CObjectFactory::~CObjectFactory()
noexcept
{
    this->logger->debug("entering CObjectFactory::DTOR()");

    this->logger = nullptr;
}

::std::unique_ptr<IObject>
CObjectFactory::CreateInstance()
{
    this->logger->debug("entering CObjectFactory::CreateInstance()");

    ::std::unique_ptr<CDefaultObject>
    instance = ::std::make_unique<CDefaultObject>(this->logger);

    return (::std::move(instance));
}

} // ::GPU
} // ::Template
} // ::Libraries
} // ::byEAjksCom
