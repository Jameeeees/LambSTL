#ifndef __LAMB_STL_INTERNAL_TYPE_TRAITS_H_
#define __LAMB_STL_INTERNAL_TYPE_TRAITS_H_

struct __true_type{};
struct __false_type{};
/*
�������������traits�������κ��ͱ�Ĳ��������������Զ����ó�__false_type
__true_type������Ӧ���ػ��汾�и���
*/
template <class type>
struct __type_traits{
	typedef __true_type 	this_dummy_member_must_be_first;
	typedef __false_type	has_trivial_default_constructor;
	typedef __false_type	has_trivial_copy_constructor;
	typedef __false_type	has_trivial_assignment_operator;
	typedef __false_type	has_trivial_destructor;
	typedef __false_type	is_POD_type;
};


/*
�ػ��汾֮һ ���int
*/
//__STL_TEMPLATE_NULL	
template<> struct __type_traits<int>{
	typedef __true_type 	this_dummy_member_must_be_first;
	typedef __true_type	has_trivial_default_constructor;
	typedef __true_type	has_trivial_copy_constructor;
	typedef __true_type	has_trivial_assignment_operator;
	typedef __true_type	has_trivial_destructor;
	typedef __true_type	is_POD_type;
};


#endif

