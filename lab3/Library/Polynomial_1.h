#ifndef H_POLYNOMIAL
#define H_POLYNOMIAL

// TODO
// self???


// static implementation without operators overloading
class Polynomial_1 {
public:
	static const int MAX_DEG = 10;

	//------/ Constructors /------

	// Create constant zero.
	Polynomial_1() noexcept;

	// Create constant, not explicit.
	Polynomial_1(double c) noexcept;

	// Factors' length must be at least (deg + 1).
	// Factors start with zero degree.
	explicit Polynomial_1(int deg, const double factors[]); 
	
	// Create monomial
	// (f != 0)
	explicit Polynomial_1(int deg, double f);


	//------/ Input/Output /-------
	std::istream& input(std::istream& in);
	std::ostream& output(std::ostream& out) const noexcept;


	//------/ Operations /---------
	Polynomial_1& sum(const Polynomial_1& a) noexcept;
	Polynomial_1& sum(const Polynomial_1& a, Polynomial_1& result) const noexcept;

	Polynomial_1& sub(const Polynomial_1& a) noexcept;
	Polynomial_1& sub(const Polynomial_1& a, Polynomial_1& result) const noexcept;

	Polynomial_1& mult(const Polynomial_1& a);
	Polynomial_1& mult(const Polynomial_1& a, Polynomial_1& result) const;

	Polynomial_1& div(const Polynomial_1& d);
	Polynomial_1& div(const Polynomial_1& d, Polynomial_1& result) const;
	
	Polynomial_1& mod(const Polynomial_1& d);
	Polynomial_1& mod(const Polynomial_1& d, Polynomial_1& result) const;
	
	Polynomial_1& derivative() noexcept;
	Polynomial_1& derivative(Polynomial_1& result) const noexcept;

	bool equals(const Polynomial_1& a, bool accurately=false) const noexcept;


	double value(double x) const noexcept;
	int root(double a, double b, double& res) const;
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