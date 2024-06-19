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

#include "byEAjksCom/Libraries/Template/CPU/ObjectFactory.h"

// Standard C-->C++ Headers
#include <cmath>
#include <cstdint>

// Standard C++/STL Headers
#include <memory>

// Dependency Headers
#include <spdlog/spdlog.h>

// Additional Template-SDK Headers
#include "byEAjksCom/Libraries/Template/CPU/DefaultObject.h"
#include "byEAjksCom/Libraries/Template/CPU/ObjectIF.h"

namespace byEAjksCom::Libraries::Template::CPU {

ObjectFactory::ObjectFactory(
    ::std::shared_ptr<::spdlog::logger> logger)
:   logger { ::std::move(logger) }
{
    this->logger->debug("entering ObjectFactory::CTOR()");
}

ObjectFactory::~ObjectFactory()
noexcept
{
    this->logger->debug("entering ObjectFactory::DTOR()");

    this->logger = nullptr;
}

auto
ObjectFactory::CreateInstance()
-> ::std::unique_ptr<ObjectIF>
{
    this->logger->debug("entering ObjectFactory::CreateInstance()");

    ::std::unique_ptr<DefaultObject>
    instance { ::std::make_unique<DefaultObject>(this->logger) };

    return (instance);
}

} // byEAjksCom::Libraries::Template::CPU
