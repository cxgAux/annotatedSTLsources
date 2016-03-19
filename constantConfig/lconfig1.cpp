/**
 *	@file		lconfig1.cpp
 *
 *	@author		cxgAlleria
 *	
 *	@brief		to test configurations defined in <stl_config.h>
 *
 */

#include <iostream>

using namespace std;

int main(int argc, char * const argv[]){
#if defined(__sgi)
	cout << "__sgi" << endl;
#endif// __sgi

#if defined(__GNUC__)
	cout << "__GNUC__" << endl;
	cout << __GNUC__ << ' ' << __GNUC_MINOR__ << endl;
#if defined(__GLIBC__)
	cout << __GLIBC__ << endl;
#endif// __GLIBC__

//case 2
#ifdef __STL_NO_DRAND48
	cout << "__STL_NO_DRAND48 defined" << endl;
#else
	cout << "__STL_NO_DRAND48 undefined" << endl;
#endif

//case 3
	cout << "__STL_STATIC_TEMPLATE_MEMBER_BUG ";
#ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG
	cout << "defined";
#else
	cout << "undefined";
#endif
	cout << endl;

//case 4
	cout << "__STL_CLASS_PARTIAL_SPECIALIZATION ";
#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
	cout << "defined";
#else
	cout << "undefined";
#endif// __STL_CLASS_PARTIAL_SPECIALIZATION
	cout << endl;
//case 5
//case 6

#endif// __GNUC__
	return 0;
}
