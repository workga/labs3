#include "element.h"

#pragma once

class Stack{
	private:
	static const int QUOTA = 10;
	int SZ;
	int top;
	Element *stack;
	public:
	Stack() : SZ(QUOTA), top(0) , stack(new Element[QUOTA]){}
	Stack(const Element& el) : SZ(QUOTA), top(1) , stack(new Element[QUOTA]) { stack[0] = el; }
	Stack(Element *, int);
	Stack(const Stack &);
	Stack(Stack &&);
	~Stack() { delete[] stack; }

	int push(const Element &);
	int pop(Element &);
	int getSize() const { return top; }
	int getMaxSZ() const { return SZ; }
	bool isEmpty() const;
	bool isFilled() const;

	friend std::ostream & operator <<(std::ostream &, const Stack &);
	friend std::istream & operator >>(std::istream &, Stack &);
	Stack & operator =(const Stack &);
	Stack & operator =(Stack &&);
	Stack & operator +=(Element);
	Stack & operator --();
	const Stack operator --(int);
};
