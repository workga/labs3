#ifndef H_POLYNOMIAL
#define H_POLYNOMIAL

// 1) ccheck noexcept


// static implementation without operators overloading
class Polynomial_3 {
public:
	static const int MAX_DEG = 10;

	//------/ Constructors /------

	// Create constant zero.
	Polynomial_3() noexcept;

	// Create constant, not explicit.
	Polynomial_3(double c) noexcept;

	// Factors' length must be at least (deg + 1).
	// Factors start with zero degree.
	Polynomial_3(int deg, const double factors[]); 
	
	// Create monomial
	// (f != 0)
	explicit Polynomial_3(int deg, double f);


	//---/ Copy-and-swap idiom /----//

	// Copy constructor
	Polynomial_3(const Polynomial_3& other);

	// Copy assignment operator
	Polynomial_3& operator=(const Polynomial_3& other);

	// Move constructor
	Polynomial_3(Polynomial_3&& other) noexcept;

	// Move assignment operator
	Polynomial_3& operator=(Polynomial_3&& other) noexcept;

	// noexcept swap
	friend void swap(Polynomial_3& a, Polynomial_3& b) noexcept;

	//------------------------------//

	~Polynomial_3();


	//------/ Operators /---------
	// Input/Output
	friend std::istream& operator>>(std::istream& in, Polynomial_3& a);
	friend std::ostream& operator<<(std::ostream& out, const Polynomial_3& a);

	// Sum
	Polynomial_3& operator+=(const Polynomial_3& a) noexcept;
	friend Polynomial_3 operator+(const Polynomial_3& a, const Polynomial_3& b) noexcept;

	// Sub
	Polynomial_3& operator-=(const Polynomial_3& a) noexcept;
	friend Polynomial_3 operator-(const Polynomial_3& a, const Polynomial_3& b) noexcept;

	// Mult
	Polynomial_3& operator*=(const Polynomial_3& a);
	friend Polynomial_3 operator*(const Polynomial_3& a, const Polynomial_3& b);

	// Div
	Polynomial_3& operator/=(const Polynomial_3& d);
	friend Polynomial_3 operator/(const Polynomial_3& a, const Polynomial_3& d);
	
	// Mod
	Polynomial_3& operator%=(const Polynomial_3& d);
	friend Polynomial_3 operator%(const Polynomial_3& a, const Polynomial_3& d);
	
	// Equals
	friend bool operator==(const Polynomial_3& a, const Polynomial_3& b);
	friend bool operator!=(const Polynomial_3& a, const Polynomial_3& b); 

	// Value
	double operator()(double x) const noexcept;
	
	// Index
	double operator[](int i) const;

	//------/ Tasks /-----------------
	Polynomial_3& derivative() noexcept;
	Polynomial_3& derivative(Polynomial_3& res) const noexcept;

	int root(double a, double b, double& res) const;

	//------/ Auxiliary /---------------
	bool equals_accurately(const Polynomial_3& a) const noexcept;
	int deg() const noexcept { return m_deg; };

private:
	static const int NEWTONE_ITERATIONS_LIMIT = 10000;
	
	int m_deg;
	//double m_factors[MAX_DEG + 1];
	double *m_factors;

	// Return lead factor
	double lead() const noexcept { return m_factors[m_deg]; };

	// allocate or reallocate m_factors
	static void set_size(double*& old_factors, int old_size, int new_size);
	static int  remove_leading_zeroes(double*& old_factors, int old_size);
};


bool cmp_doubles(double a, double b) noexcept;

#endif