#ifndef H_MATRIX
#define H_MATRIX

namespace LibMatrix {
	typedef struct Item {
		int column;
		double value;
	} Item;

	typedef struct Row {
		int len;
		Item* items;
	} Row;

	typedef struct Matrix {
		int size;
		Row* rows;
	} Matrix;

	Matrix	create(const int size);
	void	remove(Matrix& m);

	Matrix  input();
	void	output(const char* msg, const Matrix& m, bool verbose = false);

	void	process(Matrix& m);


	template <typename T>
	int get_value(T& v) {
		std::cin >> v;

		while (!std::cin.good()) {
			if (std::cin.bad()) throw std::runtime_error("Fatal error");
			if (std::cin.eof()) throw std::runtime_error("EOF"); 

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Wrong input. Please, try again from incorrect value.\n";
			std::cin >> v;
		}

		return 0;
	}
};

#endif
