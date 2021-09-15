#ifndef H_HYPOCYCLOID
#define H_HYPOCYCLOID

typedef struct Point {
	double x, y;
} Point;

class Hypocycloid {
public:
	enum class Type {
		ORDINARY,
		SHORT,
		LONG
	};


	// constructors
	Hypocycloid();
	Hypocycloid(Hypocycloid& hc);
	Hypocycloid(double R_large, double R_small);
	Hypocycloid(double R_large, double R_small, double Dist);

	// getters
	double get_R_large() const;
	double get_R_small() const;
	double get_Dist() const;

	// setters
	Hypocycloid& set_R_large(double R_large);
	Hypocycloid& set_R_small(double R_small);
	Hypocycloid& set_Dist(double Dist);

	// tasks
	Type   calc_type() const;
	Point  calc_point(double t) const;
	double calc_S_sectorial(double t) const;
	double calc_R_curvature(double t) const;


private:
	double R_large;
	double R_small;
	double Dist; // Distance between the center of smaller circle and 
				 // starting point in starting position

	// auxilliary
	static const double EPSILON;

	static bool cmp_doubles(double a, double b);
};

#endif

