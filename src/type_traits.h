#ifndef __TYPE_TRAITS_H_
#define __TYPE_TRAITS_H_

/*
һ��classʲôʱ��Ӧ�����Լ���
non-trivial default constructor,
non-trivial copy constructor,
non-trivial assignment operator,
non-trivial destructor
### ׼��
���class�ں�ָ���Ա�����Ҷ������ж�̬�ڴ����ã���ô���class����Ҫʵ�ֳ��Լ���non-trivial-xxx
*/



/*
�������������traits�������κ��ͱ�Ĳ��������������Զ����ó�__false_type
__true_type������Ӧ���ػ��汾�и���
ֵ��ע����ǣ����д���Զ����class����ζ�ű�׼����û����Ӧ�ػ���__type_traits�����е����Զ��������__false_type
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
	typedef __true_type		has_trivial_default_constructor;
	typedef __true_type		has_trivial_copy_constructor;
	typedef __true_type		has_trivial_assignment_operator;
	typedef __true_type		has_trivial_destructor;
	typedef __true_type		is_POD_type;
};


#endif

