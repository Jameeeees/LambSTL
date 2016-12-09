#include <new>		/* placement new */
#include <cstddef>	/* for ptrdiff_t, size_t */
#include <cstdlib>	/* exit() */
#include <climits>	/* UINT_MAX */
#include <iostream> /* cerr */

enum {__ALIGN = 8};	//С��������ϵ��߽�
enum {__MAX_BYTES = 128};	//С�����������
enum {__NFREELISTS = __MAX_BYTES / __ALIGN};	//free_list ����

template <bool threads,int inst>
class __default_alloc_template{

private:
	static size_t ROUND_UP(size_t bytes){
		return (((bytes) + __ALIGN - 1) & ~(__ALIGN - 1));
	}
	union obj {
		union obj* free_list_link;
		char client_data[1];
	};
	
	static obj* volatile free_list[__NFREELISTS];
	static size_t FREELIST_INDEX(size_t bytes){
		return (((bytes) + __ALIGN - 1) / __ALIGN - 1);
	}
	
	static void* refill(size_t n);
	static char* chunk_alloc(size_t size, int& nobjs);
	
	static char* start_free;	//�ڴ����ʼλ�ã�ֻ��chunk_alloc()�б仯
	static char* end_free;		//�ڴ�ؽ���λ�ã�ֻ��chunk_alloc()�б仯
	static size_t heap_size;
	
public:
	static void* allocate(size_t n){
		obj* volatile * my_free_list;
		obj* result;
		if (n > (size_t) __MAX_BYTES){
			return malloc_alloc::allocate(n);
		}
		my_free_list = free_list + FREELIST_INDEX(n);//�ҵ���Ӧ��С��freelistλ��
		result = *my_free_list;
		if (result == 0){
			//û�п��õ�freelist������ڴ�����
			void* r = refill(ROUND_UP(n));
			return r;
		}
		*my_free_list = result -> free_list_link;
		return result;
	}
	static void deallocate(void* p,size_t n){
		obj* q = (obj*)p;
		obj* volatile *my_free_list;
		
		if (n > (size_t) __MAX_BYTES){
			malloc_alloc::deallocate(p,n);
			return;
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		
		q->free_list_link = *my_free_list;
		*my_free_list = q;
	}
	static void* reallocate(void* p, size_t old_sz, size_t new_sz);
	
};

template <bool threads, int inst>
char* __default_alloc_template<threads,inst>::start_free = 0;

template <bool threads, int inst>
char* __default_alloc_template<threads,inst>::end_free = 0;

template <bool threads, int inst>
size_t __default_alloc_template<threads,inst>::heap_size = 0;

template <bool threads, int inst>
__default_alloc_template<threads, inst>::obj* volatile
__default_alloc_template<threads, inst>::free_list[__NFREELISTS] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};



























