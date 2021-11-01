//
// Created by d3Gaff on 29.10.2021.
//

#include "mem_manager.h"



void getMemRegState() {
    void* ptr;
    MEMORY_BASIC_INFORMATION info;

    std::cout << "Enter pointer ";
    if(!(safestream >> ptr)) {
        std::cout << "Invalid input: " << safestream.get_state() << '\n';
        return;
    }
    if(!VirtualQuery(ptr, &info, sizeof(info))) {
        std::cout << "ERROR: " << GetLastError();
        return;
    }

    std::cout << "Base address: " << info.BaseAddress << '\n'
    << "Allocation base address: " << info.AllocationBase << '\n';
    if(info.Protect) printMemProtect(info.Protect);
    std::cout << "Region size: " << info.RegionSize << '\n'
    << "Type: pages within region are " << type_str.find(info.Type)->second << '\n'
    << "State: " << state_str.find(info.State)->second << '\n';
}

void allocAuto() {
    alloc();
}

void allocAutoPhys() {
    alloc(nullptr, true);
}

void allocPtr() {
    void* ptr;
    std::cout << "Enter pointer ";
    if(!(safestream >> ptr)) {
        std::cout << "Invalid input: " << safestream.get_state() << '\n';
        return;
    }
    alloc(ptr);
}

void allocPtrPhys() {
    void* ptr;
    std::cout << "Enter pointer ";
    if(!(safestream >> ptr)) {
        std::cout << "Invalid input: " << safestream.get_state() << '\n';
        return;
    }
    alloc(ptr, true);
}

void alloc(void* ptr, const bool& phys) {
    SYSTEM_INFO info;
    GetSystemInfo(&info);

    DWORD type = MEM_RESERVE | ((phys) ? MEM_COMMIT : 0);
    void* a_ptr = nullptr;

    unsigned ch = 0;
    do {
        std::cout << "Enter amount of pages to allocate\n";
        if(!(safestream >> ch) || ch < 1) {
            std::cout << "Invalid input: ";
            if(!safestream) {
                std::cout << safestream.get_state();
            }
            else {
                std::cout << " amount should be at least 1";
            }
            std::cout << '\n';
        }
    }while((!safestream) || ch < 1);

    a_ptr = VirtualAlloc(ptr, ch*info.dwPageSize, type, PAGE_EXECUTE_READWRITE);
    if(!a_ptr) {
        std::cout << "ERROR: " << GetLastError();
        return;
    }
    std::cout << "Allocated, base address: " << a_ptr << '\n';

}

void virtProt() {
    SYSTEM_INFO info;
    GetSystemInfo(&info);

    void* ptr;
    DWORD protect = 0, n_protect = 0;

    std::cout << "Enter pointer ";
    if(!(safestream >> ptr)) {
        std::cout << "Invalid input: " << safestream.get_state() << '\n';
        return;
    }

    if(!inputMemProtect(n_protect)) {
        return;
    }

    if(!VirtualProtect(ptr, info.dwPageSize, n_protect, &protect)) {
        std::cout << "ERROR: " << GetLastError() << '\n';
        return;
    }

    std::cout << "Protection changed successfully.\nNew protection: ";
    printMemProtect(n_protect);
    std::cout << "Old protection: ";
    printMemProtect(protect);
}

bool inputMemProtect(DWORD& protect) {
    unsigned ch = 0;

    do {
        system("cls");
        std::cout << "\tChoose main memory protection constant\n";
        unsigned i = 1;
        for(const auto& p : mem_protect_FOR_CHANGING) {
            std::cout << i << ". " << p.second << '\n';
            ++i;
        }
        std::cout << i << ". Exit\n";
        if(!(safestream >> ch) || ch < 1 || ch > mem_protect_FOR_CHANGING.size() + 1) {
            std::cout << "Invalid input: ";
            if(!safestream) std::cout << safestream.get_state();
            else std::cout << "no choice with that number";
            std::cout << std::endl;
            pause();
        }
    }while(!safestream || ch < 1 || ch > mem_protect_FOR_CHANGING.size() + 1);

    if(ch == mem_protect_FOR_CHANGING.size() + 1) return false;

    protect |= mem_protect_FOR_CHANGING[ch-1].first;
    ch = 0;

    do {
        system("cls");
        std::cout << "\tChoose secondary memory protection constant\n";
        unsigned i = 1;
        for( ;i < mod_mem_protect.size(); ++i) {
            std::cout << i << ". " << mod_mem_protect[i-1].second << '\n';
        }
        std::cout << i << ". No secondary\n";
        std::cout << i+1 << ". Exit without setting protection constant\n";
        if(!(safestream >> ch) || ch < 1 || ch > mod_mem_protect.size() + 2) {
            std::cout << "Invalid input: ";
            if(!safestream) std::cout << safestream.get_state();
            else std::cout << "no choice with that number";
            std::cout << std::endl;
            pause();
        }
    }while(!safestream || ch < 1 || ch > mod_mem_protect.size() + 2);

    if(ch == mod_mem_protect.size() + 1) return false;
    if(ch != mod_mem_protect.size()) protect |= mod_mem_protect[ch-1].first;
    return true;

}


void printMemProtect(const DWORD& protect) {
    for(const auto& base : mem_protect) {
        for(const auto& mod: mod_mem_protect) {
            if((base.first|mod.first) == protect) {
                std::cout << "Memory protection: " << base.second << ' ' << mod.second << '\n';
                return;
            }
        }
    }
}

void enterDataIntoReg() {
    //TODO make possibility for more than 4k symbols to entered

    void* ptr;
    std::string data;

    std::cout << "Enter pointer ";
    if(!(safestream >> ptr)) {
        std::cout << "Invalid input: " << safestream.get_state() << '\n';
        return;
    }

    std::cout << "Enter data ";
    std::getline(std::cin, data);

    memcpy(ptr, data.data(), data.size());

    std::cout << "Data successfully entered. Data: " << data << '\n';
}

void readDataInReg() {
    SYSTEM_INFO info;
    GetSystemInfo(&info);

    void* ptr;
    std::string data;

    std::cout << "Enter pointer ";
    if(!(safestream >> ptr)) {
        std::cout << "Invalid input: " << safestream.get_state() << '\n';
        return;
    }

    data.assign(reinterpret_cast<char*>(ptr), info.dwPageSize);
    std::cout << "Data successfully read. Data:\n" << data << '\n';
}

void virtFree() {
    void* ptr;

    std::cout << "Enter pointer ";
    if(!(safestream >> ptr)) {
        std::cout << "Invalid input: " << safestream.get_state() << '\n';
        return;
    }

    if(!VirtualFree(ptr, 0, MEM_RELEASE)) {
        std::cout << "ERROR: " << GetLastError() << '\n';
        return;
    }
    std::cout << "Memory freed successfully\n";
}