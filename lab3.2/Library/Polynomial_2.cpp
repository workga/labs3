#include "pch.h"
#include "framework.h"

#include <iostream>
#include <cmath>

#include "Polynomial_2.h"

const double EPSILON = 0.0000001;

//------/ Constructors /------

// Create constant zero.
Polynomial_2::Polynomial_2() noexcept : m_deg(0) {
	m_factors[0] = 0;
}

// Create constant, not explicit.
Polynomial_2::Polynomial_2(double c) noexcept : m_deg(0) {
	m_factors[0] = c;
}

// Factors' length must be at least (deg + 1).
// Factors start with zero degree.
Polynomial_2::Polynomial_2(int deg, const double factors[]) {
	if (deg < 0)
		throw std::logic_error("Negative degree.");
	if (deg > MAX_DEG)
		throw std::logic_error("Too big degree.");

	m_deg = deg;
	for (int i = 0; i <= m_deg; i++) {
		m_factors[i] = factors[i];
	}

	while (m_factors[m_deg] == 0 && m_deg > 0)
		m_deg--;
}

// Create monomial
// (f != 0)
Polynomial_2::Polynomial_2(int deg, double f) {
	if (deg < 0)
		throw std::logic_error("Negative degree.");
	if (deg > MAX_DEG)
		throw std::logic_error("Too big degree.");

	m_deg = deg;
	m_factors[deg] = f;

	for (int i = 0; i < m_deg; i++) {
		m_factors[i] = 0;
	}
}


