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

	static Polynomial_1* p;
	static Status status;


	Menu(); // Private constructor doesn't allow to create an object
	static void finish();

	static void print_status();

	static int dialog(const char* options[], int options_number); // Suppose 0 means "Exit"
	static int d_constructors();
	static int d_io();
	static int d_operations();
	static int d_tasks();
};

#endif

