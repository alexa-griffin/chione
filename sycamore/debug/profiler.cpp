#include "profiler.hpp"

#include "logging.hpp"
#include <stdint.h>

namespace sm {
    Profiler::Profiler(const std::string& funcName, const std::string& file, const uint64_t linenum) :
        functionName(funcName), filename(file), linenumber(linenum),
        startTime(std::chrono::high_resolution_clock::now())
    {
    }

    Profiler::~Profiler()
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = endTime - startTime;

        // follow the same format as the other logging functions for now.
        // eventually replace this with file stuffs.
        _log(std::cout,
             "[PROFILER] ",
             filename,
             ":",
             linenumber,
             "[",
             functionName,
             "] : ",
             std::chrono::duration_cast<std::chrono::microseconds>(duration).count(),
             "us");
    }
} // namespace sm