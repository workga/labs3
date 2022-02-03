#ifndef __H_QUEUE
#define __H_QUEUE

#include <stdexcept>
#include <iostream>

template<class T>
class Queue {
public:
	Queue();
	Queue(const Queue& other);
	Queue(Queue&& other);

	~Queue();

	Queue& operator=(const Queue& other);
	Queue& operator=(Queue&& other);

	bool empty();
	int size();

	T& front();
	T& back();
	void push(T info);
	void pop();

private:
	struct Item {
		T _info;
		Item* _next;
	};

	Item* _tail;

	int _size;
};



//------/ Definitions /------------

template<class T>
Queue<T>::Queue()
	: _tail(nullptr)
	, _size(0) {
}

template<class T>
Queue<T>::~Queue() {
	if (!_tail) return;

	Item* cur = _tail->_next;
	_tail->_next = nullptr;

	Item* prev = nullptr;
	while (cur) {
		prev = cur;
		cur = cur->_next;
		delete prev;
	}
}

template<class T>
Queue<T>::Queue(const Queue& other)
	: Queue<T>() {

	Item* cur = other._tail->_next;
	do {
		push(cur->_info);
		cur = cur->_next;
	} while (cur != other._tail->_next);
}

template<class T>
Queue<T>::Queue(Queue<T>&& other)
	: Queue<T>() {
	std::swap(_tail, other._tail);
	std::swap(_size, other._size);
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	while (!empty()) {
		pop();
	}

	Item* cur = other._tail->_next;
	do {
		push(cur->_info);
		cur = cur->_next;
	} while (cur != other._tail->_next);

	return *this;
}

template<class T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) {
	std::swap(_tail, other._tail);
	std::swap(_size, other._size);

	return *this;
}

template<class T>
bool Queue<T>::empty() {
	if (!_tail) return true;
	else return false;
}

template<class T>
int Queue<T>::size() {
	return _size;
}

template<class T>
T& Queue<T>::front() {
	if (!_tail) throw std::runtime_error("No front element in empty queue.");

	return _tail->_next->_info;
}

template<class T>
T& Queue<T>::back() {
	if (!_tail) throw std::runtime_error("No back element in empty queue.");

	return _tail->_next->_info;
}

template<class T>
void Queue<T>::push(T info) {
	Item* back = new Item();

	back->_info = info;

	if (!_tail) {
		_tail = back;
		_tail->_next = back;
	}
	else {
		back->_next = _tail->_next;
		_tail->_next = back;
		_tail = back;
	}

	_size++;
}

template<class T>
void Queue<T>::pop() {
	if (!_tail) throw std::runtime_error("No front element in empty queue.");

	Item* front = _tail->_next;
	_tail->_next = front->_next;

	if (front == _tail) _tail = nullptr;

	delete front;


	_size--;
}

#endif // !


