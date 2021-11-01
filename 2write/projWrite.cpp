//
// Created by d3Gaff on 31.10.2021.
//

#include "projWrite.h"

void projFile() {
    std::string file_name, map_name;
    std::cout << "Enter file name" << '\n';
    std::getline(std::cin, file_name);
    auto file = CreateFile(file_name.data(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
                           0, nullptr);
    if(file==INVALID_HANDLE_VALUE) {
        std::cout << "File not created. ERROR: " << GetLastError() << '\n';
        return;
    }

    std::cout << "Enter map name" << '\n';
    std::getline(std::cin, map_name);
    auto file_map = CreateFileMapping(file, nullptr, PAGE_READWRITE, 0, 128, map_name.data());
    if(!file_map) {
        std::cout << "File mapping not created. ERROR: " << GetLastError() << '\n';
        return;
    }

    void* lastmap = MapViewOfFile(file_map, FILE_MAP_ALL_ACCESS, 0, 0, 128);
    if(lastmap == INVALID_HANDLE_VALUE) {
        CloseHandle(file);
        std::cout << "File not projected. ERROR: " << GetLastError() << '\n';
        return;
    }
    mappings[map_name].mapping = lastmap;
    mappings[map_name].file = file;
    std::cout << "File projected successfully\n";
}

void write() {

    std::string name, data;
    std::cout << "Enter map name\n";
    std::getline(std::cin, name);
    auto it = mappings.find(name);
    if(it==mappings.end()) {
        std::cout << "No map with such name\n";
        return;
    }

    std::cout << "Enter data\n";
    std::getline(std::cin, data);
    memcpy(it->second.mapping, data.data(), data.size());
    std::cout << "Data written to projected file successfully\n";
}

void clear_mappings() {
    for(auto& i : mappings) {
        close_mapping(i.second);
    }
    mappings.clear();
    std::cout << "All projected files closed\n";
}

void erase_mapping() {
    std::string name;
    std::cout << "Enter map name\n";
    std::getline(std::cin, name);
    auto it = mappings.find(name);
    if(it==mappings.end()) {
        std::cout << "No map with such name\n";
        return;
    }

    close_mapping(it->second);
    mappings.erase(it);
    std::cout << "Projected file closed\n";
}

void close_mapping(handle_mapping& hm) {
    UnmapViewOfFile(hm.mapping);
    CloseHandle(hm.file);
}