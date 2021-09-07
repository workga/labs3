#include <iostream>
#include "matrix.h"

using namespace LibMatrix;

// All exceptions finally are caught in main

// Create empty matrix
Matrix LibMatrix::create(const int size) {
	Matrix m;
	m.size = size;

	m.rows = new Row[size];
	for (int i = 0; i < m.size; i++) {
		m.rows[i].len = 0;
		m.rows[i].items = nullptr;
	}

	return m;
}


void LibMatrix::remove(Matrix& m) {
	for (int i = 0; i < m.size; i++) {
		delete[] m.rows[i].items;
	}
	delete m.rows;

	m.size = 0;
	m.rows = nullptr;
}


Matrix LibMatrix::input() {
	int size;

	std::cout << "Enter the size of matrix.\n";
	get_value(size);
	while (size <= 0) {
		std::cout << "Wrong input. Please, try again.\n";
		get_value(size);
	}

	

	Matrix m = create(size);
	Item* buf = new Item[m.size];

	// If critical error occurs here, remove matrix and throw exception further
	try {
		std::cout << "Enter elements.\n";
		for (int i = 0; i < m.size; i++) {
			int count = 0;
			// Put all non-zero values to buffer
			for (int j = 0; j < m.size; j++) {
				double value;
				get_value(value);

				if (value != 0) {
					buf[count].value = value;
					buf[count].column = j;
					count++;
				}
			}

			// Copy values from zero to matrix's row
			m.rows[i].len = count;
			m.rows[i].items = new Item[count];
			for (int k = 0; k < count; k++) {
				m.rows[i].items[k] = buf[k];
			}
		}
	}
	catch ( ... ) {
		remove(m);
		delete[] buf;
		throw;
	}
	// Don't catch eof exception here


	delete[] buf;
	return m;
}


void LibMatrix::output(const char* msg, const Matrix& m) {
	std::cout << msg << std::endl;
	for (int i = 0; i < m.size; i++) {
		Row row = m.rows[i];

		int last_column = -1;
		int gap_len = 0;
		for (int j = 0; j < row.len; j++) {
			Item item = row.items[j];

			gap_len = item.column - last_column - 1;
			for (int k = 0; k < gap_len; k++) {
				std::cout << 0 << "\t";
			}

			std::cout << item.value << "\t";
			last_column = item.column;
		}

		gap_len = m.size - last_column - 1;
		for (int k = 0; k < gap_len; k++) {
			std::cout << 0 << "\t";
		}

		std::cout << std::endl;
	}
}


void LibMatrix::process(Matrix& m) {
	bool changed = false;
	for (int i = 0; i < m.size; i++) {
		Row row = m.rows[i];
		if (row.len <= 1 ) continue;

		int p = -1;
		for (int j = 1; j < row.len; j++) {
			if (row.items[j].value > row.items[j - 1].value) {
				p = j;
				break;
			}
		}

		int q = -1;
		for (int j = row.len - 1; j >= 1; j--) {
			if (row.items[j].value < row.items[j - 1].value) {
				q = j;
				break;
			}
		}

		if (p >= 0 && q >= 0) {
			changed = true;

			double buf_v = row.items[p].value;
			row.items[p].value = row.items[q].value;
			row.items[q].value = buf_v;
		}
	}
	if (!changed) std::cout << "Nothing to change" << std::endl;
}