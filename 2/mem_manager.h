//
// Created by d3Gaff on 29.10.2021.
//

#ifndef INC_2_MEM_MANAGER_H
#define INC_2_MEM_MANAGER_H
#include "menu.h"
#include <windows.h>
#include <map>
#include <vector>
#include <string>
#include <string_view>

static const std::vector<std::pair<DWORD, std::string>> mem_protect_FOR_CHANGING  {
        {PAGE_EXECUTE,          "execute"},
        {PAGE_EXECUTE_READ,     "execute or read-only"},
        {PAGE_EXECUTE_READWRITE,"execute, read-only, or read/write"},
        {PAGE_NOACCESS,         "none"},
        {PAGE_READONLY,         "read-only"},
        {PAGE_READWRITE,        "read-only or read/write"},
        {PAGE_TARGETS_NO_UPDATE,"no update"}
};

static const std::vector<std::pair<DWORD, std::string>> mem_protect  {
        {PAGE_EXECUTE,          "execute"},
        {PAGE_EXECUTE_READ,     "execute or read-only"},
        {PAGE_EXECUTE_READWRITE,"execute, read-only, or read/write"},
        {PAGE_EXECUTE_WRITECOPY,"execute, read-only, or copy-on-write"},
        {PAGE_NOACCESS,         "none"},
        {PAGE_READONLY,         "read-only"},
        {PAGE_READWRITE,        "read-only or read/write"},
        {PAGE_WRITECOPY,        "read-only or copy-on-write"},
        {PAGE_TARGETS_INVALID,  "invalid targets"},
        {PAGE_TARGETS_NO_UPDATE,"no update"}
};

static const std::vector<std::pair<DWORD, std::string>> mod_mem_protect  {
        {PAGE_GUARD, "guard"},
        {PAGE_NOCACHE, "non-cachable"},
        {PAGE_WRITECOMBINE, "write-combined"},
        {0x00000000, ""}
};

static const std::map<DWORD, std::string> type_str {
        {MEM_IMAGE, "mapped into the view of an image section"},
        {MEM_MAPPED, "mapped into the view of a section"},
        {MEM_PRIVATE, "private"}
};

static const std::map<DWORD, std::string> state_str {
        {MEM_COMMIT, "committed"},
        {MEM_FREE, "free pages"},
        {MEM_RESERVE, "reserved pages"}
};

void allocAuto();
void allocAutoPhys();
void allocPtr();
void allocPtrPhys();
void alloc(void* ptr = nullptr, const bool& phys = false);

void virtProt();
bool inputMemProtect(DWORD& protect);

void getMemRegState();

void enterDataIntoReg();
void readDataInReg();
void virtFree();

void printMemProtect(const DWORD& protect);

#endif //INC_2_MEM_MANAGER_H
