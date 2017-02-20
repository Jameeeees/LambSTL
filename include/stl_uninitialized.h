#ifndef __LAMB_STL_INTERNAL_UNINITIALIZED_H_
#define __LAMB_STL_INTERNAL_UNINITIALIZED_H_
#include "stl_algorithm.h"
#include "stl_iterator.h"
#include <iostream>

/* start of uninitialized_fill_n */
/*
parameters��
	first:������firstָ������ʼ���ռ����ʼ��
	n:��ʾ����ʼ���ռ�Ĵ�С
	x:��ʾҪ��ʼ���ɵĳ�ֵ
*/

//�������POD�����ε��ù��캯��
template <class ForwardIterator, class Size, class T>
ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __false_type){
	ForwardIterator cur = first;
	for (; n > 0; --n, ++cur)
		construct(&*cur,x);
	return cur;
}


template <class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n, const T& x, T1 *){
	//POD = Plain Old Data��scalar types ���� ��ͳC struct
	//POD����ӵ��trivial ctor/dtor/copy/assignment����
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	return __uninitialized_fill_n_aux(first, n, x, is_POD());
}


template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x){
	return __uninitialized_fill_n(first, n, x, value_type(first));//ʹ��value_type��ȡ��first��type
}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __true_type){
	return fill_n(first, n, x);//���ø߽׺���
}



/* end of uninitialized_fill_n */


/* start of uninitialized_copy */
/*
parameters��
	first:ָ������˵���ʼλ��
	last:ָ������˵Ľ���λ��
	result:ָ�������
*/
template <class InputIterator, class ForwardIterator>
ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type){
	ForwardIterator cur = result;
	for ( ; first != last; ++first, ++cur)
		construct(&*cur,*first);
	return cur;
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type){
	return copy(first,last,result);//�߽׺���
}

template <class InputIterator, class ForwardIterator, class T>
inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*){
	typedef typename __type_traits<T>::is_POD_type is_POD;
	return __uninitialized_copy_aux(first, last, result, is_POD());//is POD?
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result){
	//return __uninitialized_copy(first, last, result, value_type(result));//��ȡ��type
	return __uninitialized_copy(first, last, result, value_type(result));//��ȡ��type
}





/* end of uninitialized_copy */


/* start of uninitialized_fill */
/*
parameters��
	first:ָ������ʼ���ռ����ʼ��
	last:ָ������ʼ���ռ�Ľ�����
	x:��ʾ��ֵ
*/
template <class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x, __true_type){
	fill(first, last, x);
}

template <class ForwardIterator, class T>
void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x,__false_type){
	ForwardIterator cur = first;
	for ( ; cur != last; ++cur)
		construct(&*cur,x);
}


template <class ForwardIterator, class T, class T1>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x, T1*){
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	__uninitialized_fill_aux(first, last, x, is_POD());
}


template <class ForwardIterator, class T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x){
	__uninitialized_fill(first,last,x,value_type(first));
}



/* end of uninitialized_fill */




#endif

