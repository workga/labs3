#pragma comment(lib, "MSVCRT -VERBOSE")

#ifdef _MSC_VER

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>

#endif

#include <string>

#include "pch.h"
#include "gtest\gtest.h"


#include "../Application/TextProcessor.h"

//typedef TextProcessor TP;
//
//TP make_tp(std::initializer_list<std::pair<std::string, int>> list) {
//	std::vector<std::pair<std::string, int>> v = list;
//	return TP(v);
//}

TEST(General, Default) {
	//TP tp();

	//TP tp = make_tp({
	//	{"a", 4},
	//	{"b", 3},
	//	{"c", 6},
	//	{"d", 7},
	//	{"e", 5},
	//});

	//tp.get_words();
}


int main(int argc, char* argv[]) {
	#ifdef _CRTDBG_MAP_ALLOC
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
