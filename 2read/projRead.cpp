//
// Created by d3Gaff on 01.11.2021.
//

#include "projRead.h"

void read() {
    std::string map_name;

    std::cout << "Enter map name" << '\n';
    std::getline(std::cin, map_name);
    auto mapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, map_name.data());
    if(mapping == nullptr || mapping == INVALID_HANDLE_VALUE) {
        std::cout << "File mapping not found. ERROR: " << GetLastError();
        return;
    }

    auto h = MapViewOfFile(mapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);

    if(h == INVALID_HANDLE_VALUE) {
        std::cout << "File not projected. ERROR: " << GetLastError();
        return;
    }

    std::string data(reinterpret_cast<char*>(h));
    std::cout << "Read data:\n" << data << '\n';
}