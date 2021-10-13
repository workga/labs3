#include "pch.h"
#include "framework.h"

#include <iostream>
#include <cmath>

#include "Polynomial_1.h"

const double EPSILON = 0.0000001;

//------/ Constructors /------

// Create constant zero.
Polynomial_1::Polynomial_1() noexcept : m_deg(0) {
	m_factors[0] = 0;
}

// Create constant, not explicit.
Polynomial_1::Polynomial_1(double c) noexcept : m_deg(0) {
	m_factors[0] = c;
}

// Factors' length must be at least (deg + 1).
// Factors start with zero degree.
Polynomial_1::Polynomial_1(int deg, const double factors[]) {
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
Polynomial_1::Polynomial_1(int deg, double f) {
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


//------/ Input/Output /-------
std::istream& Polynomial_1::input(std::istream& in) {
	in.exceptions(std::istream::failbit |
				  std::istream::badbit |
				  std::istream::eofbit);

	int deg;
	double factors[MAX_DEG + 1];

	in >> deg;
	if (deg > MAX_DEG || deg < 0) in.setstate(std::ios::failbit);

	for (int i = 0; i <= deg; i++) {
		in >> factors[i];
	}

	m_deg = deg;
	for (int i = 0; i <= m_deg; i++) {
		m_factors[i] = factors[i];
	}

	// Is it a better option?
	// (It will also throw exception if needed)
	// 
	//Polynomial_1 p(deg, factors);
	//*this = p;
	//
	
	return in;
}

std::ostream& Polynomial_1::output(std::ostream& out) const noexcept {
	// Does it make sense?
	// (Remove noexcept if it does)
	// 
	//in.exceptions(std::ostream::failbit |
	//			  std::ostream::badbit |
	//			  std::ostream::eofbit);

	out << m_factors[0];
	for (int i = 1; i <= m_deg; i++) {
		if (m_factors[i] == 1)
			out << "+";
		else if (m_factors[i] == -1)
			out << "-";
		else {
			out << std::showpos << m_factors[i] << std::noshowpos;
		}
		out << "x";
		if (i >= 2) out << "^" << i;
	}

	out << std::endl;
	return out;
}


//------/ Operations /---------
Polynomial_1& Polynomial_1::sum(const Polynomial_1& a) noexcept {
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

Polynomial_1& Polynomial_1::sum(const Polynomial_1& a, Polynomial_1& result) const noexcept {
	result = *this; 
	result.sum(a);

	return result;
}


Polynomial_1& Polynomial_1::sub(const Polynomial_1& a) noexcept {
	Polynomial_1 minus_one(-1);
	Polynomial_1 b;
	a.mult(minus_one, b);

	this->sum(b);

	return *this;
}

Polynomial_1& Polynomial_1::sub(const Polynomial_1& a, Polynomial_1& result) const noexcept {
	result = *this;
	result.sub(a);

	return result;
}


Polynomial_1& Polynomial_1::mult(const Polynomial_1& a) {
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

Polynomial_1& Polynomial_1::mult(const Polynomial_1& a, Polynomial_1& result) const {
	result = *this;
	result.mult(a);

	return result;
}


Polynomial_1& Polynomial_1::div(const Polynomial_1& d) {
	if (d.equals(0, true)) throw std::logic_error("Dividing by zero.");

	Polynomial_1 q(0);
	Polynomial_1 r = *this;

	while (!r.equals(0) && r.deg() >= d.deg()) {
		// t is monomial obtained by division of leading terms.
		Polynomial_1 t((r.deg() - d.deg()), (r.lead() / d.lead()));

		q.sum(t);
		r.sub(t.mult(d)); // attention: modifying t
	}
	
	*this = q;
	return *this;
}

Polynomial_1& Polynomial_1::div(const Polynomial_1& d, Polynomial_1& result) const {
	result = *this;
	result.div(d);

	return result;
}


Polynomial_1& Polynomial_1::mod(const Polynomial_1& d) {
	if (d.equals(0, true)) throw std::logic_error("Dividing by zero.");

	Polynomial_1 q(0);
	Polynomial_1 r = *this;

	while (!r.equals(0, true) && r.deg() >= d.deg()) {
		// t is monomial obtained by division of leading terms.
		Polynomial_1 t((r.deg() - d.deg()), (r.lead() / d.lead()));

		q.sum(t);
		r.sub(t.mult(d)); // attention: modifying t
	}

	*this = r;
	return *this;
}

Polynomial_1& Polynomial_1::mod(const Polynomial_1& d, Polynomial_1& result) const {
	result = *this;
	result.mod(d);

	return result;
}


Polynomial_1& Polynomial_1::derivative() noexcept {
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

Polynomial_1& Polynomial_1::derivative(Polynomial_1& result) const noexcept {
	result = *this;
	result.derivative();

	return result;
}


bool Polynomial_1::equals(const Polynomial_1& a, bool accurately) const noexcept {
	if (m_deg != a.deg()) return false;

	if (accurately) {
		for (int i = 0; i <= m_deg; i++) {
			if (m_factors[i] != a.m_factors[i]) return false;
		}
	}
	else {
		for (int i = 0; i <= m_deg; i++) {
			if (!cmp_doubles(m_factors[i], a.m_factors[i])) return false;
		}
	}

	return true;
}


double Polynomial_1::value(double x) const noexcept {
	double v = m_factors[m_deg];
	for (int i = m_deg - 1; i >= 0; i--) {
		v *= x;
		v += m_factors[i];
	}

	return v;
}

int Polynomial_1::root(double a, double b, double& res) const {
	if (a >= b) throw std::logic_error("Invalid interval.");

	double va = value(a);
	double vb = value(b);

	if (cmp_doubles(va, 0)) {
		res = a;
		return 0;
	}
	if (cmp_doubles(vb, 0)) {
		res = b;
		return 0;
	}

	if (va * vb > 0) return 1;


	Polynomial_1 d;
	derivative(d);

	double cur_x = a + (b - a) / 2;
	int count = 0;
	while (!cmp_doubles(value(cur_x), 0) && count <= NEWTONE_ITERATIONS_LIMIT) {
		cur_x = cur_x - value(cur_x) / d.value(cur_x);
		count++;
	}

	if (count > NEWTONE_ITERATIONS_LIMIT) return 1;

	res = cur_x;
	return 0;
}



bool cmp_doubles(double a, double b) noexcept {
	if (fabs(a - b) < EPSILON) return true; // for near-zero doubles
	return fabs(a - b) <= std::max(fabs(a), fabs(b)) * EPSILON; // for bigger doubles
}

//--------------------------------------------------------------------------
//Polynomial_1& Polynomial_1::div(double b) noexcept {
//	double* a = m_factors;
//	double c[MAX_DEG];
//	int n = m_deg;
//
//	if (n == 0) {
//		m_factors[n] = 0;
//		return *this;
//	}
//
//	c[n - 1] = a[n];
//	for (int i = n - 2; i >= 0; i--) {
//		c[i] = a[i + 1] + b * c[i + 1];
//	}
//
//	for (int i = 0; i <= n - 1; i++) {
//		m_factors[i] = c[i];
//	}
//	m_factors[n] = 0;
//	m_deg = n - 1;
//
//	return *this;
//}
//
//Polynomial_1 div(const Polynomial_1& p, double b) noexcept {
//	Polynomial_1 q(p);
//	q.div(b);
//	return q;
//}


//Polynomial_1& Polynomial_1::mod(double b) noexcept {
//	double v = value(b);
//	m_factors[0] = v;
//	for (int i = 1; i <= m_deg; i++) {
//		m_factors[i] = 0;
//	}
//	m_deg = 0;
//	return *this;
//}
//
//Polynomial_1 mod(const Polynomial_1& p, double b) noexcept {
//	Polynomial_1 q(p);
//	q.mod(b);
//	return q;
//}

// it finds only 1 root
//int Polynomial_1::root(double a, double b, double& res) const noexcept {
//	double left = value(a);
//	double right = value(b);
//
//	if (cmp_doubles(left, 0)) {
//		res = a;
//		return 0;
//	}
//	if (cmp_doubles(right, 0)) {
//		res = b;
//		return 0;
//	}
//
//	if (left * right > 0) return 1;
//
//	double c = a + (b - a) / 2;
//	double middle = value(c);
//
//	while (!cmp_doubles(middle, 0)) {
//		// std::cout << "P(" << c << ") = " << middle << "\n";
//		if (middle * left > 0)
//			a = c;
//		else
//			b = c;
//		c = a + (b - a) / 2;
//		middle = value(c);
//	}
//
//	res = c;
//
//	return 0;
//}