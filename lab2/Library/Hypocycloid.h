#ifndef H_HYPOCYCLOID
#define H_HYPOCYCLOID

typedef struct Point {
	double x, y;
} Point;

class Hypocycloid {
public:
	static const double EPSILON;
	enum class Type {
		ORDINARY,
		SHORT,
		LONG
	};


	// constructors
	Hypocycloid() noexcept;
	Hypocycloid(Hypocycloid& hc) noexcept;
	Hypocycloid(double R_large, double R_small);
	Hypocycloid(double R_large, double R_small, double Dist);

	// getters
	double get_R_large() const noexcept;
	double get_R_small() const noexcept;
	double get_Dist() const noexcept;

	// setters
	Hypocycloid& set_R_large(double R_large);
	Hypocycloid& set_R_small(double R_small);
	Hypocycloid& set_Dist(double Dist);

	// tasks
	Type   calc_type() const noexcept;
	Point  calc_point(double t) const noexcept;
	double calc_S_sectorial(double t) const noexcept;
	double calc_R_curvature(double t) const noexcept;


private:
	double R_large;
	double R_small;
	double Dist; // Distance between the center of smaller circle and 
				 // starting point in starting position

	// auxilliary

	static bool cmp_doubles(double a, double b) noexcept;
};

#endif