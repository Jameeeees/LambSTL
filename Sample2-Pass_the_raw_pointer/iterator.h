#ifndef ITERATOR_H_
#define ITERATOR_H_
#include "stl_config.h"
#include "iterator_traits.h"
#include "type_traits.h"


/*
����iterator��Ӧ������������
*/
template <
class Category,
class T,
class Distance = ptrdiff_t,
class Pointer = T*,
class Reference = T&
>
struct iterator{
	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
};


#endif