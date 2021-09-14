// Ask about:
// 1) tempaltes and files (.h? .tpp?)
// 2) exceptions
// 3) file
// 4) fail() and bad()

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <fstream>
#include <exception>
#include "matrix.h"

#define TEST_MODE true

using namespace LibMatrix;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	//std::streambuf* cinbuf;
	//if (TEST_MODE) {
	//	cinbuf = std::cin.rdbuf();
	//	std::ifstream test_input("input.txt");
	//	std::cin.rdbuf(test_input.rdbuf());
	//}
	


	Matrix m;
	try {
		m = input();
	}
	catch (std::bad_alloc& err) {
		std::cout << "[ERROR] Bad allocation\n" << err.what() << std::endl;
		return 1;
	}
	catch (std::runtime_error& err) {
		std::cout << err.what() << std::endl;
		return 1;
	}

	output("Original matrix:", m, true);

	process(m);
	output("Processed matrix:", m, true);

	remove(m);

	//if (TEST_MODE) {
	//	std::cin.rdbuf(cinbuf);
	//}
	return 0;
}