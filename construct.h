#ifndef __CONSTRUCT_H_
#define __CONSTRUCT_H_
#include "type_traits.h"
#include <new>

template <class T1, class T2>
inline void construct(T1* p, const T2& value){
	new (p) T1 (value);
}

template <class ForwardIterator>
inline void __destory_aux(ForwardIterator first, ForwardIterator last, __false_type){
	for(; first < last; ++first){
		destroy(&*first);
	}
}

template <class ForwardIterator>
inline void __destory_aux(ForwardIterator, ForwardIterator, __true_type){}


template <class ForwardIterator, class T>
inline void __destory(ForwardIterator first, ForwardIterator last, T*){
	typedef typename  __type_traits<T>::has_trivial_destructor trivial_destructor;
	__destory_aux(first, last, trivial_destructor());
}

template <class T>
inline void destroy(T* pointer){
	pointer->~T();
}

template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last){
	__destory(first, last, value_type(first));
}



//����Ϊdestory()��Ե�����Ϊchar*��wchar_t*���ػ���
inline void destroy(char*, char*){}
inline void destroy(wchar_t*, wchar_t*){}

#endif





