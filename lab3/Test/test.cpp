#ifdef _MSC_VER

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif

#include <string>

#include "pch.h"
#include "../Library/Polynomial_1.h"
#include "gtest\gtest.h"

typedef Polynomial_1 P;

P poly(int deg, std::initializer_list<double> f_list);

//------/ Constructors /-----------
TEST(Constructors, Default) {
	P p;

	P q = poly(0, { 0 });
	EXPECT_TRUE(p.equals(q));
}

TEST(Constructors, Constant) {
	// 1. Zero constant
	P p_1(0);

	P q_1 = poly(0, { 0 });
	EXPECT_TRUE(p_1.equals(q_1));

	// 2. Not zero constant
	P p_2(4);

	P q_2 = poly(0, { 4 });
	EXPECT_TRUE(p_2.equals(q_2));
}

TEST(Constructors, Polynomial) {
	// 1. Zero constant
	P p_1 = poly(0, { 0 });

	P q_1(0);
	EXPECT_TRUE(p_1.equals(q_1));

	// 2. Not zero constant
	P p_2 = poly(0, { -2 });

	P q_2(-2);
	EXPECT_TRUE(p_2.equals(q_2));

	// 3. Too big degree
	EXPECT_THROW({
		P p_3 = poly(P::MAX_DEG + 1, { 0 });
	}, std::logic_error);

	// 4. Negative degree
	EXPECT_THROW({
		P p_4 = poly(-3, { 1, 2, 3});
	}, std::logic_error);

	// 5. Leading zeroes
	P p_5 = poly(3, { 1, 2, 0, 0 });
	P q_5 = poly(1, { 1, 2 });
	EXPECT_TRUE(p_5.equals(q_5));

	// 6. All zeroes
	P p_6 = poly(3, { 0, 0, 0, 0 });
	P q_6(0);
	EXPECT_TRUE(p_6.equals(q_6));
}

TEST(Constructors, Monomial) {
	// 1. Monomial
	P p_1(3, 4);

	P q_1 = poly(3, { 0,0,0,4 });
	EXPECT_TRUE(p_1.equals(q_1));

	// 2. Constant monomial
	P p_2(0, -2);

	P q_2(-2);
	EXPECT_TRUE(p_2.equals(q_2));

	// 3. Too big degree
	EXPECT_THROW({
		P p_3 = poly(P::MAX_DEG + 1, { 0 });
		}, std::logic_error);

	// 4. Negative degree
	EXPECT_THROW({
		P p_4 = poly(-2, { 1, 2});
		}, std::logic_error);
}


//------/ Input/Output /-----------

TEST(IO, Input) {
	// 1. Correct input
	std::istringstream istr_1("3 1 2 3 4\n");
	P p_1;
	p_1.input(istr_1);

	P q_1 = poly(3, { 1, 2, 3, 4 });
	EXPECT_TRUE(p_1.equals(q_1));

	// 2. EOF input
	std::istringstream istr_2("3 1 2 3");

	P p_2;
	EXPECT_THROW({
		p_2.input(istr_2);
	}, std::iostream::failure);

	// 3. Fail input
	std::istringstream istr_3("3 1 a");

	P p_3;
	EXPECT_THROW({
		p_3.input(istr_3);
	}, std::iostream::failure);

	// 4. Too big degree
	std::istringstream istr_4(std::to_string(int(P::MAX_DEG + 1)));

	P p_4;
	EXPECT_THROW({
		p_4.input(istr_4);
	}, std::iostream::failure);

	// 5. Negative degree
	std::istringstream istr_5(std::to_string(int(P::MAX_DEG + 1)));

	P p_5;
	EXPECT_THROW({
		p_5.input(istr_5);
	}, std::iostream::failure);
}

TEST(IO, Output) {
	// 1. Polynomial
	std::ostringstream ostr_1;

	P p_1 = poly(2, { 1, -1, 1 });
	p_1.output(ostr_1);

	EXPECT_EQ(ostr_1.str(), "1-x+x^2\n");

	// 2. Zero factors + negative factors
	std::ostringstream ostr_2;

	P p_2 = poly(2, { 1, 0, -2 });
	p_2.output(ostr_2);

	EXPECT_EQ(ostr_2.str(), "1+0x-2x^2\n");

	// 3. Constant
	std::ostringstream ostr_3;

	P p_3 = poly(0, { -3 });
	p_3.output(ostr_3);

	EXPECT_EQ(ostr_3.str(), "-3\n");
}


//------/ Operations /-----------

