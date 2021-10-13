#ifndef H_MENU
#define H_MENU

class Menu {
public:
	Menu() = delete;
	static void start();

private:
	enum class Status {
		NOT_CREATED,
		CREATED,
		DELETED,
		MODIFIED,
		NOT_MODIFIED
	};

	static Polynomial_1* p;
	static Status status;

	static void finish();

	// Suppose 0 means "Exit"
	static int ask_yes_no(const char question[] = nullptr);
	static int dialog(const char* options[], int options_number);
	static void print_status();

	
	static int d_constructors();
	static int d_io();
	static int d_operations();
	static int d_tasks();

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

