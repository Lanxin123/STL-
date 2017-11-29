#ifndef __JJALLOC__
#define  __JJALLOC__

#include <new>		//for placement new.
#include <cstddef>	//ptrdiff_t,size_t
#include <cstdlib>	//for exit()
#include <climits>	//for UNIT_MAX
#include <iostream>//for cerr

namespace JJ
{
	template<class T>
	inline T* _allocate(ptrdiff_t size, T*) {
		set_new_handler(0);
		T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
		if (tmp == 0) {
			cerr << "out of memory" << endl;
			exit(1);
		}
		return tmp;
	}
	
	template <class T>
	inline void _deallocate(T* buffer) {
		::operator delete(buffer);
	}

	template<class T1,class T2>
	inline void _construct(T1* p, const T2& value) {
		new(p) T1(value);			//placement new. invoke ctor of T1声明一个新的唤起T1的ctor
	}
	
	template<class T>
	inline void _destory(T* ptr) {
		ptr->T();
	}
	
	template<class T>
	class allocator {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_referemce;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		//rebind allocator of type U
		template<class U>
		struct rebind {
			typedef allocator<U> other;
		};

		pointer allocate(size_type n, const void* hint = 0) {
			return _allocate((difference_type)n, (pointer)0);
		}

		void deallocate(pointer p, size_type n) { _deallocate(p); }

		void construct(pointer p, const T& value) {
			_construct(p, value);
		}

		void destroy(pointer  p) { _destory(p); }

		pointer address(reference x) { return (pointer)&x };

		const_pointer const_adress(const_referemce x) {
			return (const_pointer)&x;
		}

		size_type max_size() const {
			return size_type(UINT_MAX / sizeof(T));
		}
	};
}
#endif //__JJALLOC__

//首先这个头文件无法搭配SGI stl运行，而且只能有限度的搭配PJ STL运行，
//其次这个语法我没太懂，就是::operator，是指定类型的意思吗？
//::有全局作用域运算符的意思，C++的语法还是没学透



