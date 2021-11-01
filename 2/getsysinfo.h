//
// Created by d3Gaff on 27.10.2021.
//

#ifndef INC_2_GETSYSINFO_H
#define INC_2_GETSYSINFO_H
#include <windows.h>
#include <string_view>
#include <string>
#include <map>

static const std::map<WORD, std::string> proc_arc {
        {PROCESSOR_ARCHITECTURE_AMD64, "AMD64"},
        {PROCESSOR_ARCHITECTURE_ARM, "ARM"},
        {PROCESSOR_ARCHITECTURE_ARM64, "ARM64"},
        {PROCESSOR_ARCHITECTURE_IA64, "Intel Itanium-based"},
        {PROCESSOR_ARCHITECTURE_INTEL, "x86"},
        {PROCESSOR_ARCHITECTURE_UNKNOWN, "Unknown architecture"}
};

std::string_view det_arc(const WORD& arc);

void getSystemInfo();

void getGlobalMemoryStatus();
#endif //INC_2_GETSYSINFO_H
