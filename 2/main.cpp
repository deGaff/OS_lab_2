#include <iostream>
#include <windows.h>
#include "menu.h"
#include "getsysinfo.h"
#include "mem_manager.h"

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    view_menu main_menu("MAIN MENU", menu({
        std::make_shared<action_menu>("System info", getSystemInfo),
        std::make_shared<action_menu>("Global memory status", getGlobalMemoryStatus),
        std::make_shared<view_menu>("Memory management", menu({
            std::make_shared<action_menu>("Get memory region state", getMemRegState),
            std::make_shared<view_menu>("Memory allocation", menu({
                std::make_shared<action_menu>("Allocate auto", allocAuto),
                std::make_shared<action_menu>("Allocate auto physical", allocAutoPhys),
                std::make_shared<action_menu>("Allocate by ptr", allocPtr),
                std::make_shared<action_menu>("Allocate by ptr physical", allocPtrPhys)
            })),
            std::make_shared<action_menu>("Set protection on region", virtProt),
            std::make_shared<action_menu>("Enter data in a region", enterDataIntoReg),
            std::make_shared<action_menu>("Read data from a region", readDataInReg),
            std::make_shared<action_menu>("Free memory", virtFree)
        }))
    }));

    main_menu.execute();
    return 0;
}
