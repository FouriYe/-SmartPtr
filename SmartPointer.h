//目前还不支持指向常量字符串


#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include<iostream>

#define PRINT_STR(str) \
do{\
	std::cout<<str<<std::endl;\
}while(0);\

#define PRINT_PTR(str,ptr) \
do{\
	std::cout<<str<<static_cast<const void*>(ptr)<<std::endl;\
	std::cout<<"this ptr's type is "<<typeid(ptr).name()<<std::endl;\
} while (0); \

class test_type {
public:
	void func() {
		PRINT_STR("test func");
	}
};

template<typename T>
class SmartPtr {
public:
	//构造函数
	SmartPtr() :mpointer(nullptr) { ref_count = new size_t(0); PRINT_STR("creat a smart ptr"); }
	SmartPtr(T *p) :mpointer(p) { 
		ref_count = new size_t(1);
		PRINT_PTR("creat a smart ptr at ", mpointer);
	}
	//拷贝构造
	SmartPtr(const SmartPtr<T> &p) {
		if (&p) {
			mpointer = p.mpointer;
			ref_count = p.ref_count;
			(*ref_count)++;
		}
	}
	//赋值符重载
	SmartPtr &operator=(const SmartPtr<T> &p) {
		if (&p == this) return *this;              //防止自我赋值
        //释放底层指针
		if (*ref_count == 0) { 
			delete mpointer; 
			delete ref_count;
			PRINT_STR("deconstruct!");
		}
		else if ((--(*ref_count)) == 0) {
			delete mpointer;
			delete ref_count;
			PRINT_STR("deconstruct!");
		}
		mpointer = p.mpointer;
		ref_count = p.ref_count;
		(*ref_count)++;
		return *this; 
	}
	//解引用
	T& operator*() const{
		return *mpointer;
	}
	T* operator->() const{
		return mpointer;
	}
	//比较和判空
	bool operator==(const T* p) {
		return mpointer == p;
	}
	bool operator==(const SmartPtr& p) {
		return mpointer == p.mpointer;
	}
	bool operator!=(const T* p) {
		return mpointer != p;
	}
	bool operator!=(const SmartPtr& p) {
		return mpointer != p.mpointer;
	}
	//析构函数
	~SmartPtr() {
		PRINT_PTR("release a smart ptr at ", mpointer);
		if (*ref_count == 0) {                //防止出现ref_count已经为0，自减后为无穷大的情况（ref_count为size_t类型）
			delete mpointer;
			delete ref_count;
			PRINT_STR("deconstruct!");
		}
		else if ((--(*ref_count)) == 0) {
		delete mpointer;
		delete ref_count;
		PRINT_STR("deconstruct!");
		}
	}
	//得到引用计数
	size_t get_ref_count() {
		return *ref_count;
	}
private:
	T *mpointer;
	size_t *ref_count;
};

#endif
