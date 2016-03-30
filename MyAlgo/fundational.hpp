#ifndef _FUNDATIONAL_HPP_
#define _FUNDATIONAL_HPP_

#include <iterator>
#include <chrono>
#include <random>
#ifdef DEBUG
	#include <iostream>
#endif

#if defined(DEBUG)
	#define _log(x) std::cout << (x) << std::endl;
#else
	#define _log(x)
#endif

namespace cxg {

	int RandInt(int _lower, int _upper) {
		static std::default_random_engine __generator(std::chrono::system_clock::now().time_since_epoch().count());
		return __generator() % (_upper - _lower);
	}

	template < class InputIterator >
	typename InputIterator::iterator_category iterator_category(InputIterator) {
		typename InputIterator::iterator_category __tag;
		return __tag;
	}

	template < class T >
	void swap (T & _pre, T & _post) {
		T __tmp (_pre);
		_pre = _post;
		_post = __tmp;
		_log("swap(T &, T &)")
	}

	template < class InputIterator >
	void iter_swap (InputIterator _pre, InputIterator _post) {
		swap(* _pre, * _post);
		_log("swap(InputIterator, InputIterator)")
	}

	template < class BidirectionalIterator >
	void _reverse (BidirectionalIterator _first, BidirectionalIterator _last, std::bidirectional_iterator_tag) {
		while(_first != _last && _first != --_last) {
			iter_swap(_first ++, _last);
		}
		_log("\t_reverse(BidirectionalIterator, BidirectionalIterator)")
	}

	template < class RandomAccessIterator >
	void _reverse (RandomAccessIterator _first, RandomAccessIterator _last, std::random_access_iterator_tag) {
		typename RandomAccessIterator::difference_type __diff = _last - _first;
		while(__diff > 0) {
			iter_swap(_first ++, -- _last);
			__diff -= 2;
		}
		_log("\t_reverse(RandomAccessIterator, RandomAccessIterator)")
	}

	template < class BidirectionalIterator >
	void reverse (BidirectionalIterator _first, BidirectionalIterator _last) {
		_reverse(_first, _last, iterator_category(_first));
		_log("reverse(BidirectionalIterator, BidirectionalIterator)")
	}

	template < class ForwardIterator, class T, class Comp = std::less<T> >
	ForwardIterator _lower_bound (ForwardIterator _first, ForwardIterator _last, const T & _val, Comp comp, std::forward_iterator_tag) {
		typename ForwardIterator::difference_type __diff = 0, __len = 0;
		__diff = std::distance(_first, _last);
		ForwardIterator __half;
		while(__diff > 0) {
			__half = _first;
			__len = (__diff >> 1);
			advance(__half, __len);
			if(comp(* __half, _val)) {
				_first = __half;
				_first ++;
				__diff -= __len + 1;
			}
			else {
				__diff = __len;
			}
		}
		_log("\t_lower_bound(ForwardIterator, ForwardIterator)")
		return _first;
	}

	template < class RandomAccessIterator, class T, class Comp = std::less<T> >
	RandomAccessIterator _lower_bound (RandomAccessIterator _first, RandomAccessIterator _last, const T & _val, Comp comp, std::random_access_iterator_tag) {
		typename RandomAccessIterator::difference_type __diff = _last - _first, __len = 0;
		RandomAccessIterator __half;
		while(__diff > 0) {
			__len = (__diff >> 1);
			__half = _first + __len;
			if(comp(* __half, _val)) {
				_first = __half;
				_first ++;
				__diff -= __len + 1;
			}
			else {
				__diff = __len;
			}
		}
		_log("\t_lower_bound(RandomAccessIterator, RandomAccessIterator)")
		return _first;
	}

	template < class ForwardIterator, class T, class Comp = std::less<typename ForwardIterator::value_type> >
	ForwardIterator lower_bound(ForwardIterator _first, ForwardIterator _last, const T & _val, Comp comp = Comp()) {
		_log("lower_bound")
		return _lower_bound(_first, _last, _val, comp, iterator_category(_first));
	}

	template < class ForwardIterator, class T, class Comp = std::greater<T> >
	ForwardIterator _upper_bound (ForwardIterator _first, ForwardIterator _last, const T & _val, Comp comp, std::forward_iterator_tag) {
		typename ForwardIterator::difference_type __diff = 0, __len = 0;
		__diff = std::distance(_first, _last);
		ForwardIterator __half;
		while(__diff > 0) {
			__half = _first;
			__len = (__diff >> 1);
			advance(__half, __len);
			if(comp(* __half, _val)) {
				__diff = __len;
			}
			else {
				_first = __half;
				_first ++;
				__diff -= __len + 1;
			}
		}
		_log("\t_upper_bound(ForwardIterator, ForwardIterator)")
		return _first;
	}