TEST(Operations, Sum) {
	// 1. Equal degrees
	P a_1 = poly(2, { 3, 2, 1 });
	P b_1 = poly(2, { 3, -2, 1 });

	P r_1 = poly(2, { 6, 0, 2 });

	P c_1;
	a_1.sum(b_1, c_1);
	EXPECT_TRUE(c_1.equals(r_1));
	
	a_1.sum(b_1);
	EXPECT_TRUE(a_1.equals(r_1));

	// 2. Different degrees
	P a_2 = poly(2, { 3, 2, 1 });
	P b_2 = poly(4, { 1, -1, -2, 3, 4 });

	P r_2 = poly(4, { 4, 1, -1, 3, 4 });

	P c_2;
	a_2.sum(b_2, c_2);
	EXPECT_TRUE(c_2.equals(r_2));

	a_2.sum(b_2);
	EXPECT_TRUE(a_2.equals(r_2));

	// 3. Decreasing degrees
	P a_3 = poly(4, { 3, 2, 1, -3, -4});
	P b_3 = poly(4, { 1, -1, -2, 3, 4 });

	P r_3 = poly(2, { 4, 1, -1 });

	P c_3;
	a_3.sum(b_3, c_3);
	EXPECT_TRUE(c_3.equals(r_3));

	a_3.sum(b_3);
	EXPECT_TRUE(a_3.equals(r_3));
}

TEST(Operations, Sub) {
	// 1. Equal degrees
	P a_1 = poly(2, { 3, 2, 1 });
	P b_1 = poly(2, { 2, 0, -2});

	P r_1 = poly(2, { 1, 2, 3 });

	P c_1;
	a_1.sub(b_1, c_1);
	EXPECT_TRUE(c_1.equals(r_1));

	a_1.sub(b_1);
	EXPECT_TRUE(a_1.equals(r_1));

	// 2. Different degrees
	P a_2 = poly(2, { 3, 2, 1 });
	P b_2 = poly(4, { 1, -1, -2, 3, 4 });

	P r_2 = poly(4, { 2, 3, 3, -3, -4 });

	P c_2;
	a_2.sub(b_2, c_2);
	EXPECT_TRUE(c_2.equals(r_2));

	a_2.sub(b_2);
	EXPECT_TRUE(a_2.equals(r_2));

	// 3. Decreasing degrees
	P a_3 = poly(4, { 3, 2, 1, 4, 5 });
	P b_3 = poly(4, { 1, -1, -2, 4, 5 });

	P r_3 = poly(2, { 2, 3, 3 });

	P c_3;
	a_3.sub(b_3, c_3);
	EXPECT_TRUE(c_3.equals(r_3));

	a_3.sub(b_3);
	EXPECT_TRUE(a_3.equals(r_3));
}

TEST(Operations, Mult) {
	// 1. Zero
	P a_1 = poly(2, { 3, 2, 1 });
	P b_1(0);

	P r_1(0);

	P c_1;
	a_1.mult(b_1, c_1);
	EXPECT_TRUE(c_1.equals(r_1));

	a_1.mult(b_1);
	EXPECT_TRUE(a_1.equals(r_1));

	// 2. Constant
	P a_2 = poly(3, { -2, 3, 3, -4 });
	P b_2(-3);

	P r_2 = poly(3, { 6, -9, -9, 12 });

	P c_2;
	a_2.mult(b_2, c_2);
	EXPECT_TRUE(c_2.equals(r_2));

	a_2.mult(b_2);
	EXPECT_TRUE(a_2.equals(r_2));

	// 3. Monomial
	P a_3 = poly(2, { -3, 1, 4});
	P b_3(2, -2);

	P r_3 = poly(4, { 0, 0, 6, -2, -8 });

	P c_3;
	a_3.mult(b_3, c_3);
	EXPECT_TRUE(c_3.equals(r_3));

	a_3.mult(b_3);
	EXPECT_TRUE(a_3.equals(r_3));

	// 4. Polynomial
	P a_4 = poly(1, { -1, 1 });
	P b_4 = poly(1, { 1, 1 });

	P r_4 = poly(2, { -1, 0, 1 });

	P c_4;
	a_4.mult(b_4, c_4);
	EXPECT_TRUE(c_4.equals(r_4));

	a_4.mult(b_4);
	EXPECT_TRUE(a_4.equals(r_4));

	// 5. Too big degrees
	P a_5(P::MAX_DEG - 1, 1);
	P b_5(2, 1);

	P c_5;
	EXPECT_THROW({
		a_5.mult(b_5, c_5);
	}, std::logic_error);

	EXPECT_THROW({
		a_5.mult(b_5);
	}, std::logic_error);
}

