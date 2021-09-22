// ToDo
//1) add exception class
//2) add more variants of good cases in tests

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include "../Library/Hypocycloid.h"
#include "Menu.h"

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // here we catch all unexpected exceptions
    try {
        Menu::start(); 
    }
    catch (std::exception& err) {
        std::cout << "[ERROR] Unexpected exception: " << err.what() << std::endl;
    }
}