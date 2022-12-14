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
#include <string>

// Dependency Headers
#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Additional Template SDK Headers
#include "Version.h"
#include "byEAjksCom/Libraries/Template/CPU/IObjectFactory.h"
#include "byEAjksCom/Libraries/Template/CPU/IObject.h"
#include "byEAjksCom/Libraries/Template/CPU/CObjectFactory.h"
#include "byEAjksCom/Libraries/Template/GPU/IObjectFactory.h"
#include "byEAjksCom/Libraries/Template/GPU/IObject.h"
#include "byEAjksCom/Libraries/Template/GPU/CObjectFactory.h"

namespace CPU = ::byEAjksCom::Libraries::Template::CPU;
namespace GPU = ::byEAjksCom::Libraries::Template::GPU;

//! \brief Is the entry-point of the executable.
//! \param[in] argc The number of command-line arguments.
//! \param[in] argv The command-line arguments.
int
main(
    int argc,
    char ** argv)
{
    ::CLI::App app { EXECUTABLE_NAME + ", v" + EXECUTABLE_VERSION };

    int32_t verbosityLevel { 0 };

    app.add_flag(
        "-v,--verbose",
        verbosityLevel,
        "Sets the verbosity level");

    bool logToFile { false };

    app.add_flag(
        "--log,!--no-log",
        logToFile,
        "Creates a log file.");

    ::std::string logFileName { EXECUTABLE_NAME + ".log" };

    app.add_option(
        "--log-to",
        logFileName,
        "Sets the log file name.");

    try
    {
        app.parse(argc, argv);
    }
    catch (const ::CLI::ParseError & exception)
    {
        return app.exit(exception);
    }

    ::std::shared_ptr<::spdlog::logger>
    logger = ::std::make_shared<::spdlog::logger>(EXECUTABLE_NAME);
    logger->flush_on(::spdlog::level::err);
    logger->set_level(::spdlog::level::trace);
    ::spdlog::register_logger(logger);

    {
        ::spdlog::sink_ptr
        sink = ::std::make_shared<::spdlog::sinks::stdout_color_sink_mt>();
        sink->set_pattern("%^[%L] %v%$");
        logger->sinks().push_back(sink);

        switch (verbosityLevel)
        {
            case  0: sink->set_level(::spdlog::level::warn);  break;
            case  1: sink->set_level(::spdlog::level::info);  break;
            case  2: sink->set_level(::spdlog::level::debug); break;
            default: sink->set_level(::spdlog::level::trace); break;
        }
    }

    if (logToFile == true)
    {
        ::spdlog::sink_ptr
        sink = ::std::make_shared<::spdlog::sinks::basic_file_sink_mt>(logFileName);
        sink->set_pattern("[%T.%F] %l: %v (%n)");
        logger->sinks().push_back(sink);

        switch (verbosityLevel)
        {
            case  0: sink->set_level(::spdlog::level::info);  break;
            case  1: sink->set_level(::spdlog::level::info);  break;
            case  2: sink->set_level(::spdlog::level::debug); break;
            default: sink->set_level(::spdlog::level::trace); break;
        }
    }

    try
    {
        logger->info("starting {}, v{}", EXECUTABLE_NAME, EXECUTABLE_VERSION);

        ::std::unique_ptr<CPU::IObjectFactory>
        factoryCPU = ::std::make_unique<CPU::CObjectFactory>(logger);

        ::std::unique_ptr<CPU::IObject>
        instanceCPU = factoryCPU->CreateInstance();

        instanceCPU->Run();

        ::std::unique_ptr<GPU::IObjectFactory>
        factoryGPU = ::std::make_unique<GPU::CObjectFactory>(logger);

        ::std::unique_ptr<GPU::IObject>
        instanceGPU = factoryGPU->CreateInstance();

        instanceGPU->Run();

        logger->info("finished successfully");
        logger->flush();

        return (0);
    }
    catch(const ::std::exception & exception)
    {
        logger->error(exception.what());
        logger->info("finished prematurely with error(s)");
        logger->flush();

        return (1);
    }
}
