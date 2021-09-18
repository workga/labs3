#include <iostream>

#include "../Library/Hypocycloid.h"
#include "Menu.h"

Hypocycloid* Menu::hc = nullptr;
Menu::Status Menu::status;

// public:
void Menu::start() {
	const char* options[] = {
		"0. Exit",
		"1. Constructors",
		"2. Getters",
		"3. Setters",
		"4. Tasks"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int (*dialogs[])() = {
		nullptr,
		d_constructors,
		d_getters,
		d_setters,
		d_tasks
	};

	status = Status::NOT_CREATED;


	// main loop, all expected exceptions should be caught here or somewhere inside
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
	delete hc;
}

void Menu::print_status() {
	switch (status)
	{
	case Menu::Status::NOT_CREATED:
		std::printf("[ Hypocycloid wasn't created ]\n");
		break;
	case Menu::Status::CREATED:
		std::printf("[ Hypocycloid was created (R_large: %lf, R_small: %lf, Dist: %lf)]\n",
					hc->get_R_large(), hc->get_R_small(), hc->get_Dist());
		break;
	case Menu::Status::DELETED:
		std::printf("[ Hypocycloid was deleted ]\n");
		break;
	case Menu::Status::MODIFIED:
		std::printf("[ Hypocycloid was modified (R_large: %lf, R_small: %lf, Dist: %lf)]\n",
					hc->get_R_large(), hc->get_R_small(), hc->get_Dist());
		break;
	case Menu::Status::NOT_MODIFIED:
		std::printf("[ Hypocycloid wasn't modified (R_large: %lf, R_small: %lf, Dist: %lf)]\n",
					hc->get_R_large(), hc->get_R_small(), hc->get_Dist());
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
		"2. R_large and R_small",
		"3. R_large, R_small and Dist"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);


	int opt = dialog(options, options_number);
	if (opt == 0) return 0;


	double R_large, R_small, Dist;
	Hypocycloid* new_hc;
	// Catch only possible logical exceptions here, unexpected and fatal exceptions are caught in main
	try {
		switch (opt)
		{
		case 1:
			new_hc = new Hypocycloid();
			delete hc;
			hc = new_hc;
			break;
		case 2:
			//double R_large, R_small;

			if (get_value(R_large) ||
				get_value(R_small))
			{
				return 1;
			}

			new_hc = new Hypocycloid(R_large, R_small);
			delete hc;
			hc = new_hc;
			break;
		case 3:
			//double R_large, R_small, Dist;

			if (get_value(R_large) ||
				get_value(R_small) ||
				get_value(Dist)) 
			{
				return 1;
			}

			new_hc = new Hypocycloid(R_large, R_small, Dist);
			delete hc;
			hc = new_hc;
			break;
		}
		status = Status::CREATED;
	}
	catch (std::logic_error& err) {
		std::cout << "[ERROR] Logical error: " << err.what() << std::endl;
	}


	return 0;
}

int Menu::d_getters() {
	if (hc == nullptr) {
		std::cout << "Unavailable. Please, create hypocycloid" << std::endl;
		return 0;
	}

	const char* options[] = {
		"0. Back",
		"1. get_R_large",
		"2. get_R_Small",
		"3. get_Dist"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int opt = dialog(options, options_number);
	if (opt == 0) return 0;

	// Dont catch any exceptions here, because only unexpected and fatal exceptions are possible here
	// and they are caught in main()
	switch (opt)
	{
	case 1:
		std::cout << "R_large = " << hc->get_R_large() << std::endl;
		break;
	case 2:
		std::cout << "R_small = " << hc->get_R_small() << std::endl;
		break;
	case 3:
		std::cout << "Dist = " << hc->get_Dist() << std::endl;
		break;
	}

	return 0;
}

int Menu::d_setters() {
	if (hc == nullptr) {
		std::cout << "Unavailable. Please, create hypocycloid" << std::endl;
		return 0;
	}

	const char* options[] = {
	"0. Back",
	"1. set_R_large",
	"2. set_R_Small",
	"3. set_Dist"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int opt = dialog(options, options_number);
	if (opt == 0) return 0;


	double R_large, R_small, Dist;
	// Catch here only logical exceptions
	try {
		switch (opt)
		{
		case 1:
			if (get_value(R_large)) return 1;

			hc->set_R_large(R_large);
			status = Status::MODIFIED;
			break;
		case 2:
			if (get_value(R_small)) return 1;

			hc->set_R_small(R_small);
			status = Status::MODIFIED;
			break;
		case 3:
			if (get_value(Dist)) return 1;

			hc->set_Dist(Dist);
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
	if (hc == nullptr) {
		std::cout << "Unavailable. Please, create hypocycloid." << std::endl;
		return 0;
	}

	const char* options[] = {
		"0. Back",
		"1. calc_Type",
		"2. calc_point(t)",
		"3. calc_S_sectorial(t)",
		"4. calc_R_curvature(t)"
	};
	const int options_number = sizeof(options) / sizeof(options[0]);

	int opt = dialog(options, options_number);
	if (opt == 0) return 0;
	

	double t;
	const char* types[] = {
		"Ordinary",
		"Short",
		"Long"
	};

	// Dont catch any exceptions here, because only unexpected and fatal exceptions are possible here
	// and they are caught in main()
	switch (opt)
	{
	case 1:
		std::cout << "Type is: " << types[(int)(hc->calc_type())] << std::endl;
		break;
	case 2:
		if (get_value(t)) return 1;

		Point p = hc->calc_point(t);
		std::printf("Point is: (%lf, %lf)\n", p.x, p.y);
		break;
	case 3:
		if (get_value(t)) return 1;

		std::printf("S_sectorial = %lf\n", hc->calc_S_sectorial(t));
		break;
	case 4:
		if (get_value(t)) return 1;
		std::printf("R_curvature = %lf\n", hc->calc_R_curvature(t));
		break;
	}

	return 0;
}