	template < class RandomAccessIterator, class T, class Comp = std::greater<T> >
	RandomAccessIterator _upper_bound (RandomAccessIterator _first, RandomAccessIterator _last, const T & _val, Comp comp, std::random_access_iterator_tag) {
		typename RandomAccessIterator::difference_type __diff = _last - _first, __len = 0;
		RandomAccessIterator __half;
		while(__diff > 0) {
			__len = (__diff >> 1);
			__half = _first + __len;
			if(comp(* __half, _val)) {
				__diff = __len;
			}
			else {
				_first = __half;
				_first ++;
				__diff -= __len + 1;
			}
		}
		_log("\t_upper_bound(RandomAccessIterator, RandomAccessIterator)")
		return _first;
	}

	template < class ForwardIterator, class T, class Comp = std::greater<T> >
	ForwardIterator upper_bound(ForwardIterator _first, ForwardIterator _last, const T & _val, Comp comp = Comp()) {
		_log("upper_bound")
		return _upper_bound(_first, _last, _val, comp, iterator_category(_first));
	}

	template < class ForwardIterator, class T, class Comp = std::less<T> >
	ForwardIterator binary_search(ForwardIterator _first, ForwardIterator _last, const T & _val, Comp comp = Comp()) {
		_log("binary_search")
		return lower_bound(_first, _last, _val, comp);
	}

	template < class BidirectionalIterator, class Comp = std::less<typename BidirectionalIterator::value_type> >
	bool next_permutation(BidirectionalIterator _first, BidirectionalIterator _last, Comp comp = Comp()) {
		_log("next_permutation")
		BidirectionalIterator __i = _first;
		if(__i == _last || ++ __i == _last) {
			return false;
		}
		__i = _last;
		__i --;
		while(true) {
			BidirectionalIterator __ii = __i, __j;
			__i --;
			if(comp(* __i, * __ii)) {
				__j = _last;
				while(! comp(* __i, * -- __j));;
				iter_swap(__j, __i);
				reverse(__ii, _last);
				return true;
			}
			if(__i == _first) {
				reverse(_first, _last);
				return false;
			}
		}
	}

	template < class BidirectionalIterator, class Comp = std::greater<typename BidirectionalIterator::value_type> >
	bool prev_permutation(BidirectionalIterator _first, BidirectionalIterator _last, Comp comp = Comp()) {
		_log("prev_permutation")
		BidirectionalIterator __i = _first;
		if(__i == _last || ++ __i == _last) {
			return false;
		}
		__i = _last;
		__i --;
		while(true) {
			BidirectionalIterator __ii = __i, __j;
			__i --;
			if(comp(* __i, * __ii)) {
				__j = _last;
				while(! comp(* __i, * -- __j));;
				iter_swap(__j, __i);
				reverse(__ii, _last);
				return true;
			}
			if(__i == _first) {
				reverse(_first, _last);
				return false;
			}
		}
	}

	template < class RandomAccessIterator >
	void random_shuffle(RandomAccessIterator _first, RandomAccessIterator _last) {
		_log("random shuffle")
		if(_first == _last) {
			return;
		}
		while(_first != _last) {
			iter_swap(_first, _first + RandInt(0, _last - _first));
			++ _first;
		}
	}

	template < class RandomAccessIterator, class Comp = std::less<typename RandomAccessIterator::value_type> >
	RandomAccessIterator partition (RandomAccessIterator _first, RandomAccessIterator _last, Comp _comp = Comp()) {
		_log("partition")
		RandomAccessIterator __i = _first;
		typename RandomAccessIterator::value_type __guard(* __i);
		while(true) {
			while((++ __i < _last) && _comp(* __i, __guard));
			while((_first < -- _last) && ! _comp(* _last, __guard));
			if(__i >= _last) {
				break;
			}
			iter_swap(__i, _last);
		}
		iter_swap(_first, _last);
		return _last;
	}

	template < class RandomAccessIterator, class Comp = std::less<typename RandomAccessIterator::value_type> >
	RandomAccessIterator unguarded_partition (RandomAccessIterator _first, RandomAccessIterator _last, Comp _comp = Comp()) {
		_log("partition")
		RandomAccessIterator __i = _first;
		typename RandomAccessIterator::value_type __guard(* __i);
		while(true) {
			while(_comp(* ++ __i, __guard));//compared with partition, there is no nned to perform bound checking
			while(! _comp(* -- _last, __guard));
			if(__i >= _last) {
				break;
			}
			iter_swap(__i, _last);
		}
		iter_swap(_first, _last);
		return _last;
	}

	template < class RandomAccessIterator, class Comp = std::less<typename RandomAccessIterator::value_type> >
	RandomAccessIterator random_partition (RandomAccessIterator _first, RandomAccessIterator _last, Comp _comp = Comp()) {
		_log("random partition")
		iter_swap(_first, _first + RandInt(0, _last - _first));
		return partition(_first, _last, _comp);
	}

