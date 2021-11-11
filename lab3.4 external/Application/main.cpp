#ifdef _MSC_VER

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif

#include <iostream>
#include <string>

#include "TextProcessor.h"
#include "Menu.h"

typedef TextProcessor TP;

int main() {
	#ifdef _CRTDBG_MAP_ALLOC
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	TP tp;
	Menu menu;
	menu.start(&tp);
}