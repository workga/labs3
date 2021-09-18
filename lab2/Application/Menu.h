#ifndef H_MENU
#define H_MENU

class Menu {
public:
	static void start();

private:
	enum class Status {
		NOT_CREATED,
		CREATED,
		DELETED,
		MODIFIED,
		NOT_MODIFIED
	};

	static Hypocycloid* hc;
	static Status status;


	Menu(); // Private constructor doesn't allow to create an object
	static void finish();
	
	static void print_status();
	
	static int dialog(const char* options[], int options_number); // Suppose 0 means "Exit"
	static int d_constructors();
	static int d_getters();
	static int d_setters();
	static int d_tasks();


	template <typename T>
	static int get_value(T& v) {
		std::cin >> v;

		while (!std::cin.good()) {
			if (std::cin.bad()) throw std::runtime_error("Fatal error");
			if (std::cin.eof()) return 1;

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Invalid input. Please, try again from incorrect value" << std::endl;
			std::cin >> v;
		}

		return 0;
	}
};

#endif

