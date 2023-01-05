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

// Standard C-->C++ Headers
#include <cmath>
#include <cstdint>

// Standard C++/STL Headers
#include <memory>

// Dependency Headers
#include <pybind11/pybind11.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Additional Template-GPU Headers
#include "byEAjksCom/Libraries/Template/GPU/Version.h"
#include "byEAjksCom/Libraries/Template/GPU/CObjectFactory.h"
#include "byEAjksCom/Libraries/Template/GPU/IObject.h"

namespace GPU = ::byEAjksCom::Libraries::Template::GPU;

PYBIND11_MODULE(TemplateGPUBindingForPython, module)
{
    module.doc() = "Python Binding for the Template-GPU C++ Library";

    ::std::shared_ptr<::spdlog::logger>
    logger = ::std::make_shared<::spdlog::logger>(GPU::LIBRARY_NAME);
    logger->flush_on(::spdlog::level::err);
    logger->set_level(::spdlog::level::trace);
    ::spdlog::register_logger(logger);

    ::spdlog::sink_ptr
    sink = ::std::make_shared<::spdlog::sinks::stdout_color_sink_mt>();
    sink->set_pattern("%^[%L] %v%$");
    sink->set_level(::spdlog::level::trace);
    logger->sinks().push_back(sink);

    pybind11::class_<GPU::CObjectFactory>(module, "CObjectFactory")
        .def(pybind11::init([logger]() { return new GPU::CObjectFactory(logger); }))
        .def("create_instance", &GPU::CObjectFactory::CreateInstance);

    pybind11::class_<GPU::IObject>(module, "IObject")
        .def("run", &GPU::IObject::Run);
}