TEST(Operations, Div) {
	// 1. a is Zero
	P a_1(0);
	P b_1 = poly(1, { 2, 3 });

	P r_1(0);

	P c_1;
	a_1.div(b_1, c_1);
	EXPECT_TRUE(c_1.equals(r_1));

	a_1.div(b_1);
	EXPECT_TRUE(a_1.equals(r_1));

	// 2. b is Zero
	P a_2 = poly(2, { 1, 1, 1 });
	P b_2(0);

	P c_2;
	EXPECT_THROW({
		a_2.div(b_2, c_2);
	}, std::logic_error);

	EXPECT_THROW({
		a_2.div(b_2);
	}, std::logic_error);

	// 3. a is Constant
	P a_3(4);
	P b_3 = poly(1, { 2, 3 });

	P r_3(0);

	P c_3;
	a_3.div(b_3, c_3);
	EXPECT_TRUE(c_3.equals(r_3));

	a_3.div(b_3);
	EXPECT_TRUE(a_3.equals(r_3));

	// 4. b is Constant
	P a_4 = poly(3, { 3, -12, 0, -42 });
	P b_4(-3);

	P r_4 = poly(3, { -1, 4, 0, 14 });

	P c_4;
	a_4.div(b_4, c_4);
	EXPECT_TRUE(c_4.equals(r_4));

	a_4.div(b_4);
	EXPECT_TRUE(a_4.equals(r_4));

	// 5. Polynomial
	P a_5 = poly(3, { 1, -12, 0, -42 });
	P b_5 = poly(1, { 3, 1});

	P r_5 = poly(2, { -390, 126, -42 });

	P c_5;
	a_5.div(b_5, c_5);
	EXPECT_TRUE(c_5.equals(r_5));

	a_5.div(b_5);
	EXPECT_TRUE(a_5.equals(r_5));
}

TEST(Operations, Mod) {
	// 1. a is Zero
	P a_1(0);
	P b_1 = poly(1, { 2, 3 });

	P r_1(0);

	P c_1;
	a_1.mod(b_1, c_1);
	EXPECT_TRUE(c_1.equals(r_1));

	a_1.mod(b_1);
	EXPECT_TRUE(a_1.equals(r_1));

	// 2. b is Zero
	P a_2 = poly(2, { 1, 1, 1 });
	P b_2(0);

	P c_2;
	EXPECT_THROW({
		a_2.mod(b_2, c_2);
		}, std::logic_error);

	EXPECT_THROW({
		a_2.mod(b_2);
		}, std::logic_error);

	// 3. a is Constant
	P a_3(4);
	P b_3 = poly(1, { 2, 3 });

	P r_3(4);

	P c_3;
	a_3.mod(b_3, c_3);
	EXPECT_TRUE(c_3.equals(r_3));

	a_3.mod(b_3);
	EXPECT_TRUE(a_3.equals(r_3));

	// 4. b is Constant
	P a_4 = poly(3, { 3, -12, 0, -42 });
	P b_4(-3);

	P r_4(0);

	P c_4;
	a_4.mod(b_4, c_4);
	EXPECT_TRUE(c_4.equals(r_4));

	a_4.mod(b_4);
	EXPECT_TRUE(a_4.equals(r_4));

	// 5. a and b are Constants
	P a_5(6);
	P b_5(-3);

	P r_5(0);

	P c_5;
	a_5.mod(b_5, c_5);
	EXPECT_TRUE(c_5.equals(r_5));

	a_5.mod(b_5);
	EXPECT_TRUE(a_5.equals(r_5));

	// 6. Polynomial
	P a_6 = poly(3, { 1, -12, 0, -42 });
	P b_6 = poly(1, { 3, 1 });

	P r_6(1171);

	P c_6;
	a_6.mod(b_6, c_6);
	EXPECT_TRUE(c_6.equals(r_6));

	a_6.mod(b_6);
	EXPECT_TRUE(a_6.equals(r_6));
}

TEST(Operations, Derivative) {
	// 1. Zero
	P a_1(0);

	P r_1(0);

	P c_1;
	a_1.derivative(c_1);
	EXPECT_TRUE(c_1.equals(r_1));

	a_1.derivative();
	EXPECT_TRUE(a_1.equals(r_1));

	// 2. Constant
	P a_2(4);

	P r_2(0);

	P c_2;
	a_2.derivative(c_2);
	EXPECT_TRUE(c_2.equals(r_2));

	a_2.derivative();
	EXPECT_TRUE(a_2.equals(r_2));

	// 3. Polinomial

	P a_3 = poly(3, { 42, -6, 8, 12 });
	
	P r_3 = poly(2, { -6, 16, 36 });

	P c_3;
	a_3.derivative(c_3);
	EXPECT_TRUE(c_3.equals(r_3));

	a_3.derivative();
	EXPECT_TRUE(a_3.equals(r_3));
}

