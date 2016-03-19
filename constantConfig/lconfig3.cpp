/**
 * @file		lconfig3.cpp
 *
 * @author		cxgAlleria
 *
 * @brief		to test several congirations in <stl_config.h>
 *
 */

#include <iostream>

using namespace std;

/**
 * @brief	test __STL_STATIC_TEMPLATE_MEMBER_BUG
 */
template<typename T>
class staticTemplate{
public:
	static int _data;
};

/**
 * @warning	<with g++ v4.8.4>must with syntax "template<>"
 */
template<>
int staticTemplate<int>::_data = 1;
template<>
int staticTemplate<char>::_data = 2;

void test1(){
	cout << "This block is to test __STL_STATIC_TEMPLATE_MEMBER_BUG" << endl;

	cout << staticTemplate<int>::_data << endl;
	cout << staticTemplate<char>::_data << endl;
	
	staticTemplate<int> ob1;
	staticTemplate<char> ob2;
	ob1._data = 11;
	ob2._data = 22;
	cout << staticTemplate<int>::_data << endl;
	cout << staticTemplate<char>::_data << endl;
	cout << "test __STL_STATIC_TEMPLATE_MEMBER_BUG end." << endl;
}

/**
 * @brief	to test __STL_CLASS_PARTIAL_SPECIALIZATION
 */

//泛化设计
template<class I, class O>
struct partialSpecialization {
	partialSpecialization() {
		cout << "I, O" << endl;
	}
};

//特化设计１
template<class T>
struct partialSpecialization<T *, T *> {
	partialSpecialization() {
		cout << "T *, T *" << endl;
	}
};

//特化设计2
template<class T>
struct partialSpecialization<const T *, T *> {
	partialSpecialization() {
		cout << "const T *, T *" << endl;
	}
};

void test2(){
	cout << "This block is to test __STL_CLASS_TEMPLATE_PARTIAL_SPECIALIZATION" << endl;
	partialSpecialization<int, char> ob1;
	partialSpecialization<int *, int *> ob2;
	partialSpecialization<const char *, char *> ob3;
	cout << "test __STL_CLASS_TEMPLATE_PARTIAL_SPECIALIZATION ends." << endl;
}

/**
 * @brief	to test __STL_FUNCTION_TMPL_PARTIAL_ORDER
 */
void test3(){
	cout << "This block is to test __STL_FUNCTION_TMPL_PARTIAL_ORDER" << endl;
#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
	cout << "y" << endl;
#else
	cout << "n" << endl;
#endif// __STL_FUNCTION_TMPL_PARTIAL_ORDER
	cout << "test __STL_FUNCTION_TMPL_PARTIAL_ORDER end" << endl;
}


/**
 * @brief	to test __STL_MEMBER_TEMPLATES
 */
class alloc{
};

template<class T, class Alloc = alloc>
class MemberTemplate{
public:
	template<class I>
	void insert(T val, I first, I last){
		cout << "insert()" << endl;
	}
};

void test4(){
	cout << "This block is to test __STL_MEMBER_TEMPLATES" << endl;
	MemberTemplate<int> mt;
	mt.insert(4, 5, 6);
	cout << "test __STL_MEMBER_TEMPLATES end" << endl;
}

/**
 * @brief	to test __STL_LIMITED_DEFAULT_TEMPLATES
 */
template<class T, class Alloc = alloc, size_t Bufsiz = 0>
class deque {
public:
	deque() {
		cout << "deque" << endl;
	}
};

template<class T, class Sequence = deque<T> >
class stack {
public:
	stack() {
		cout << "stack" << endl;
	}
private:
	Sequence c;
};

void test5(){
	cout << "This block is to test __STL_LIMITED_DEFAULT_TEMPLATES" << endl;
	stack<int> x;
	cout << "test __STL_LIMITED_DEFAULT_TEMPLATES end" << endl;
}

/**
 * @brief	to test __STL_NON_TYPE_TMPL_PARAM_BUG
 */
inline size_t __deque_buf_size(size_t n, size_t sz){
	return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

template<class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator {
	typedef __deque_iterator<T, T &, T *, BufSiz> iterator;
	typedef __deque_iterator<const T, const T &, const T *, BufSiz> const_iterator;
	static size_t buffer_size(){
		return __deque_buf_size(BufSiz, sizeof(T));
	}
};

template<class T, class Alloc = alloc, size_t BufSiz = 0>
class deque6 {
public:
	typedef __deque_iterator<T, T &, T *, BufSiz> iterator;
};

void test6(){
	cout << "This block is to test __STL_NON_TYPE_TMPL_PARAM_BUG" << endl;
	cout << deque6<int>::iterator::buffer_size() << endl;
	cout << deque6<int, alloc, 64>::iterator::buffer_size() << endl;
	cout << "test __STL_NON_TYPE_TMPL_PARAM_BUG end" << endl;
}

/**
 * @biref	main block
 */
int main(int argc, char * const argv[]){
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	return 0;
}
