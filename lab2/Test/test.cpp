#include "pch.h"

#include <tchar.h>

#include "..\Library\Hypocycloid.h"
#include "gtest\gtest.h"

// Constructors
TEST(Constructors, DefaultConstructor) {
	Hypocycloid hc_1;
	EXPECT_NEAR(hc_1.get_R_large(), 1., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.get_R_small(), 0.25, Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.get_Dist(), 0.25, Hypocycloid::EPSILON);
}

TEST(Constructors, ParametrizedConstructor_1) {
	Hypocycloid hc_1(2., 1., 0.25);
	EXPECT_NEAR(hc_1.get_R_large(), 2., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.get_R_small(), 1., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.get_Dist(), 0.25, Hypocycloid::EPSILON);

	EXPECT_THROW({
		Hypocycloid hc_2(-1., 1., 0.25);
		}, std::logic_error);
	EXPECT_THROW({
		Hypocycloid hc_3(2., -1., 0.25);
		}, std::logic_error);
	EXPECT_THROW({
		Hypocycloid hc_4(2., 1., -0.25);
		}, std::logic_error);
	EXPECT_THROW({
		Hypocycloid hc_5(1., 2., 0.25);
		}, std::logic_error);
}

TEST(Constructors, ParametrizedConstructor_2) {
	Hypocycloid hc_1(2., 1.);
	EXPECT_NEAR(hc_1.get_R_large(), 2., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.get_R_small(), 1., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.get_Dist(), 1., Hypocycloid::EPSILON);

	EXPECT_THROW({
		Hypocycloid hc_2(-1., 1.);
		}, std::logic_error);
	EXPECT_THROW({
		Hypocycloid hc_3(2., -1.);
		}, std::logic_error);
	EXPECT_THROW({
		Hypocycloid hc_4(1., 2.);
		}, std::logic_error);
}

TEST(Constructors, CopyConstructor) {
	Hypocycloid hc_1((Hypocycloid()));
	EXPECT_NEAR(hc_1.get_R_large(), 1., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.get_R_small(), 0.25, Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.get_Dist(), 0.25, Hypocycloid::EPSILON);

	Hypocycloid hc_2(Hypocycloid(2., 1., 0.25));
	EXPECT_NEAR(hc_2.get_R_large(), 2., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_2.get_R_small(), 1., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_2.get_Dist(), 0.25, Hypocycloid::EPSILON);
}


// Getters
TEST(Getters, AllGetters) {
	Hypocycloid hc_1(2., 1., 0.25);
	EXPECT_NEAR(hc_1.get_R_large(), 2., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.get_R_small(), 1., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.get_Dist(), 0.25, Hypocycloid::EPSILON);

	Hypocycloid hc_2(4., 1., 0.5);
	EXPECT_NEAR(hc_2.get_R_large(), 4., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_2.get_R_small(), 1., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_2.get_Dist(), 0.5, Hypocycloid::EPSILON);
}

// Setters
TEST(Setters, Set_R_large) {
	Hypocycloid hc_1(2., 1., 0.25);

	EXPECT_THROW({
		hc_1.set_R_large(-1.);
		}, std::logic_error);
	EXPECT_THROW({
		hc_1.set_R_large(0.5);
		}, std::logic_error);


	hc_1.set_R_large(4);
	EXPECT_NEAR(hc_1.get_R_large(), 4, Hypocycloid::EPSILON);
}

TEST(Setters, Set_R_small) {
	Hypocycloid hc_1(2., 1., 0.25);

	EXPECT_THROW({
		hc_1.set_R_small(-1.);
		}, std::logic_error);
	EXPECT_THROW({
		hc_1.set_R_small(4.);
		}, std::logic_error);


	hc_1.set_R_small(0.5);
	EXPECT_NEAR(hc_1.get_R_small(), 0.5, Hypocycloid::EPSILON);
}

TEST(Setters, Set_Dist) {
	Hypocycloid hc_1(2., 1., 0.25);

	EXPECT_THROW({
		hc_1.set_Dist(-1.);
		}, std::logic_error);

	hc_1.set_Dist(0.5);
	EXPECT_NEAR(hc_1.get_Dist(), 0.5, Hypocycloid::EPSILON);
}

// tasks
TEST(Tasks, calc_type) {
	Hypocycloid hc_1(2., 1., 0.25);
	Hypocycloid hc_2(2., 1., 1.);
	Hypocycloid hc_3(2., 1., 1.25);

	EXPECT_EQ(hc_1.calc_type(), Hypocycloid::Type::SHORT);
	EXPECT_EQ(hc_2.calc_type(), Hypocycloid::Type::ORDINARY);
	EXPECT_EQ(hc_3.calc_type(), Hypocycloid::Type::LONG);
}

