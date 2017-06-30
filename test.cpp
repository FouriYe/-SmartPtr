#ifdef _WINDOWS                 //检测内存泄漏
#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#endif

#include "SmartPointer.h"
#include<iostream>
using namespace std;

void test1() {
	cout << endl;
	cout << "-------------------In test1---------------------" << endl;
	//检测智能指针指向基本类型
	SmartPtr<char> sp_char1;
	SmartPtr<char> sp_char2 = nullptr;
	SmartPtr<char> sp_char3 = new char('a');
	cout << endl;
	SmartPtr<char *> sp_char_x1;
	SmartPtr<char *> sp_char_x2 = new char*;
	cout << endl;
	SmartPtr<int> sp_int1;
	SmartPtr<int> sp_int2 = new int(123);
	cout << endl;
	SmartPtr<int *> sp_int_x1;
	SmartPtr<int *> sp_int_x2 = new int*;

#ifdef CONST_CHAR
	SmartPtr<const char *> sp = "const char * is OK";
#endif

	cout << endl;
	cout << "--------------------Out test1-------------------" << endl;
}

void test2() {
	//测试拷贝构造函数与赋值运算符
	cout << endl;
	cout << "--------------------In test2--------------------" << endl;
	SmartPtr<char> sp_char1 = new char('a');
	SmartPtr<char> sp_char2 = new char('b');
	SmartPtr<char> sp_char3 = sp_char1;
	sp_char1 = sp_char2;
	cout << endl;
	SmartPtr<int> sp_int1 = new int(123);
	SmartPtr<int> sp_int2 = new int(789);
	SmartPtr<int> sp_int3 = sp_int1;
	sp_int1 = sp_int2;
	cout << endl;
	cout << "--------------------Out test2---------------------" << endl;
}

void test3() {
	cout << "--------------------In test3----------------------" << endl;
	//测试引用计数
	int* p_int = new int();
	SmartPtr<int> sp_Outer = p_int;
	cout << "Ref Count (" << sp_Outer.get_ref_count() << ") outer 1." << endl;
	{
		SmartPtr<int> sp_Inner = sp_Outer;
		cout << "Ref Count (" << sp_Inner.get_ref_count() << ") inner." << endl;
	}
	cout << "Ref Count (" << sp_Outer.get_ref_count() << ") outer 2." << endl;
	SmartPtr<int> sp_Outer2 = new int();
	sp_Outer = sp_Outer2;// 1处new出来的int*将会被自动释放  
	cout << "Ref Count (" << sp_Outer.get_ref_count() << ") outer 2." << endl;
	cout << "--------------------Out test3---------------------" << endl;
}
void test4() {
	//测试解引用，判空和比较
{
	cout << "=======testcase4_1=========" << endl;
	SmartPtr<test_type> sp_tt = new test_type();
	(*sp_tt).func();
	sp_tt->func();
	cout << "==========================" << endl;
}
{	std::cout << "=======testcase4_2=========" << std::endl;
	test_type *p_tt = new test_type();
	SmartPtr<test_type> sp_tt = p_tt;

	SmartPtr<test_type> spo_tt = new test_type();
	SmartPtr<test_type> spo_tt2 = spo_tt;

	if (sp_tt == NULL) std::cout << "sp_tt is NULL pointer" << std::endl;
	if (sp_tt != NULL) std::cout << "sp_tt is not NULL pointer" << std::endl;
	if (sp_tt == p_tt)
	std::cout << "sp_tt and p_tt are same pointer" << std::endl;
	if (sp_tt != p_tt)
	std::cout << "sp_tt and p_tt are not same pointer" << std::endl;
	//     if (sp_tt != spo_tt) // ERROR !
	//        std::cout<< "sp_tt and spo_tt are not same pointer" << std::endl;
	//     if (sp_tt == spo_tt) // ERROR !
	//        std::cout<< "sp_tt and spo_tt are same pointer" << std::endl;
	if (spo_tt == spo_tt2) std::cout << "spo_tt and spo_tt2 are same pointer" << std::endl;
	if (spo_tt != spo_tt2) std::cout << "spo_tt and spo_tt2 are not same pointer" << std::endl;
	std::cout << "==========================" << std::endl;
}
}
void test() {
	test1();
	test2();
	test3();
	test4();
}

int main() {
#ifdef _WINDOWS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF):
#endif
	test();
	return 0;
}