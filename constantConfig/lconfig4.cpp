/**
 * @file		lconfig4.cpp
 *
 * @author		cxgAlleria
 *
 * @brief		several funny properties
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * @brief	<1 st> to test unnamed objects
 */
template<class T>
class Printer {
public:
	bool operator()(const T & elem){
		cout << elem << ' ';
	}
};

void test1() {
	cout << "Test 1st for unnamed objects" << endl;

	int ia[] = {4, 3, 2, 1, 5, 6};
	vector<int> via(ia, ia + 6);
	for_each(via.begin(), via.end(), Printer<int>());
	cout << "Test 1st ends." << endl;
}

/**
 * @brief	<2 nd> to test whether const class variables can be initialized within class declararion
 */

template<class T>
class cs {
public:
	static const int v1 = 1;
};

void test2() {
	cout << "Test 2nd for in-declaration static class variables initialization" << endl;
	cs<int> s;
	cout << "Test 2nd ends." << endl;
}

/**
 * @brief	<3 rd> to test the increment, decrement and dereference 
 */
class Integer {
public:
	friend ostream & operator<<(ostream & os, const Integer & integer) {
		os << "(" << integer.m_i << ")";
	}
	Integer(int val = 0):
		m_i(val) {
	}
	Integer(const Integer & integer) 
		: m_i(integer.m_i) {		
	}
	Integer & operator++() {
		this->m_i += 1;
		return *this;
	}
	const Integer operator++(int) {
		Integer * temp = new Integer(this->m_i);
		++ (*this);
		return *temp;
	}
	Integer & operator--() {
		this->m_i -= 1;
		return *this;
	}
	const Integer operator--(int) {
		Integer * temp = new Integer(this->m_i);
		-- (*this);
		return *temp;
	}

	int & operator*() const{
		return (int &)this->m_i;
	}
private:
	int m_i;
};

void test3() {
	cout << "Test 3rd for increment, decrement and dereference operators" << endl;

	Integer integer(5);
	++ integer = Integer(100);
	cout << ++ integer << endl;
	cout << integer ++ << endl;
	cout << integer -- << endl;
	cout << -- integer << endl;
	cout << *integer << endl;
	const Integer int2(10);
	cout << int2 << " " << *int2 << endl;
	cout << "Test 3rd ends." << endl;
}

/**
 * @brief	4th to test functor, that is, operator()
 */
template<class T>
struct Plusor {
	T operator()(const T & _pre, const T & _post) {
		return _pre + _post;	
	}
};

template<class T>
class Minusor
{
public:
	T operator()(const T & _pre, const T & _post) {
		return _pre + _post;
	}
};

void test4() {
	cout << "Test 4th for functors" << endl;

	Plusor<int> plusor;
	cout << plusor(3, 4) << endl;
	cout << Plusor<double>()(3.9, 4.5) << endl;

	Minusor<double> minusor;
	cout << minusor(5., 4.) << endl;
	cout << Minusor<double>()(99., .1) << endl;
	cout << minusor.operator()(1., -.2) << endl;
	cout << "Test 4th ends." << endl;
}


int main(int argc, char * const argv[]) {
	test1();
	test2();
	test3();
	test4();
	return 0;
}
