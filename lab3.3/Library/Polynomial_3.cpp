#include "pch.h"
#include "framework.h"

#include <iostream>
#include <cmath>

#include "Polynomial_3.h"

using std::swap;

const double EPSILON = 0.0000001;

//------/ Constructors /------

// Create constant zero.
Polynomial_3::Polynomial_3() noexcept
	: m_deg(0) {

	m_factors = new double[1];
	m_factors[0] = 0;
}

// Create constant, not explicit.
Polynomial_3::Polynomial_3(double c) noexcept
	: m_deg(0) {

	m_factors = new double[1];
	m_factors[0] = c;
}

// Factors' length must be at least (deg + 1).
// Factors start with zero degree.
Polynomial_3::Polynomial_3(int deg, const double factors[])
	: m_deg(deg) {

	if (deg < 0)
		throw std::logic_error("Negative degree.");

	while (factors[m_deg] == 0 && m_deg > 0)
		m_deg--;

	m_factors = new double[m_deg + 1];
	try {
		std::copy(factors, factors + m_deg + 1, m_factors);
	}
	catch (std::exception& err) {
		delete[] m_factors;
		throw;
	}
}

// Create monomial
// (f != 0)
Polynomial_3::Polynomial_3(int deg, double f)
	: m_deg(deg) {

	if (deg < 0)
		throw std::logic_error("Negative degree.");


	m_factors = new double[m_deg + 1](); // All elements equal zero
	m_factors[m_deg] = f;
}


//---/ Copy-and-swap idiom /----//

// Copy constructor
Polynomial_3::Polynomial_3(const Polynomial_3& other)
	: m_deg(other.m_deg) {
	
	m_factors = new double[other.m_deg + 1];

	try {
		std::copy(other.m_factors, other.m_factors + other.m_deg + 1, m_factors);
	}
	catch (std::exception& err) {
		delete[] m_factors;
		throw;
	}
}

// Copy assignment operator
Polynomial_3& Polynomial_3::operator=(const Polynomial_3& other) {
	Polynomial_3 copy(other);
	swap(*this, copy);
	return *this;
}

// Move constructor
Polynomial_3::Polynomial_3(Polynomial_3&& other) noexcept
	: Polynomial_3() {
	swap(*this, other);
}

// Move assignment operator
Polynomial_3& Polynomial_3::operator=(Polynomial_3&& other) noexcept {
	swap(*this, other);
	return *this;
}

// noexcept swap
void swap(Polynomial_3& a, Polynomial_3& b) noexcept {
	using std::swap;

	swap(a.m_deg, b.m_deg);
	swap(a.m_factors, b.m_factors);
}

//------------------------------//

Polynomial_3::~Polynomial_3() {
	delete[] m_factors;
}

