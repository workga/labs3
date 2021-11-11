#ifndef __H_MENU
#define __H_MENU

class Menu {
public:
	Menu() {};
	void start(TextProcessor *tp);

private:
	enum class Status {
		NOT_LOADED,
		LOADED,
		SORTED
	};

	TextProcessor* _tp;
	Status status;

	int dialog(const char* options[], int options_number);
	void print_status();

	int d_list_files();
	int d_choose_file();
	int d_analysis();
};

template <typename T>
int get_value(T& v) {
	std::cin >> v;

	while (!std::cin.good()) {
		if (std::cin.bad()) throw std::runtime_error("Input stream fatal error.");
		if (std::cin.eof()) return 1;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Invalid input. Please, try again from incorrect value." << std::endl;
		std::cin >> v;
	}

	return 0;
}

#endif


