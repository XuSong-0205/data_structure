#include <iostream>
#include <vector>
#include "MyList.h"
using namespace std;


int main()
{
	MyList<int> list;
	cout << "list is empty : " << boolalpha << list.empty() << endl;
	cout << "list size : " << list.size() << endl;

	for (int i = 0; i < 10; ++i) list.insertTail(i);
	for (int i = 0; i < 10; ++i) list.insertHead(i);

	list.print();
	cout << endl;
	cout << "list is empty : " << boolalpha << list.empty() << endl;
	cout << "list size : " << list.size() << endl;

	for (int i = 0; i < 10; i += 3)
	{
		cout << list.printN(i) << " ";
	}
	cout << endl;

	cout << "3 在list中的位置为 : " << list.find(3) << endl;
	cout << "将 20 插入到第 5 个元素" << endl;
	list.insertIndex(20, 5);
	list.print();
	cout << endl;


	{
		MyList<int> list1;
		for (int i = 0; i < 200; ++i) list1.insertTail(i);
		cout << "list1 size : " << list1.size() << endl;
		cout << "输出 list1 : " << endl;
		list1.print();
		cout << endl;

		list = list1;
		cout << "list size : " << list.size() << endl;
		cout << "输出 list : " << endl;
		list.print();
		cout << endl;

		auto list2 = list;
		list2.insertHead(222);
		list2.insertTail(666);
		cout << "list2 size : " << list2.size() << endl;
		cout << "输出 list2 : " << endl;
		list2.print();
		cout << endl;
	}

	{
		cout << "移动构造函数测试 : " << endl;
		auto temp = list;
		auto list3 = std::move(temp);
		cout << "list3 size : " << list3.size() << endl;
		cout << "list3 is empty : " << boolalpha << list3.empty() << endl;
		cout << "输出 list3 : " << endl;
		list3.print();
		cout << endl;
	}

	{
		cout << "移动赋值运算符测试 : " << endl;
		auto temp = list;
		decltype(temp) list4;
		list4 = std::move(temp);
		cout << "list4 size : " << list4.size() << endl;
		cout << "list4 is empty : " << boolalpha << list4.empty() << endl;
		cout << "输出 list4 : " << endl;
		list4.print();
		cout << endl;
	}


	return 0;
}