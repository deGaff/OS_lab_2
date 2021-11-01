//
// Created by d3Gaff on 28.10.2021.
//

#include "getsysinfo.h"
#include <iostream>
#include <bitset>

std::string_view det_arc(const WORD& arc)
{
    auto it = proc_arc.find(arc);
    if(it!=proc_arc.end()) {
        return it->second;
    }
    return (--proc_arc.end())->second;
}

void getSystemInfo() {
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    std::string mask_buff = std::bitset<32>(info.dwActiveProcessorMask).to_string();
    std::string_view mask(mask_buff);
    mask.remove_prefix(mask.size() - info.dwNumberOfProcessors);
    std::cout << "Processor architecture: " << det_arc(info.wProcessorArchitecture) << '\n'
              << "Number of processors: " << info.dwNumberOfProcessors << '\n'
              << "Active processor mask: " << mask << '\n'
              << "Page size: " << info.dwPageSize << '\n'
              << "Minimum application address: " << info.lpMinimumApplicationAddress <<'\n'
              << "Maximum application address: " << info.lpMaximumApplicationAddress << '\n'
              << "Processor level: " << info.wProcessorLevel << '\n'
              << "Processor revision: " << info.wProcessorRevision << '\n'
              << "Allocation Granularity: " << info.dwAllocationGranularity << '\n';

}

void getGlobalMemoryStatus() {
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    if(!GlobalMemoryStatusEx(&status)) {
        std::cout << "ERROR: " << GetLastError() << '\n';
        return;
    }

    std::cout << "Memory load: " << status.dwMemoryLoad << "%\n"
              << "Available phys memory: "
              << status.ullAvailPhys / 1024 << "/" << status.ullTotalPhys / 1024           << " Kb\n"
              << "Available page memory: "
              << status.ullAvailPageFile / 1024 << "/" << status.ullTotalPageFile / 1024   << " Kb\n"
              << "Available virt memory: "
              << status.ullAvailPhys / 1024 << "/" << status.ullTotalPhys / 1024           << " Kb\n";
}
