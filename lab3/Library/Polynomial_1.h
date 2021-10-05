#ifndef H_POLYNOMIAL
#define H_POLYNOMIAL

// TODO
// Gorner's scheme
// Root search

// static implementation without operators overloading
class Polynomial_1 {
public:
	static const int MAX_DEG = 10;

	// Constructors
	Polynomial_1() noexcept; // Create polynomial "0"
	explicit Polynomial_1(int deg, const double factors[] = nullptr);

	// Operations
	friend std::istream& input(std::istream& in, Polynomial_1& p); // ">>"
	friend std::ostream& output(std::ostream& out, const Polynomial_1& p) noexcept; // "<<"

	Polynomial_1& sum(const Polynomial_1& p) noexcept; // "+="
	friend Polynomial_1 sum(const Polynomial_1& p1, const Polynomial_1& p2) noexcept; // "+"

	Polynomial_1& div(double b) noexcept; // "/="
	friend Polynomial_1 div(const Polynomial_1& p, double b) noexcept; // "/"

	// return the rest as null-degree polynomial
	Polynomial_1& mod(double b) noexcept; // "%="
	friend Polynomial_1 mod(const Polynomial_1& p, double b) noexcept; // "%"
	
	Polynomial_1& derivative() noexcept;
	friend Polynomial_1 derivative(const Polynomial_1& p) noexcept;

	bool equals(const Polynomial_1& p) const noexcept;

	double value(double x) const noexcept; // "()"
	int root(double a, double b, double& res) const noexcept;
	


private:
	int m_deg;
	double m_factors[MAX_DEG + 1];
};


bool cmp_doubles(double a, double b) noexcept;

template <typename T>
static int get_value(T& v, std::istream& in=std::cin, std::ostream& out = std::cout) {
	in >> v;

	while (!in.good()) {
		if (in.bad()) throw std::runtime_error("Fatal error");
		if (in.eof()) return 1;

		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		out << "Invalid input. Please, try again from incorrect value" << std::endl;
		in >> v;
	}

	return 0;
}
#endif
