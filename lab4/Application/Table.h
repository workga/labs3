#ifndef __H_TABLE
#define __H_TABLE

#include <stdexcept>
#include <string>
#include <vector>

template< class T>
class Table {
public:
	Table();

	int get_max_level();
	const T& operator[](int i);

	int add_level(T props);


	//  PLACEHOLDER
	static T levels[3];
	//
private:
	int _max_level;
	std::vector<T> data;
};

template<class T>
Table<T>::Table() {
	_max_level = 0;

	for (const T& t : levels)
		add_level(t);
	// here use T.name to load T structures from file
}

template<class T>
int Table<T>::get_max_level() { 
	return _max_level;
}

template<class T>
const T& Table<T>::operator[](int i) {
	if (i <= 0)
		throw std::runtime_error("Index < 1.");
	return data[i - 1];
}

template<class T>
int Table<T>::add_level(T props) {
	data.push_back(props); 
	_max_level++;
	
	return _max_level;
}


#endif

