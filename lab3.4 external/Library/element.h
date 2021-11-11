#include <iostream>
#include <exception>
#include <cstring>
#include <limits>

#pragma once

typedef struct Element {
	static const int strSZ = 3;
	int _a, _b;

	Element() : _a(0), _b(0) {};
	Element(int a, int b) : _a(a), _b(b) {};

	std::ostream & print(std::ostream &) const;
	std::istream & scan(std::istream &);

	friend std::ostream & operator<<(std::ostream &, const Element &);
	friend std::istream & operator>>(std::istream &, Element &);
} Element;
