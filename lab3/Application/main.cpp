s#ifdef _MSC_VER

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif

#include <iostream>
#include "../Library/Polynomial_1.h"
#include "Menu.h"

int main() {
	#ifdef _CRTDBG_MAP_ALLOC
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

    // here we catch all unexpected exceptions
    try {
        Menu::start();
    }
    catch (std::exception& err) {
        std::cout << "[ERROR] Unexpected exception: " << err.what() << std::endl;
    }
}