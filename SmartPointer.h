//Ŀǰ����֧��ָ�����ַ���


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
	//���캯��
	SmartPtr() :mpointer(nullptr) { PRINT_STR("creat a smart ptr"); }
	SmartPtr(T *p) :mpointer(p) { 
		if (mpointer) ref_count=new size_t(1);
		PRINT_PTR("creat a smart ptr at ", mpointer); 
	}
	//��������
	SmartPtr(const SmartPtr<T> &p) :mpointer(p.mpointer),ref_count(p.ref_count) {
		if (p.mpointer) (*ref_count)++;
	}
	//��ֵ������
	SmartPtr &operator=(const SmartPtr<T> &p) {
		if (&p == this) return *this;
		if (mpointer) {
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
		}
		mpointer = p.mpointer;
		ref_count = p.ref_count;
		(*ref_count)++;
		return *this; 
	}
	//������
	T& operator*() const{
		return *mpointer;
	}
	T* operator->() const{
		return mpointer;
	}
	//�ȽϺ��п�
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
	//��������
	~SmartPtr() {
		PRINT_PTR("release a smart ptr at ", mpointer);
		if(mpointer){
			if (*ref_count == 0) {                //��ֹ����ref_count�Ѿ�Ϊ0���Լ���Ϊ�����������ref_countΪsize_t���ͣ�
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
	}
	//�õ����ü���
	size_t get_ref_count() {
		return *ref_count;
	}
private:
	T *mpointer;
	size_t *ref_count;
};

#endif

