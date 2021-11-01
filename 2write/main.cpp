#include <iostream>
#include <windows.h>
#include "menu.h"
#include "projWrite.h"

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    view_menu main_menu("MAIN MENU", menu({
        std::make_shared<action_menu>("Project file fragment into memory", projFile),
        std::make_shared<action_menu>("Write into projected file", write),
        std::make_shared<action_menu>("Erase mapping of projected file", erase_mapping),
        std::make_shared<action_menu>("Clear all mappings of projected files", clear_mappings)
    }));
    main_menu.execute();
    clear_mappings();
    return 0;
}
