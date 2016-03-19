#include <iostream>
#include "2jjalloc.h"
#include <vector>
#include <type_traits>

using namespace std;

void overloaded(const int & x) {
	std::cout << "lv" << endl;
}

void overloaded(int && x) {
	cout << "rv" << endl;
}

template<class T>
void comp(T && p){
	overloaded(p);
	overloaded(forward<T>(p));
}

int main(int argc, char * const argv[]) {
	int ia[5] = {0, 2, 4, 5, 101};
	unsigned int i;
	vector<int, JJ::allocator<int> > iv(ia, ia + 5);
	for(i = 0; i < 5; ++ i) {
		cout << iv[i] << " ";
	}
	cout << endl;

	vector<int, std::allocator<int>  > ivv;

	int a = 1, & b = a;
	comp(a);
	comp(b);
	comp(0);
	return 0;
}