//------/ Operators /---------
// Input/Output
std::istream& operator>>(std::istream& in, Polynomial_2& a) {
	int deg;
	double factors[Polynomial_2::MAX_DEG + 1];
	
	in >> deg;
	if (!in.good()) {
		return in;
	}

	if (deg > Polynomial_2::MAX_DEG || deg < 0) {
		in.setstate(std::ios::failbit);
		return in;
	}

	for (int i = 0; i <= deg; i++) {
		in >> factors[i];
		if (!in.good()) {
			return in;
		}
	}

	a.m_deg = deg;
	for (int i = 0; i <= a.m_deg; i++) {
		a.m_factors[i] = factors[i];
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, const Polynomial_2& a) {
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
Polynomial_2& Polynomial_2::operator+=(const Polynomial_2& a) noexcept {
	for (int i = 0; i <= a.deg(); i++) {
		if (i <= m_deg)
			m_factors[i] += a.m_factors[i];
		else
			// These factors may contain garbage.
			m_factors[i] = a.m_factors[i];
	}

	int n = std::max(m_deg, a.deg());

	// Decrease degree only if current factor equals zero accurately.
	while (m_factors[n] == 0 && n > 0)
		n--;

	m_deg = n;

	return *this;
}

Polynomial_2 operator+(const Polynomial_2& a, const Polynomial_2& b) noexcept {
	Polynomial_2 res = a;
	res += b;

	return res;
}

// Sub
Polynomial_2& Polynomial_2::operator-=(const Polynomial_2& a) noexcept {
	Polynomial_2 b = a * (-1);
	(*this) += b;

	return *this;
}

Polynomial_2 operator-(const Polynomial_2& a, const Polynomial_2& b) noexcept {
	Polynomial_2 res = a;
	res -= b;

	return res;
}

// Mult
Polynomial_2& Polynomial_2::operator*=(const Polynomial_2& a) {

	if (m_deg + a.deg() > MAX_DEG) throw std::logic_error("Too big degrees.");

	int deg = m_deg + a.deg();
	double factors[MAX_DEG + 1];
	for (int i = 0; i <= deg; i++) { // It's loop, but it initialize only necessary factors.
		factors[i] = 0;
	}

	for (int i = 0; i <= m_deg; i++) {
		for (int j = 0; j <= a.deg(); j++) {
			factors[i + j] += m_factors[i] * a.m_factors[j];
		}
	}

	// Decrease degree only if current factor equals zero accurately.
	while (factors[deg] == 0 && deg > 0)
		deg--;

	m_deg = deg;
	for (int i = 0; i <= deg; i++) {
		m_factors[i] = factors[i];
	}

	return *this;
}

Polynomial_2 operator*(const Polynomial_2& a, const Polynomial_2& b) {
	Polynomial_2 res = a;
	res *= b;

	return res;
}

// Div
Polynomial_2& Polynomial_2::operator/=(const Polynomial_2& d) {
	if (d.equals_accurately(0)) throw std::logic_error("Dividing by zero.");

	Polynomial_2 q(0);
	Polynomial_2 r = *this;

	while (!r.equals_accurately(0) && r.deg() >= d.deg()) {
		// t is monomial obtained by division of leading terms.
		Polynomial_2 t((r.deg() - d.deg()), (r.lead() / d.lead()));

		q += t;
		r -= (t * d);
	}

	*this = q;
	return *this;
}

Polynomial_2 operator/(const Polynomial_2& a, const Polynomial_2& d) {
	Polynomial_2 res = a;
	res /= d;

	return res;
}

// Mod
Polynomial_2& Polynomial_2::operator%=(const Polynomial_2& d) {
	if (d.equals_accurately(0)) throw std::logic_error("Dividing by zero.");

	Polynomial_2 q(0);
	Polynomial_2 r = *this;

	while (!r.equals_accurately(0) && r.deg() >= d.deg()) {
		// t is monomial obtained by division of leading terms.
		Polynomial_2 t((r.deg() - d.deg()), (r.lead() / d.lead()));

		q += t;
		r -= t * d;
	}

	*this = r;
	return *this;
}

Polynomial_2 operator%(const Polynomial_2& a, const Polynomial_2& d) {
	Polynomial_2 res = a;
	res %= d;

	return res;
}


// Equals
bool operator==(const Polynomial_2& a, const Polynomial_2& b) {
	if (a.deg() != b.deg()) return false;

	for (int i = 0; i <= a.deg(); i++) {
		if (!cmp_doubles(a.m_factors[i], b.m_factors[i])) return false;
	}

	return true;
}

bool operator!=(const Polynomial_2& a, const Polynomial_2& b) {
	return !(a == b);
}

// Value
double Polynomial_2::operator()(double x) const noexcept {
	double value = m_factors[m_deg];
	for (int i = m_deg - 1; i >= 0; i--) {
		value *= x;
		value += m_factors[i];
	}

	return value;
}

// Index
double Polynomial_2::operator[](int i) const {
	if (i < 0) throw std::logic_error("Negative index.");
	if (i > m_deg) throw std::logic_error("Index is greater than degree.");

	return m_factors[i];
}


//------/ Tasks /------------------
Polynomial_2& Polynomial_2::derivative() noexcept {
	if (m_deg == 0) {
		m_factors[m_deg] = 0;
		return *this;
	}

	for (int i = 0; i < m_deg; i++) {
		m_factors[i] = m_factors[i + 1] * (i + 1);
	}
	m_factors[m_deg] = 0;
	m_deg--;

	return *this;
}

Polynomial_2& Polynomial_2::derivative(Polynomial_2& res) const noexcept {
	res = *this;
	res.derivative();

	return res;
}


int Polynomial_2::root(double a, double b, double& res) const {
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


	Polynomial_2 d;
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
bool Polynomial_2::equals_accurately(const Polynomial_2& a) const noexcept {
	if (m_deg != a.deg()) return false;

	for (int i = 0; i <= m_deg; i++) {
		if (m_factors[i] != a.m_factors[i]) return false;
	}

	return true;
}




bool cmp_doubles(double a, double b) noexcept {
	if (fabs(a - b) < EPSILON) return true; // for near-zero doubles
	return fabs(a - b) <= std::max(fabs(a), fabs(b)) * EPSILON; // for bigger doubles
}