//------/ Operators /---------
// Input/Output
std::istream& operator>>(std::istream& in, Polynomial_3& a) {
	int deg;
	double *factors = nullptr;
	
	try {
		in >> deg;
		if (!in.good()) {
			return in;
		}

		if (deg < 0) {
			in.setstate(std::ios::failbit);
			return in;
		}

		factors = new double[deg + 1];
		for (int i = 0; i <= deg; i++) {
			in >> factors[i];
			if (!in.good()) {
				delete[] factors;
				return in;
			}
		}

		a.m_deg = Polynomial_3::remove_leading_zeroes(factors, deg + 1) - 1;
		delete[] a.m_factors;
		a.m_factors = factors;
	}
	catch (std::exception& err) {
		delete[] factors;
		throw;
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, const Polynomial_3& a) {
	out << a.m_factors[0];
	for (int i = 1; i <= a.m_deg; i++) {
		if (a.m_factors[i] == 1)
			out << "+";
		else if (a.m_factors[i] == -1)
			out << "-";
		else {
			out << std::showpos << a.m_factors[i] << std::noshowpos;
		}
		out << "x";
		if (i >= 2) out << "^" << i;
	}

	out << std::endl;
	return out;
}

// Sum
Polynomial_3& Polynomial_3::operator+=(const Polynomial_3& a) noexcept {
	if (m_deg < a.m_deg) {
		set_size(m_factors, m_deg + 1, a.m_deg + 1);
	}

	for (int i = 0; i <= a.deg(); i++) {
		m_factors[i] += a.m_factors[i];
	}

	m_deg = std::max(m_deg, a.deg());
	m_deg = remove_leading_zeroes(m_factors, m_deg + 1) - 1;

	return *this;
}

Polynomial_3 operator+(const Polynomial_3& a, const Polynomial_3& b) noexcept {
	Polynomial_3 res = a;
	res += b;

	return res;
}

// Sub
Polynomial_3& Polynomial_3::operator-=(const Polynomial_3& a) noexcept {
	Polynomial_3 b = a * (-1);
	(*this) += b;

	return *this;
}

Polynomial_3 operator-(const Polynomial_3& a, const Polynomial_3& b) noexcept {
	Polynomial_3 res = a;
	res -= b;

	return res;
}

// Mult
Polynomial_3& Polynomial_3::operator*=(const Polynomial_3& a) {
	int deg = m_deg + a.deg();
	double* factors = new double[deg + 1]();

	for (int i = 0; i <= m_deg; i++) {
		for (int j = 0; j <= a.deg(); j++) {
			factors[i + j] += m_factors[i] * a.m_factors[j];
		}
	}

	m_deg = remove_leading_zeroes(factors, deg + 1) - 1;


	delete[] m_factors;
	m_factors = factors;

	return *this;
}

Polynomial_3 operator*(const Polynomial_3& a, const Polynomial_3& b) {
	Polynomial_3 res = a;
	res *= b;

	return res;
}

// Div
Polynomial_3& Polynomial_3::operator/=(const Polynomial_3& d) {
	if (d.equals_accurately(0)) throw std::logic_error("Dividing by zero.");

	Polynomial_3 q(0);
	Polynomial_3 r = *this;

	while (!r.equals_accurately(0) && r.deg() >= d.deg()) {
		// t is monomial obtained by division of leading terms.
		Polynomial_3 t((r.deg() - d.deg()), (r.lead() / d.lead()));

		q += t;
		r -= (t * d);
	}

	*this = q;
	return *this;
}

Polynomial_3 operator/(const Polynomial_3& a, const Polynomial_3& d) {
	Polynomial_3 res = a;
	res /= d;

	return res;
}

// Mod
Polynomial_3& Polynomial_3::operator%=(const Polynomial_3& d) {
	if (d.equals_accurately(0)) throw std::logic_error("Dividing by zero.");

	Polynomial_3 q(0);
	Polynomial_3 r = *this;

	while (!r.equals_accurately(0) && r.deg() >= d.deg()) {
		// t is monomial obtained by division of leading terms.
		Polynomial_3 t((r.deg() - d.deg()), (r.lead() / d.lead()));

		q += t;
		r -= t * d;
	}

	*this = r;
	return *this;
}

Polynomial_3 operator%(const Polynomial_3& a, const Polynomial_3& d) {
	Polynomial_3 res = a;
	res %= d;

	return res;
}


// Equals
bool operator==(const Polynomial_3& a, const Polynomial_3& b) {
	if (a.deg() != b.deg()) return false;

	for (int i = 0; i <= a.deg(); i++) {
		if (!cmp_doubles(a.m_factors[i], b.m_factors[i])) return false;
	}

	return true;
}

bool operator!=(const Polynomial_3& a, const Polynomial_3& b) {
	return !(a == b);
}

// Value
double Polynomial_3::operator()(double x) const noexcept {
	double value = m_factors[m_deg];
	for (int i = m_deg - 1; i >= 0; i--) {
		value *= x;
		value += m_factors[i];
	}

	return value;
}

// Index
double Polynomial_3::operator[](int i) const {
	if (i < 0) throw std::logic_error("Negative index.");
	if (i > m_deg) throw std::logic_error("Index is greater than degree.");

	return m_factors[i];
}


//------/ Tasks /------------------
Polynomial_3& Polynomial_3::derivative() noexcept {
	if (m_deg == 0) {
		m_factors[m_deg] = 0;
		return *this;
	}

	for (int i = 0; i < m_deg; i++) {
		m_factors[i] = m_factors[i + 1] * (i + 1);
	}

	set_size(m_factors, m_deg + 1, m_deg);
	m_deg--;

	return *this;
}

Polynomial_3& Polynomial_3::derivative(Polynomial_3& res) const noexcept {
	res = *this;
	res.derivative();

	return res;
}


int Polynomial_3::root(double a, double b, double& res) const {
	if (a >= b) throw std::logic_error("Invalid interval.");

	double va = (*this)(a);
	double vb = (*this)(b);

	if (cmp_doubles(va, 0)) {
		res = a;
		return 0;
	}
	if (cmp_doubles(vb, 0)) {
		res = b;
		return 0;
	}

	if (va * vb > 0) return 1;


	Polynomial_3 d;
	derivative(d);

	double cur_x = a + (b - a) / 2;
	int count = 0;
	while (!cmp_doubles((*this)(cur_x), 0) && count <= NEWTONE_ITERATIONS_LIMIT) {
		cur_x = cur_x - (*this)(cur_x) / d(cur_x);
		count++;
	}

	if (count > NEWTONE_ITERATIONS_LIMIT) return 1;

	res = cur_x;
	return 0;
}


//------/ Auxiliary /---------------
bool Polynomial_3::equals_accurately(const Polynomial_3& a) const noexcept {
	if (m_deg != a.deg()) return false;

	for (int i = 0; i <= m_deg; i++) {
		if (m_factors[i] != a.m_factors[i]) return false;
	}

	return true;
}

// allocate or reallocate m_factors
void Polynomial_3::set_size(double*& old_factors, int old_size, int new_size) {
	if (old_size == new_size)
		return;

	double* new_factors = new double[new_size]();
	try {
		if (!old_factors) {
			old_factors = new_factors;
			return;
		}
		
		std::copy(old_factors, old_factors + std::min(old_size, new_size), new_factors);
	}
	catch (std::exception& err) {
		delete[] new_factors;
		throw;
	}

	delete[] old_factors;
	old_factors = new_factors;
}

int Polynomial_3::remove_leading_zeroes(double*& old_factors, int old_size) {
	int n = old_size;
	while (old_factors[n - 1] == 0 && n - 1 > 0)
		n--;

	if (n == old_size)
		return old_size;

	set_size(old_factors, old_size, n);

	return n;
}


bool cmp_doubles(double a, double b) noexcept {
	if (fabs(a - b) < EPSILON) return true; // for near-zero doubles
	return fabs(a - b) <= std::max(fabs(a), fabs(b)) * EPSILON; // for bigger doubles
}