//------/ Tasks /------------------
TEST(Tasks, Equal) {
	// 1. Equal
	P a_1 = poly(3, { 42, -6, 8, 12 });
	P b_1 = poly(3, { 42, -6, 8, 12 });

	EXPECT_TRUE(a_1.equals(b_1));

	// 2. Different degrees
	P a_2 = poly(3, { 42, -6, 8, 12 });
	P b_2 = poly(2, { 42, -6, 8});

	EXPECT_FALSE(a_2.equals(b_2));

	// 3. Constants
	P a_3(4);
	P b_3(0);

	EXPECT_FALSE(a_3.equals(b_3));

	// 4. Different factors
	P a_4 = poly(3, { 42, -6, 8, 12 });
	P b_4 = poly(3, { 42, 2, 8, -1 });

	EXPECT_FALSE(a_4.equals(b_4));
}

TEST(Tasks, Value) {
	// 1. Zero
	P p_1(0);

	EXPECT_TRUE(cmp_doubles(p_1.value(2), 0));
	EXPECT_TRUE(cmp_doubles(p_1.value(0), 0));
	EXPECT_TRUE(cmp_doubles(p_1.value(-3), 0));

	// 2. Constant
	P p_2(5);

	EXPECT_TRUE(cmp_doubles(p_2.value(2), 5));
	EXPECT_TRUE(cmp_doubles(p_2.value(0), 5));
	EXPECT_TRUE(cmp_doubles(p_2.value(-3), 5));
	
	// 3. Polinomial 1
	P p_3 = poly(3, { 1, 0, -2, 3 });

	EXPECT_TRUE(cmp_doubles(p_3.value(2), 17));
	EXPECT_TRUE(cmp_doubles(p_3.value(0), 1));
	EXPECT_TRUE(cmp_doubles(p_3.value(-3), -98));

	// 4. Polinomial 2
	P p_4 = poly(4, { -1, 6, 0, 0, -1 });

	EXPECT_TRUE(cmp_doubles(p_4.value(-6), -1333));
	EXPECT_TRUE(cmp_doubles(p_4.value(4), -233));
	EXPECT_TRUE(cmp_doubles(p_4.value(-2), -29));
}

TEST(Tasks, Root) {
	// 1. Zero
	P p_1(0);

	double root_1 = 0;

	p_1.root(1, 3, root_1);
	EXPECT_TRUE(cmp_doubles(root_1, 1));


	// 2. Polynonomial 1
	P p_2 = poly(2, { 0, -2, 1});

	double root_2 = 0;

	p_2.root(1, 3, root_2);
	EXPECT_TRUE(cmp_doubles(root_2, 2));

	p_2.root(0, 1, root_2);
	EXPECT_TRUE(cmp_doubles(root_2, 0));

	p_2.root(1, 2, root_2);
	EXPECT_TRUE(cmp_doubles(root_2, 2));


	EXPECT_EQ(p_2.root(-1, 3, root_2), 1);
	EXPECT_EQ(p_2.root(0.5, 1.5, root_2), 1);

	// 3. Polynomial 2
	P p_3 = poly(3, { 1, 0, -2, 1 });

	double root_3 = 0;

	p_3.root(-1, 0, root_3);
	EXPECT_TRUE(cmp_doubles(root_3, -0.61803398));

	p_3.root(0, 1.5, root_3);
	EXPECT_TRUE(cmp_doubles(root_3, 1));

	p_3.root(-1, 2, root_3);
	EXPECT_TRUE(cmp_doubles(root_3, 1));


	EXPECT_EQ(p_3.root(-1.5, -1, root_3), 1);

	// 4. Invalid interval
	P p_4 = poly(2, { 0, 2, -6 });

	double root_4 = 0;

	EXPECT_THROW({
		p_4.root(4, 2, root_4);
	}, std::logic_error);
}


int main(int argc, char* argv[]) {
	#ifdef _CRTDBG_MAP_ALLOC
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

P poly(int deg, std::initializer_list<double> f_list) {
	double* factors = new double[f_list.size()];
	for (auto it = f_list.begin(); it != f_list.end(); ++it) {
		factors[it - f_list.begin()] = *it;
	}

	try {
		P p(deg, factors);
		return p;
	}
	catch (std::exception& err) {
		delete[] factors;
		throw;
	}
}