	template < class InputIterator, class Comp = std::less<typename InputIterator::value_type> >
	InputIterator medianOfThree(InputIterator _first, InputIterator _second, InputIterator _third, Comp _comp = Comp()) {
		if(_comp(* _first, * _second)) {//f s
			if(_comp(* _first, * _third)) {
				if(_comp(* _second, * _third)) {
					return _second;// f s t
				}
				else {
					return _third;//f t s
				}
			}
			else {
				return _first;//t f s
			}
		}
		else {//s f
			if(_comp(* _first, * _third)) {// s f t
				return _first;
			}
			else {
				if(_comp(* _second, * _third)) { // s t f
					return _third;
				}
				else {
					return _second;// t s f
				}
			}
		}
	}

	template < class RandomAccessIterator, class Comp = std::less<typename RandomAccessIterator::value_type> >
	RandomAccessIterator median_of_three_partition (RandomAccessIterator _first, RandomAccessIterator _last, Comp _comp = Comp()) {
		_log("median of three partition")
		iter_swap(_first, medianOfThree(_first, _first + (_last - _first) / 2, _last - 1));
		return unguarded_partition(_first, _last, _comp);
	}

	template < class RandomAccessIterator, class Comp = std::less<typename RandomAccessIterator::value_type> >
	void quick_sort (RandomAccessIterator _first, RandomAccessIterator _last, Comp _comp = Comp()) {
		_log("quick sort")
		if(_last - _first > 2) {
			RandomAccessIterator __delimiter = median_of_three_partition(_first, _last, _comp);
			quick_sort(_first, __delimiter, _comp);
			quick_sort(++ __delimiter, _last, _comp);
		}
		else if (_last - _first == 2){
			if (! _comp(* _first, * (_first + 1))) {
				iter_swap(_first, _first + 1);
			}
		}
	}

	template < class RandomAccessIterator, class Comp = std::less<typename RandomAccessIterator::value_type> >
	void push_heap (RandomAccessIterator _first, RandomAccessIterator _last, Comp _comp = Comp()) {
		_log("push heap")
		typename RandomAccessIterator::difference_type __diff = _last - _first, __cur = __diff - 1, __parent = __cur >> 1;
		while (__cur != 1 && _comp(* (_first + __cur), * (_first + __parent))) {
			iter_swap(_first + __cur, _first + __parent);
			__cur = __parent;
			__parent = __cur >> 1;
		}
	}

	template < class RandomAccessIterator, class Comp = std::less<typename RandomAccessIterator::value_type> >
	void pop_heap (RandomAccessIterator _first, RandomAccessIterator _last, Comp _comp = Comp()) {
		_log("pop heap")
		typename RandomAccessIterator::difference_type __diff = _last - _first - 1, __cur = 1, __child = __cur << 1;
		if(__diff > 1) {
			iter_swap(_first + 1, _last - 1);
			while(__child < __diff) {
				if(__child + 1 < __diff && _comp(* (_first + __child + 1), * (_first + __child))) {
					__child ++;
				}
				if(_comp(* (_first + __child), *(_first + __cur))) {
					iter_swap(_first + __child, _first + __cur);
				}
				else {
					break;
				}
				__cur = __child;
				__child = __cur << 1;
			}
		}
	}

	template < class RandomAccessIterator, class Comp = std::less<typename RandomAccessIterator::value_type> >
	void make_heap (RandomAccessIterator _first, RandomAccessIterator _last, Comp _comp = Comp()) {
		_log("make heap")
		typename RandomAccessIterator::difference_type __diff = _last - _first, __cur = 1;
		for(; __cur <= __diff; ++ __cur) {
			push_heap(_first, _first + __cur, _comp);
		}
	}

	template < class RandomAccessIterator, class Comp = std::less<typename RandomAccessIterator::value_type> >
	void sort_heap (RandomAccessIterator _first, RandomAccessIterator _last, Comp _comp = Comp()) {
		_log("sort heap")
		typename RandomAccessIterator::difference_type __diff = _last - _first;
		while(__diff > 1) {
			pop_heap(_first, _first + __diff --, _comp);
		}
	}

	template < class RandomAccessIterator, class Comp = std::less<typename RandomAccessIterator::value_type> >
	void heap_sort (RandomAccessIterator _first, RandomAccessIterator _last, Comp _comp = Comp()) {
		_log("heap sort")
		typename RandomAccessIterator::difference_type __diff = _last - _first;
		make_heap (_first, _last, _comp);
		sort_heap (_first, _last, _comp);
	}

	template < class RandomAccessIterator, class Comp = std::less<typename RandomAccessIterator::value_type> >
	void partial_sort (RandomAccessIterator _first, RandomAccessIterator _middle, RandomAccessIterator _last, Comp _comp = Comp()) {
		_log("partial sort")
		typename RandomAccessIterator::difference_type __diff = _last - _middle, __cur = 0;
		make_heap(_first, _middle, _comp);
		for(; __cur < __diff; ++ __cur) {
			if(_comp(* (_middle + __cur), * _first)) {
				iter_swap(_middle, _middle + __cur);
				pop_heap(_first, _middle + 1, _comp);
			}
		}
		sort_heap(_first, _middle, _comp);
	}


}

#endif // _FUNDATIONAL_HPP_
