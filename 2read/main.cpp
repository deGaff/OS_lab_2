#include <iostream>
#include <windows.h>
#include "menu.h"
#include "projRead.h"

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    view_menu main_menu("MAIN MENU", menu({
        std::make_shared<action_menu>("Read projected file", read)
    }));
    main_menu.execute();
    return 0;
}
