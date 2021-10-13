#ifdef _MSC_VER

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif

#include "pch.h"
#include "../Library/Polynomial_1.h"
#include "gtest\gtest.h"

typedef Polynomial_1 P;

P poly(int deg, std::initializer_list<double> f_list) {
	double* factors = new double[f_list.size()];
	for (auto it = f_list.begin(); it != f_list.end(); ++it)	{
		factors[it - f_list.begin()] = *it;
	}

	P p(deg, factors);
	delete[] factors;
	return p;
}

//TEST(General, General) {
//	P p = poly(2, {-1, 0, 1 });
//	P q = poly(1, { 1, 1 });
//	p.div(q);
//	p.output(std::cout);
//}

TEST(Constructors, Default) {
	P p_1;

	P q_1 = poly(0, { 0 });
	EXPECT_TRUE(p_1.equals(q_1));
}

TEST(Constructors, Constant) {
	// Polynomial equals "0"
	P p_1(0);

	P q_1 = poly(0, { 0 });
	EXPECT_TRUE(p_1.equals(q_1));
	
	//// Polynomial with zero factors
	//P P_2(3);
	//double fQ_2[] = { 0, 0, 0, 0 };
	//P Q_2(3, fQ_2);
	//EXPECT_TRUE(P_2.equals(Q_2));

	//// Too big degree
	//EXPECT_THROW({
	//	P P_3(P::MAX_DEG + 1);
	//}, std::logic_error);
}
//
//
//TEST(Operations, Sum) {
//	// check sum for different degrees
//	double fP_1[] = { 3, -1, 0, -1, 0 };
//	P P_1(4, fP_1);
//
//	double fQ_1[] = { 1, 2 };
//	P Q_1(1, fQ_1);
//
//	double fS_1[] = { 3, -1, 0, 0, 2};
//	P S_1(4, fS_1);
//
//	P R_1 = sum(P_1, Q_1);
//	EXPECT_TRUE(R_1.equals(S_1));
//
//	P_1.sum(Q_1);
//	EXPECT_TRUE(P_1.equals(S_1));
//
//	// check sum if greatest factor equals zero (right behavior: dont decrease degree)
//	double fP_2[] = { 3, -1, 0, -1, 0 };
//	P P_2(4, fP_2);
//
//	double fQ_2[] = { -3, 0, 1, 0, -1 };
//	P Q_2(4, fQ_2);
//
//	double fS_2[] = { 0, -1, 1, -1, -1 };
//	P S_2(4, fS_2);
//	
//	P R_2 = sum(P_2, Q_2);
//	EXPECT_TRUE(R_2.equals(S_2));
//
//	P_2.sum(Q_2);
//	EXPECT_TRUE(P_2.equals(S_2));
//}
//
//TEST(Operations, Div) {
//	// check decreasing of degree (if degree doesn't equal to zero)
//	double fP_1[] = { 1, -12, 0, -42 };
//	P P_1(3, fP_1);
//
//	double b_1 = 3;
//
//	double fD_1[] = { 1, -9, -27 };
//	P D_1(2, fD_1);
//
//	P R_1 = div(P_1, b_1);
//	EXPECT_TRUE(R_1.equals(D_1));
//
//	P_1.div(b_1);
//	EXPECT_TRUE(P_1.equals(D_1));
//
//	// if degree equals to zero
//	double fP_2[] = {4};
//	P P_2(0, fP_2);
//
//	double b_2 = 3;
//
//	double fD_2[] = { 0 };
//	P D_2(0, fD_2);
//
//	P R_2 = div(P_2, b_2);
//	EXPECT_TRUE(R_2.equals(D_2));
//
//	P_2.div(b_2);
//	EXPECT_TRUE(P_2.equals(D_2));
//}
//
//TEST(Operations, Mod) {
//	//
//	double fP_1[] = { 1, -12, 0, -42 };
//	P P_1(3, fP_1);
//
//	double b_1 = 3;
//
//	double fM_1[] = { -123 };
//	P M_1(0, fM_1);
//
//	P R_1 = mod(P_1, b_1);
//	EXPECT_TRUE(R_1.equals(M_1));
//
//	P_1.mod(b_1);
//	EXPECT_TRUE(P_1.equals(M_1));
//
//	// if degree equals to zero
//	double fP_2[] = { 4 };
//	P P_2(0, fP_2);
//
//	double b_2 = 3;
//
//	double fM_2[] = { 4 };
//	P M_2(0, fM_2);
//
//	P R_2 = mod(P_2, b_2);
//	EXPECT_TRUE(R_2.equals(M_2));
//
//	P_2.mod(b_2);
//	EXPECT_TRUE(P_2.equals(M_2));
//}
//
//TEST(Operations, Derivative) {
//	//
//	double fP_1[] = { 1, -12, 0, -42 };
//	P P_1(3, fP_1);
//
//	double fD_1[] = { 3, -24, 0 };
//	P D_1(2, fD_1);
//
//	P R_1 = derivative(P_1);
//	EXPECT_TRUE(R_1.equals(D_1));
//
//	P_1.derivative();
//	EXPECT_TRUE(P_1.equals(D_1));
//
//
//	// Zero degree
//	double fP_2[] = { 20 };
//	P P_2(0, fP_2);
//
//	double fD_2[] = { 0 };
//	P D_2(0, fD_2);
//
//	P R_2 = derivative(P_2);
//	EXPECT_TRUE(R_2.equals(D_2));
//
//	P_2.derivative();
//	EXPECT_TRUE(P_2.equals(D_2));
//}
//
//TEST(Tasks, Value) {
//	//
//	double fP_1[] = { 3, -2, 0, 1 };
//	P P_1(3, fP_1);
//
//	double x_1 = 2;
//	EXPECT_TRUE(cmp_doubles(P_1.value(x_1), 17));
//
//	double x_2 = 0;
//	EXPECT_TRUE(cmp_doubles(P_1.value(x_2), 1));
//
//	double x_3 = -3;
//	EXPECT_TRUE(cmp_doubles(P_1.value(x_3), -98));
//
//
//	//
//	double fQ_1[] = { -1, 0, 0, 6, -1 };
//	P Q_1(4, fQ_1);
//
//	double y_1 = -6;
//	EXPECT_TRUE(cmp_doubles(Q_1.value(y_1), -1333));
//
//	double y_2 = 4;
//	EXPECT_TRUE(cmp_doubles(Q_1.value(y_2), -233));
//
//	double y_3 = -2;
//	EXPECT_TRUE(cmp_doubles(Q_1.value(y_3), -29));
//}
//
//TEST(Tasks, Root) {
//	//
//	double fP_1[] = { 1, -2, 0 };
//	P P_1(2, fP_1);
//
//	double root_1;
//	int status_1;
//
//	P_1.root(1, 3, root_1);
//	EXPECT_TRUE(cmp_doubles(root_1, 2));
//
//	P_1.root(0, 1, root_1);
//	EXPECT_TRUE(cmp_doubles(root_1, 0));
//
//	P_1.root(1, 2, root_1);
//	EXPECT_TRUE(cmp_doubles(root_1, 2));
//
//	status_1 = P_1.root(-1, 3, root_1);
//	EXPECT_EQ(status_1, 1);
//
//	status_1 = P_1.root(0.5, 1.5, root_1);
//	EXPECT_EQ(status_1, 1);
//
//	//
//	double fP_2[] = { 1, -2, 0, 1 };
//	P P_2(3, fP_2);
//
//	double root_2;
//	int status_2;
//	P_2.root(-1, 0, root_2);
//	EXPECT_TRUE(cmp_doubles(root_2, -0.61803398));
//
//	P_2.root(0, 1.5, root_2);
//	EXPECT_TRUE(cmp_doubles(root_2, 1));
//
//	P_2.root(-1, 2, root_2);
//	EXPECT_TRUE(cmp_doubles(root_2, -0.61803398));
//
//	status_2 = P_2.root(-1.5, -1, root_2);
//	EXPECT_EQ(status_2, 1);
//
//
//}


int main(int argc, char* argv[]) {
	#ifdef _CRTDBG_MAP_ALLOC
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}