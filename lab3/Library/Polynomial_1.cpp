#include "pch.h"
#include "framework.h"

#include <iostream>
#include <cmath>

#include "Polynomial_1.h"

const double EPSILON = 0.0000001;


// Constructors and Destructor

// Create polynomial "0"
Polynomial_1::Polynomial_1() noexcept : m_deg(0) {
	for (int i = 0; i <= MAX_DEG; i++) {
		m_factors[i] = 0;
	}
}

// factors' length must be at least (deg + 1)
// Descending factors
// Ascending m_factors
Polynomial_1::Polynomial_1(int deg, const double factors[]) {
	if (deg > MAX_DEG) throw std::logic_error("Too big degree");

	m_deg = deg;
	if (!factors) {
		for (int i = 0; i <= MAX_DEG; i++) {
			m_factors[i] = 0;
		}
	}
	else {
		for (int i = 0; i <= m_deg; i++) {
			m_factors[i] = factors[m_deg - i];
		}
		for (int i = m_deg + 1; i <= MAX_DEG; i++) {
			m_factors[i] = 0;
		}
	}
}


// Operations
std::istream& input(std::istream& in, Polynomial_1& p) {
	int degree;
	if (get_value(degree, in)) throw std::runtime_error("EOF");
	if (degree < 0) throw std::logic_error("Negative degree");

	p.m_deg = degree;
	for (int i = 0; i <= p.m_deg; i++) {
		if (get_value(p.m_factors[p.m_deg - i], in)) 
			throw std::runtime_error("EOF");
	}
	
	return in;
}

std::ostream& output(std::ostream& out, const Polynomial_1& p) noexcept {
	bool first = true;
	for (int i = 0; i <= p.m_deg; i++) {
		double cur = p.m_factors[i];
		

		if (!first) {
			out << std::showpos << cur << std::noshowpos;
			out << "x^" << i;
		}
		else out << cur;
		first = false;
	}

	out << std::endl;
	return out;
}


Polynomial_1& Polynomial_1::sum(const Polynomial_1& p) noexcept {
	m_deg = std::max(m_deg, p.m_deg);
	for (int i = 0; i <= p.m_deg; i++) {
		m_factors[i] += p.m_factors[i];
	}

	return *this;
}

Polynomial_1 sum(const Polynomial_1& p1, const Polynomial_1& p2) noexcept {
	Polynomial_1 p(p1);
	p.sum(p2);

	return p;
}


Polynomial_1& Polynomial_1::div(double b) noexcept {
	double* a = m_factors;
	double c[MAX_DEG];
	int n = m_deg;

	if (n == 0) {
		m_factors[n] = 0;
		return *this;
	}

	c[n - 1] = a[n];
	for (int i = n - 2; i >= 0; i--) {
		c[i] = a[i + 1] + b * c[i + 1];
	}

	for (int i = 0; i <= n - 1; i++) {
		m_factors[i] = c[i];
	}
	m_factors[n] = 0;
	m_deg = n - 1;

	return *this;
}

Polynomial_1 div(const Polynomial_1& p, double b) noexcept {
	Polynomial_1 q(p);
	q.div(b);
	return q;
}


Polynomial_1& Polynomial_1::mod(double b) noexcept {
	double v = value(b);
	m_factors[0] = v;
	for (int i = 1; i <= m_deg; i++) {
		m_factors[i] = 0;
	}
	m_deg = 0;
	return *this;
}

Polynomial_1 mod(const Polynomial_1& p, double b) noexcept {
	Polynomial_1 q(p);
	q.mod(b);
	return q;
}


Polynomial_1& Polynomial_1::derivative() noexcept {
	double* a = m_factors;
	double c[MAX_DEG];

	int n = m_deg;

	if (n == 0) {
		m_factors[n] = 0;
		return *this;
	}

	for (int i = 0; i < n; i++) {
		c[i] = a[i + 1] * (static_cast<double>(i) + 1);
	}

	for (int i = 0; i <= n - 1; i++) {
		m_factors[i] = c[i];
	}

	m_factors[n] = 0;
	m_deg = n - 1;

	return *this;
}


Polynomial_1 derivative(const Polynomial_1& p) noexcept {
	Polynomial_1 q(p);
	q.derivative();
	return q;
}



bool Polynomial_1::equals(const Polynomial_1& p) const noexcept {
	if (m_deg != p.m_deg) return false;
	for (int i = 0; i <= m_deg; i++) {
		if (!cmp_doubles(m_factors[i], p.m_factors[i])) return false;
	}

	return true;
}


double Polynomial_1::value(double x) const noexcept {
	double cur_x = 1;
	double v = m_factors[0];
	for (int i = 1; i <= m_deg; i++) {
		cur_x *= x;
		v += m_factors[i] * cur_x;
	}

	return v;
}

// it finds only 1 root
int Polynomial_1::root(double a, double b, double& res) const noexcept {
	double left = value(a);
	double right = value(b);

	if (cmp_doubles(left, 0)) {
		res = a;
		return 0;
	}
	if (cmp_doubles(right, 0)) {
		res = b;
		return 0;
	}

	if (left * right > 0) return 1;

	double c = a + (b - a) / 2;
	double middle = value(c);

	while (!cmp_doubles(middle, 0)) {
		// std::cout << "P(" << c << ") = " << middle << "\n";
		if (middle * left > 0)
			a = c;
		else
			b = c;
		c = a + (b - a) / 2;
		middle = value(c);
	}

	res = c;

	return 0;
}


bool cmp_doubles(double a, double b) noexcept {
	if (fabs(a - b) < EPSILON) return true; // for near-zero doubles
	return fabs(a - b) <= std::max(fabs(a), fabs(b)) * EPSILON; // for bigger doubles
}