TEST(Tasks, calc_point) {
	Point p;


	// SHORT type
	Hypocycloid hc_1(2., 1., 0.25);

	// p(0) = (1.25, 0)
	p = hc_1.calc_point(0);
	EXPECT_NEAR(p.x, 1.25, Hypocycloid::EPSILON);
	EXPECT_NEAR(p.y, 0., Hypocycloid::EPSILON);

	// p(2) = (-0.520183, 0.681973)
	p = hc_1.calc_point(2);
	EXPECT_NEAR(p.x, -0.520183, Hypocycloid::EPSILON);
	EXPECT_NEAR(p.y, 0.681973, Hypocycloid::EPSILON);

	// p(-5) = (0.354577, 0.719193)
	p = hc_1.calc_point(-5);
	EXPECT_NEAR(p.x, 0.354577, Hypocycloid::EPSILON);
	EXPECT_NEAR(p.y, 0.719193, Hypocycloid::EPSILON);


	// ORDINARY type
	Hypocycloid hc_2(4., 2., 2.);

	// p(0) = (4., 0.)
	p = hc_2.calc_point(0);
	EXPECT_NEAR(p.x, 4., Hypocycloid::EPSILON);
	EXPECT_NEAR(p.y, 0., Hypocycloid::EPSILON);

	// p(2.5) = (-3.204574, 0.)
	p = hc_2.calc_point(2.5);
	EXPECT_NEAR(p.x, -3.204574, Hypocycloid::EPSILON);
	EXPECT_NEAR(p.y, 0., Hypocycloid::EPSILON);

	// p(-3.8) = (-3.163870, 0.)
	p = hc_2.calc_point(-3.8);
	EXPECT_NEAR(p.x, -3.163870, Hypocycloid::EPSILON);
	EXPECT_NEAR(p.y, 0., Hypocycloid::EPSILON);


	// LONG type
	Hypocycloid hc_3(3., 2.5, 2.7);

	// p(0) = (3.2, 0.)
	p = hc_3.calc_point(0);
	EXPECT_NEAR(p.x, 3.2, Hypocycloid::EPSILON);
	EXPECT_NEAR(p.y, 0., Hypocycloid::EPSILON);

	// p(1.3) = (2.743002, -0.212338)
	p = hc_3.calc_point(1.3);
	EXPECT_NEAR(p.x, 2.743002, Hypocycloid::EPSILON);
	EXPECT_NEAR(p.y, -0.212338, Hypocycloid::EPSILON);

	// p(-1.1) = (2.861721, 0.143616)
	p = hc_3.calc_point(-1.1);
	EXPECT_NEAR(p.x, 2.861721, Hypocycloid::EPSILON);
	EXPECT_NEAR(p.y, 0.143616, Hypocycloid::EPSILON);
}

TEST(Tasks, calc_S_sectorial) {
	// SHORT type
	Hypocycloid hc_1(2., 1., 0.25);
	EXPECT_NEAR(hc_1.calc_S_sectorial(0.), 0., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.calc_S_sectorial(-1.1), -0.515625, Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.calc_S_sectorial(1.7), 0.796875, Hypocycloid::EPSILON);

	// ORDINARY type
	Hypocycloid hc_2(4., 2., 2.);
	EXPECT_NEAR(hc_2.calc_S_sectorial(0.), 0., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_2.calc_S_sectorial(-1.1), 0., Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_2.calc_S_sectorial(1.7), 0., Hypocycloid::EPSILON);

	// LONG type
	Hypocycloid hc_3(3., 2.5, 2.7);
	EXPECT_NEAR(hc_3.calc_S_sectorial(0), 0, Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_3.calc_S_sectorial(2.2), -1.545170, Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_3.calc_S_sectorial(-2.3), 1.556779, Hypocycloid::EPSILON);
}

TEST(Tasks, calc_R_curvature) {
	// SHORT type
	Hypocycloid hc_1(2., 1., 0.25);
	EXPECT_NEAR(hc_1.calc_R_curvature(0.), 0.45, Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.calc_R_curvature(-1.1), 1.685693, Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_1.calc_R_curvature(1.7), 2.050219, Hypocycloid::EPSILON);
	
	// ORDINARY type
	Hypocycloid hc_2(4., 2., 2.);
	EXPECT_NEAR(hc_2.calc_R_curvature(0.), std::numeric_limits<double>::max(), Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_2.calc_R_curvature(-1.1), std::numeric_limits<double>::max(), Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_2.calc_R_curvature(1.7), std::numeric_limits<double>::max(), Hypocycloid::EPSILON);

	// LONG type
	Hypocycloid hc_3(3., 2.5, 2.7);
	EXPECT_NEAR(hc_3.calc_R_curvature(0.), 0.002631, Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_3.calc_R_curvature(2.2), 2.683760, Hypocycloid::EPSILON);
	EXPECT_NEAR(hc_3.calc_R_curvature(-2.3), 2.715381, Hypocycloid::EPSILON);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}