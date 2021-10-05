#include <iostream>

#include "../Library/Polynomial_1.h"
#include "Menu.h"

Polynomial_1* Menu::p = nullptr;
Menu::Status Menu::status;

// public:
void Menu::start() {
	const char* options[] = {
		"0. Exit",
		"1. Constructors",
		"2. Input/Output",
		"3. Operations",
		"4. Tasks"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int (*dialogs[])() = {
		nullptr,
		d_constructors,
		d_io,
		d_operations,
		d_tasks
	};

	status = Status::NOT_CREATED;


	// main loop, all expected exceptions should be caught here or somewhere inside,
	// except EOF exception
	try {
		int opt;
		while ((opt = dialog(options, options_number))) {
			if (opt == 0 || dialogs[opt]()) {
				break;
			}
		}
	}
	catch (std::runtime_error& err) {
		std::cout << "[ERROR] Runtime error: " << err.what() << std::endl;
	}


	finish();
	std::cout << "Program finished" << std::endl;
}


// private:
Menu::Menu() {}

void Menu::finish() {
	delete p;
}

void Menu::print_status() {
	switch (status)
	{
	case Menu::Status::NOT_CREATED:
		std::printf("[ Polynomial wasn't created ]\n");
		break;
	case Menu::Status::CREATED:
		std::printf("[ Polynomial was created ]\n");
		break;
	case Menu::Status::DELETED:
		std::printf("[ Polynomial was deleted ]\n");
		break;
	case Menu::Status::MODIFIED:
		std::printf("[ Polynomial was modified ]\n");
		break;
	case Menu::Status::NOT_MODIFIED:
		std::printf("[ Polynomial wasn't modified ]\n");
		break;
	default:
		std::printf("[ Undefined status ]\n");
		break;
	}
}


int Menu::dialog(const char* options[], int options_number) {
	const char* msg = "";
	int opt;

	do {
		std::cout << msg;

		// print status and menu
		std::cout << "\n\n";
		print_status();
		for (int i = 0; i < options_number; i++) {
			std::cout << options[i] << std::endl;
		}
		std::cout << "Make your choice:" << std::endl;


		if (get_value(opt)) {
			opt = 0;
		}

		msg = "Invalid choice. Please, repeate.\n";
	} while (opt < 0 || opt >= options_number);

	return opt;

}



int Menu::d_constructors() {
	const char* options[] = {
		"0. Back",
		"1. Default",
		"2. Parametrized: degree",
		"3. Parametrized: degree and all factors"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);


	int opt = dialog(options, options_number);
	if (opt == 0) return 0;


	int degree;
	Polynomial_1* new_p = nullptr;
	// Catch only possible logical exceptions here. Unexpected, EOF and fatal exceptions are caught in main
	try {
		switch (opt)
		{
		case 1:
			new_p = new Polynomial_1();
			delete p;
			p = new_p;
			break;
		case 2:
			// degree

			if (get_value(degree)) return 1;

			new_p = new Polynomial_1(degree);
			delete p;
			p = new_p;
			break;
		case 3:
			// degree and all factors;

			new_p = new Polynomial_1();
			input(std::cin, *new_p);
			delete p;
			p = new_p;
			break;
		}
		status = Status::CREATED;
	}
	catch (std::logic_error& err) {
		std::cout << "[ERROR] Logical error: " << err.what() << std::endl;
		delete new_p;
	}


	return 0;
}

int Menu::d_io() {
	if (p == nullptr) {
		std::cout << "Unavailable. Please, create Polynomial" << std::endl;
		return 0;
	}

	// Dont catch any exceptions here, because only unexpected and fatal exceptions are possible here
	// and they are caught in main()

	const char* options[] = {
		"0. Back",
		"1. Input another Polynomial",
		"2. Output current Polynomial"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int opt = dialog(options, options_number);
	if (opt == 0) return 0;

	try {
		switch (opt)
		{
		case 1: // Input
			std::cout << "Please, enter degree (int) and then all factors (doubles)\n";
			input(std::cin, *p);
			status = Status::NOT_MODIFIED;
		case 2: // Output
			output(std::cout, *p);
			status = Status::NOT_MODIFIED;
		}
	}
	catch (std::logic_error& err) {
		std::cout << "[ERROR] Logical error: " << err.what() << std::endl;
	}

	return 0;
}

int Menu::d_operations() {
	if (p == nullptr) {
		std::cout << "Unavailable. Please, create Polynomial" << std::endl;
		return 0;
	}

	const char* options[] = {
		"0. Back",
		"1. Sum",
		"2. Div",
		"3. Mod",
		"4. Derivative"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int opt = dialog(options, options_number);
	if (opt == 0) return 0;


	double b;
	Polynomial_1 q;
	try {
		switch (opt)
		{
		case 1: // Sum
			std::cout << "Please, enter Polynomial to add\n (degree (int) and then all factors (doubles))\n";
			input(std::cin, q);
			
			p->sum(q);
			status = Status::MODIFIED;
			break;
		case 2: // Div
			std::cout << "Please, enter b(double) to divide by (x - b)\n";
			if (get_value(b)) return 1;

			p->div(b);
			status = Status::MODIFIED;
			break;
		case 3: // Mod
			std::cout << "Please, enter b(double) to get modulo after dividing by (x - b)\n";
			if (get_value(b)) return 1;

			q = mod(*p, b);
			std::cout << "Modulo: ";
			output(std::cout, q);

			status = Status::NOT_MODIFIED;
			break;
		case 4: // Derivative
			p->derivative();

			status = Status::MODIFIED;
			break;
		}
	}
	catch (std::logic_error& err) {
		std::cout << "[ERROR] Logic_error: " << err.what() << std::endl;
		status = Status::NOT_MODIFIED;
	}

	return 0;
}

int Menu::d_tasks() {
	if (p == nullptr) {
		std::cout << "Unavailable. Please, create Polynomial." << std::endl;
		return 0;
	}

	const char* options[] = {
		"0. Back",
		"1. Value at point",
		"2. Root on interval"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int opt = dialog(options, options_number);
	if (opt == 0) return 0;

	switch (opt)
	{
	case 1: // Value
		std::cout << "Please, enter point x (double)\n";
		double x;
		if (get_value(x)) return 1;

		std::cout << "Value P(" << x << ") = " << p->value(x);
		break;
	case 2: // Root
		std::cout << "Please, enter interval (a, b) (doubles)\n";
		double a, b;
		if (get_value(a) || get_value(b)) return 1;
		if (a >= b) {
			std::cout << "Invalid interval (a >= b)\n";
			return 1;
		}

		double root;
		if (p->root(a, b, root)) std::cout << "No root or our method didn't find it\n";
		else std::cout << "Root of P(x) at interval ( " << a << ", " << b << " ): x = " << root << std::endl;
		break;
	}

	return 0;
}
