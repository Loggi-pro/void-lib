#pragma once

namespace vd{
	
	
template <class ForwardIterator, class T>
void fill (ForwardIterator first, ForwardIterator last, const T& val) {
	while (first != last) {
		*first = val;
		++first;
	}
}

template <class ForwardIterator, class T>
void fill_n (ForwardIterator first, size_t count, const T& val) {
	while (count--) {
		*first = val;
		++first;
	}
}


template <class InputIterator, class OutputIterator>
void copy (InputIterator source, OutputIterator target, size_t count) {
	for (size_t i = 0; i < count; i++) {
		*target = *source;
		target++;
		source++;
	}
}

template<class InputIterator, class OutputIterator>
OutputIterator copy (InputIterator first, InputIterator last, OutputIterator target) {
	while (first != last) {
		*target = *first;
		++target;
		++first;
	}

	return target;
}

template<class T> 
void swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}
	
	
}