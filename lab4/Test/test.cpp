#ifdef _MSC_VER
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#include "pch.h"
#include "gtest\gtest.h"

#include "../Application/Queue.h"

//------/ Queue /------------------
TEST(Constructors, Default) {
	Queue<int> q;

	EXPECT_TRUE(q.empty());
	EXPECT_THROW(q.front(), std::runtime_error);
	EXPECT_THROW(q.back(), std::runtime_error);
	EXPECT_THROW(q.pop(), std::runtime_error);
}

TEST(Constructors, CopyConstructor) {
	Queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);

	Queue<int> p = q;

	EXPECT_EQ(q.front(), 1);
	EXPECT_NO_THROW(q.pop());
	EXPECT_EQ(q.front(), 2);
	EXPECT_NO_THROW(q.pop());
	EXPECT_EQ(q.front(), 3);
	EXPECT_NO_THROW(q.pop());
	EXPECT_TRUE(q.empty());

	EXPECT_EQ(p.front(), 1);
	EXPECT_NO_THROW(p.pop());
	EXPECT_EQ(p.front(), 2);
	EXPECT_NO_THROW(p.pop());
	EXPECT_EQ(p.front(), 3);
	EXPECT_NO_THROW(p.pop());
	EXPECT_TRUE(p.empty());
}

TEST(Constructors, MoveConstructor) {
	Queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);

	Queue<int> p = std::move(q);

	EXPECT_EQ(p.front(), 1);
	EXPECT_NO_THROW(p.pop());
	EXPECT_EQ(p.front(), 2);
	EXPECT_NO_THROW(p.pop());
	EXPECT_EQ(p.front(), 3);
	EXPECT_NO_THROW(p.pop());
	EXPECT_TRUE(p.empty());

	EXPECT_TRUE(q.empty());
}

TEST(Operators, CopyAssignment) {
	Queue<int> q;
	Queue<int> p;

	q.push(1);
	q.push(2);
	q.push(3);

	p.push(1);

	p = q;

	EXPECT_EQ(q.front(), 1);
	EXPECT_NO_THROW(q.pop());
	EXPECT_EQ(q.front(), 2);
	EXPECT_NO_THROW(q.pop());
	EXPECT_EQ(q.front(), 3);
	EXPECT_NO_THROW(q.pop());
	EXPECT_TRUE(q.empty());

	EXPECT_EQ(p.front(), 1);
	EXPECT_NO_THROW(p.pop());
	EXPECT_EQ(p.front(), 2);
	EXPECT_NO_THROW(p.pop());
	EXPECT_EQ(p.front(), 3);
	EXPECT_NO_THROW(p.pop());
	EXPECT_TRUE(p.empty());
}

TEST(Operators, MoveAssignment) {
	Queue<int> q;
	Queue<int> p;

	q.push(1);
	q.push(2);
	q.push(3);

	p.push(1);

	p = std::move(q);

	EXPECT_EQ(p.front(), 1);
	EXPECT_NO_THROW(p.pop());
	EXPECT_EQ(p.front(), 2);
	EXPECT_NO_THROW(p.pop());
	EXPECT_EQ(p.front(), 3);
	EXPECT_NO_THROW(p.pop());
	EXPECT_TRUE(p.empty());

	EXPECT_EQ(q.front(), 1);
	EXPECT_NO_THROW(q.pop());
	EXPECT_TRUE(p.empty());
}

TEST(Methods, PushAndPop) {
	Queue<int> q;

	q.push(1);
	q.push(2);

	EXPECT_EQ(q.front(), 1);
	EXPECT_EQ(q.size(), 2);
	EXPECT_NO_THROW(q.pop());

	EXPECT_EQ(q.front(), 2);
	EXPECT_EQ(q.size(), 1);
	EXPECT_NO_THROW(q.pop());

	q.push(3);

	EXPECT_EQ(q.front(), 3);
	EXPECT_EQ(q.size(), 1);
	EXPECT_NO_THROW(q.pop());

	EXPECT_TRUE(q.empty());
	EXPECT_THROW(q.front(), std::runtime_error);
	EXPECT_THROW(q.back(), std::runtime_error);
	EXPECT_THROW(q.pop(), std::runtime_error);
}

TEST(Methods, Empty) {
	Queue<int> q;

	// empty
	EXPECT_TRUE(q.empty());
	EXPECT_EQ(q.size(), 0);

	EXPECT_THROW(q.front(), std::runtime_error);
	EXPECT_THROW(q.back(), std::runtime_error);
	EXPECT_THROW(q.pop(), std::runtime_error);

	// pushed 1 item
	q.push(1);
	EXPECT_FALSE(q.empty());
	EXPECT_EQ(q.size(), 1);

	EXPECT_EQ(q.front(), 1);
	EXPECT_NO_THROW(q.front());
	EXPECT_EQ(q.back(), 1);
	EXPECT_NO_THROW(q.back());

	// poped 1 item, empty
	EXPECT_NO_THROW(q.pop());

	EXPECT_TRUE(q.empty());
	EXPECT_EQ(q.size(), 0);

	EXPECT_THROW(q.front(), std::runtime_error);
	EXPECT_THROW(q.back(), std::runtime_error);
	EXPECT_THROW(q.pop(), std::runtime_error);
}


//------/ RUN TESTS /--------------
int main(int argc, char* argv[]) {
	#ifdef _CRTDBG_MAP_ALLOC
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}