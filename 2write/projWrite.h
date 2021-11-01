//
// Created by d3Gaff on 31.10.2021.
//

#ifndef INC_2WRITE_PROJWRITE_H
#define INC_2WRITE_PROJWRITE_H
#include <iostream>
#include <string>
#include <map>
#include <windows.h>
#include "safe_input.h"

struct handle_mapping {
    void* mapping = nullptr;
    HANDLE file = INVALID_HANDLE_VALUE;
};

static std::map<std::string, handle_mapping> mappings;

void clear_mappings();
void erase_mapping();
void close_mapping(handle_mapping& hm);
void projFile();
void write();
#endif //INC_2WRITE_PROJWRITE_H
