#include <iostream>

#include "TextProcessor.h"
#include "Menu.h"


void Menu::start(TextProcessor *tp) {
	_tp = tp;
	const char* options[] = {
		"0. Exit",
		"1. List available files",
		"2. Choose file",
		"3. Analysis"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int (Menu::*dialogs[])() = {
		nullptr,
		&Menu::d_list_files,
		&Menu::d_choose_file,
		&Menu::d_analysis
	};

	status = Status::NOT_LOADED;

	try {
		int opt;
		while ((opt = dialog(options, options_number))) {
			if (opt == 0 || (this->*dialogs[opt])()) {
				break;
			}
		}
	}
	catch (std::runtime_error& err) {
		std::cout << "[ERROR] Runtime error: " << err.what() << std::endl;
	}

	std::cout << "Program finished" << std::endl;
}

int Menu::dialog(const char* options[], int options_number) {
	const char  *msg = "";
	int opt;

	do {
		std::cout << msg;

		std::cout << "\n\n";
		print_status();
		for (int i = 0; i < options_number; i++) {
			std::cout << options[i] << std::endl;
		}
		std::cout << "Make your choice: ";

		if (get_value(opt)) {
			opt = 0;
		}

		msg = "Invalid choice. Please, repeate.\n";
	} while (opt < 0 || opt >= options_number);

	return opt;
}

void Menu::print_status() {
	switch (status)
	{
	case Menu::Status::NOT_LOADED:
		std::printf("[ NOT LOADED ]\n");
		break;
	case Menu::Status::LOADED:
		std::printf("[ LOADED ]\n");
		break;
	case Menu::Status::SORTED:
		std::printf("[ SORTED ]\n");
		break;
	default:
		std::printf("[ <<UNDEFINED STATUS>> ]\n");
		break;
	}
}


int Menu::d_list_files() {
	_tp->list_files(".\\data");

	return 0;
}

int Menu::d_choose_file() {
	std::string filename;
	if (get_value(filename)) return 1;

	_tp->load_words((fs::path(".\\data") /= filename));
	status = Status::LOADED;

	return 0;
}

int Menu::d_analysis() {
	if (status == Status::NOT_LOADED) {
		std::cout << "Choose file for loading and analysis." << std::endl;
		return 0;
	}

	std::cout << "Enter min length of word and max number of words: \n";
	int min_len;
	if (get_value(min_len)) return 1;
	int num;
	if (get_value(num)) return 1;

	_tp->get_words(min_len, num);
	status = Status::SORTED;

	return 0;
}