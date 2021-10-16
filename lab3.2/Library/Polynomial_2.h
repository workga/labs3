#ifndef H_POLYNOMIAL
#define H_POLYNOMIAL


// static implementation without operators overloading
class Polynomial_2 {
public:
	static const int MAX_DEG = 10;

	//------/ Constructors /------

	// Create constant zero.
	Polynomial_2() noexcept;

	// Create constant, not explicit.
	Polynomial_2(double c) noexcept;

	// Factors' length must be at least (deg + 1).
	// Factors start with zero degree.
	explicit Polynomial_2(int deg, const double factors[]); 
	
	// Create monomial
	// (f != 0)
	explicit Polynomial_2(int deg, double f);


	//------/ Operators /---------
	// Input/Output
	friend std::istream& operator>>(std::istream& in, Polynomial_2& a);
	friend std::ostream& operator<<(std::ostream& out, const Polynomial_2& a);

	// Sum
	Polynomial_2& operator+=(const Polynomial_2& a) noexcept;
	friend Polynomial_2 operator+(const Polynomial_2& a, const Polynomial_2& b) noexcept;

	// Sub
	Polynomial_2& operator-=(const Polynomial_2& a) noexcept;
	friend Polynomial_2 operator-(const Polynomial_2& a, const Polynomial_2& b) noexcept;

	// Mult
	Polynomial_2& operator*=(const Polynomial_2& a);
	friend Polynomial_2 operator*(const Polynomial_2& a, const Polynomial_2& b);

	// Div
	Polynomial_2& operator/=(const Polynomial_2& d);
	friend Polynomial_2 operator/(const Polynomial_2& a, const Polynomial_2& d);
	
	// Mod
	Polynomial_2& operator%=(const Polynomial_2& d);
	friend Polynomial_2 operator%(const Polynomial_2& a, const Polynomial_2& d);
	
	// Equals
	friend bool operator==(const Polynomial_2& a, const Polynomial_2& b);
	friend bool operator!=(const Polynomial_2& a, const Polynomial_2& b); 

	// Value
	double operator()(double x) const noexcept;
	
	// Index
	double operator[](int i) const;

	//------/ Tasks /-----------------
	Polynomial_2& derivative() noexcept;
	Polynomial_2& derivative(Polynomial_2& result) const noexcept;

	int root(double a, double b, double& res) const;

	//------/ Auxiliary /---------------
	bool equals_accurately(const Polynomial_2& a) const noexcept;
	int deg() const noexcept { return m_deg; };

private:
	static const int NEWTONE_ITERATIONS_LIMIT = 10000;
	
	int m_deg;
	double m_factors[MAX_DEG + 1];

	// Return lead factor
	double lead() const noexcept { return m_factors[m_deg]; };
};


bool cmp_doubles(double a, double b) noexcept;

#endif