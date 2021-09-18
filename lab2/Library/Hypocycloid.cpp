#include "pch.h"
#include "framework.h"

#include <stdexcept>
#include <cmath>

#include "Hypocycloid.h"

const double Hypocycloid::EPSILON = 0.00001;


// constructors
Hypocycloid::Hypocycloid() : 
	R_large(1.), R_small(0.25), Dist(0.25) {}

Hypocycloid::Hypocycloid(Hypocycloid& hc) : // Default copy constructor does the same. It's just an exercise
	R_large(hc.R_large), R_small(hc.R_small), Dist(hc.R_small) {}

Hypocycloid::Hypocycloid(double R_large, double R_small) : // Delegating constructor
	Hypocycloid(R_large, R_small, R_small) {}

Hypocycloid::Hypocycloid(double R_large, double R_small, double Dist) {
	if (R_large <= 0) throw std::logic_error("R_large isn't positive");
	if (R_small <= 0) throw std::logic_error("R_small isn't positive");
	if (Dist <= 0)    throw std::logic_error("Dist isn't positive");

	if (R_large <= R_small) throw std::logic_error("R_large isn't larger than current R_small");

	this->R_large = R_large;
	this->R_small = R_small;
	this->Dist    = Dist;
}


// getters
double Hypocycloid::get_R_large() const { return this->R_large; }
double Hypocycloid::get_R_small() const { return this->R_small; }
double Hypocycloid::get_Dist()    const { return this->Dist; }


// setters
Hypocycloid& Hypocycloid::set_R_large(double R_large) {
	if (R_large <= 0) throw std::logic_error("R_large isn't positive");
	if (R_large <= this->R_small) throw std::logic_error("R_large isn't larger than current R_small");

	this->R_large = R_large;
	return *this;
}

Hypocycloid& Hypocycloid::set_R_small(double R_small) {
	if (R_small <= 0) throw std::logic_error("R_small isn't positive");
	if (R_small >= this->R_large) throw std::logic_error("R_small isn't smaller than current R_large");

	this->R_small = R_small;
	return *this;
}

Hypocycloid& Hypocycloid::set_Dist(double Dist) {
	if (Dist <= 0)
		throw std::logic_error("Dist isn't positive");

	this->Dist = Dist;
	return *this;
}



// tasks
Hypocycloid::Type Hypocycloid::calc_type() const {
	if (cmp_doubles(this->Dist, this->R_small)) return Type::ORDINARY;
	if (this->Dist < this->R_small) return Type::SHORT;
	return Type::LONG;
}

Point Hypocycloid::calc_point(double t) const {
	double x, y;

	x = (R_large - R_small) * cos(t) +
		Dist * cos((R_large - R_small) * t / R_small);
	y = (R_large - R_small) * sin(t) -
		Dist * sin((R_large - R_small) * t / R_small);

	return Point{ x, y };
}

double Hypocycloid::calc_S_sectorial(double t) const {
	double s;

	s = ((R_large - R_small) / 2.) *
		((R_large - R_small - Dist * Dist / R_small) * t  + Dist * (R_large - 2. * R_small) * sin(R_large * t / R_small) / R_large );

	return s;
}

double Hypocycloid::calc_R_curvature(double t) const {
	double R_c;

	double denominator = fabs(Dist * Dist * (R_large - R_small) -
							  R_small * R_small * R_small -
							  Dist * R_small * (R_large - 2. * R_small) * cos(R_large * t / R_small));


	if (cmp_doubles(denominator, 0.)) return std::numeric_limits<double>::max();

	double numerator = pow(R_small * R_small + Dist * Dist - 2. * Dist * R_small * cos(R_large * t / R_small), 1.5);

	R_c = numerator / denominator;

	return R_c;
}



// auxilliary
bool Hypocycloid::cmp_doubles(double a, double b) {
	// const epsilon, works badly with large doubles
	return (fabs(a - b) < EPSILON);

	// relative epsilon, doesn't work with near-zero doubles
	/*
	double diff = fabs(a - b);
	a = fabs(a);
	b = fabs(b);
	double largest = (a > b) ? a : b;

	if (diff <= largest * std::numeric_limits<double>::epsilon())
		return true;
	return false;
	*/
}

