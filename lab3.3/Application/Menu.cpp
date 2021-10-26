#include <iostream>

#include "../Library/Polynomial_3.h"
#include "Menu.h"

Polynomial_3* Menu::p = nullptr;
Menu::Status Menu::status;

//------/ Public /-----------------

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


//------/ Private /----------------

void Menu::finish() {
	delete p;
}

int Menu::ask_yes_no(const char question[]) {
	std::cout << question << std::endl;

	const char* options[] = {
	"0. Back",
	"1. Yes",
	"2. No"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int opt = dialog(options, options_number);
	return opt;
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

//------/ Dialogs /----------------

int Menu::d_constructors() {
	const char* options[] = {
		"0. Back",
		"1. Default",
		"2. Constant",
		"3. Polynomial",
		"4. Monomial"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);


	int opt = dialog(options, options_number);
	if (opt == 0) return 0;


	Polynomial_3* new_p = nullptr;
	try {
		switch (opt) {
			case 1: { // Default
				new_p = new Polynomial_3();

				break;
			}
			case 2: { // Constant
				double c;

				if (get_value(c)) return 1;

				new_p = new Polynomial_3(c);

				break;
			}
			case 3: { // Polynomial
				int deg;
				double factors[Polynomial_3::MAX_DEG + 1];

				if (get_value(deg)) return 1;
				for (int i = 0; i <= deg; i++) {
					if (get_value(factors[i])) return 1;
				}

				new_p = new Polynomial_3(deg, factors);

				break;
			}
			case 4: { // Monomial
				int deg;
				double f;

				if (get_value(deg)) return 1;
				if (get_value(f)) return 1;

				new_p = new Polynomial_3(deg, f);

				break;
			}
		}
		delete p;
		p = new_p;
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
		std::cout << "Unavailable. Please, create Polynomial." << std::endl;
		return 0;
	}


	const char* options[] = {
		"0. Back",
		"1. Input another Polynomial",
		"2. Output current Polynomial"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int opt = dialog(options, options_number);
	if (opt == 0) return 0;

	try {
		switch (opt) {
			case 1: { // Input
				std::cout << "Please, enter degree (int) and then all factors (doubles)\n";
				std::cin >> *p;
				status = Status::MODIFIED;
				break;
			}
			case 2: {// Output
				std::cout << *p;
				status = Status::NOT_MODIFIED;
				break;
			}
		}
	}
	catch (std::logic_error& err) {
		std::cout << "[ERROR] Logical error: " << err.what() << std::endl;
	}
	catch (std::iostream::failure& err) {
		std::cout << "[ERROR] Input stream error: " << err.what() << std::endl;
		
		if (std::cin.bad() || std::cin.eof()) return 1;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return 0;
}

int Menu::d_operations() {
	if (p == nullptr) {
		std::cout << "Unavailable. Please, create Polynomial." << std::endl;
		return 0;
	}

	const char* options[] = {
		"0. Back",

		"1. Sum",
		"2. Sub\n",

		"3. Mult",
		"4. Div",
		"5. Mod\n",

		"6. Derivative"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int opt = dialog(options, options_number);
	if (opt == 0) return 0;

	int answ = ask_yes_no("Modify current Polinomial?");
	if (answ == 0) return 0;

	bool modify = (answ == 1) ? true : false;

	Polynomial_3 q;
	Polynomial_3 res = *p;
	try {
		switch (opt) {
			case 1: { // Sum
				std::cout << "Please, enter Polynomial to add\n" \
					"(degree(int) and then all factors(doubles)).\n";
				std::cin >> q;

				res += q;

				break;
			}
			case 2: { // Sub
				std::cout << "Please, enter Polynomial to substract\n" \
					"(degree(int) and then all factors(doubles)).\n";
				std::cin >> q;

				res -= q;

				break;
			}
			case 3: { // Mult
				std::cout << "Please, enter Polynomial to multiply by\n" \
					"(degree(int) and then all factors(doubles)).\n";
				std::cin >> q;

				res *= q;

				break;
			}
			case 4: { // Div
				std::cout << "Please, enter Polynomial to divide by \n" \
					"(degree(int) and then all factors(doubles)).\n";
				std::cin >> q;

				res /= q;

				break;
			}
			case 5: { // Mod
				std::cout << "Please, enter Polynomial to divide by \n" \
					"(degree(int) and then all factors(doubles)).\n";
				std::cin >> q;

				res %= q;

				break;
			}
			case 6: { // Derivative
				res.derivative();

				break;
			}
		}

		std::cout << "Result:\n";
		std::cout << res;

		if (modify) {
			*p = res;
			status = Status::MODIFIED;
		}
		else {
			status = Status::NOT_MODIFIED;
		}
	}
	catch (std::logic_error& err) {
		std::cout << "[ERROR] Logic_error: " << err.what() << std::endl;
		status = Status::NOT_MODIFIED;
	}
	catch (std::iostream::failure& err) {
		std::cout << "[ERROR] Input stream error: " << err.what() << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
		"2. Root in interval"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int opt = dialog(options, options_number);
	if (opt == 0) return 0;

	switch (opt) {
		case 1: { // Value at point
			std::cout << "Please, enter point x (double).\n";
			double x;
			if (get_value(x)) return 1;

			std::printf("Value P(%10.5lf) = %10.5lf\n", x, (*p)(x));
			break;
		}
		case 2: { // Root in interval
			std::cout << "Please, enter interval (a, b) (doubles).\n";
			double a, b;
			if (get_value(a) || get_value(b)) return 1;
			if (a >= b) {
				std::cout << "Invalid interval (a >= b)\n";
				return 0;
			}

			double root;
			if (p->root(a, b, root)) std::cout << "No root or Newtone's method didn't converge.\n";
			else std::printf("Root of P(x) in interval (%10.5lf, %10.5lf): x = %10.5lf\n", a, b, root);
			break;
		}
	}

	return 0;
}
