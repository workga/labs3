#ifndef H_POLYNOMIAL
#define H_POLYNOMIAL

// TODO
// does division work for constant?
// self???

// overloadings:
// + += 
// - -= 
// ( / /= )
// ( % %= )
// == !=
// ()
// [] read only


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

//........................................................


//template <typename T>
//static int get_value(T& v, std::istream& in=std::cin, std::ostream& out = std::cout) {
//	while (!in.good()) {
//		if (in.bad()) throw std::runtime_error("Fatal error");
//		if (in.eof()) return 1;
//
//		in.clear();
//		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//		out << "Invalid input. Please, try again from incorrect value" << std::endl;
//		in >> v;
//	}
//
//	return 0;
//}
