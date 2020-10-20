#include <iostream>
#include "Queue.h"
using namespace std;

int main()
{
	Queue<int> que;
	cout << "push 10 个数" << endl;
	for (int i = 0; i < 10; ++i) que.push(i);
	que.print();
	cout << endl;
	cout << "que.front : " << que.front() << endl;
	cout << "que.size : " << que.size() << endl;
	cout << "que.empty : " << boolalpha << que.empty() << endl;

	cout << "\n再次 push 20 个数" << endl;
	for (int i = 0; i < 20; ++i) que.push(i << 1);
	que.print();
	cout << endl;
	cout << "que.front : " << que.front() << endl;
	cout << "que.size : " << que.size() << endl;
	cout << "que.empty : " << boolalpha << que.empty() << endl;

	cout << "\npop 15 个数" << endl;
	for (int i = 0; i < 15; ++i) que.pop();
	que.print();
	cout << endl;
	cout << "que.front : " << que.front() << endl;
	cout << "que.size : " << que.size() << endl;
	cout << "que.empty : " << boolalpha << que.empty() << endl;

	cout << "\n一边 pop 一边 push 10 个数" << endl;
	for (int i = 0; i < 10; ++i)
	{
		que.pop();
		que.push(i * 10);
	}
	que.print();
	cout << endl;
	cout << "que.front : " << que.front() << endl;
	cout << "que.size : " << que.size() << endl;
	cout << "que.empty : " << boolalpha << que.empty() << endl;

	cout << "\n再次 push 30 个数" << endl;
	for (int i = 0; i < 30; ++i) que.push(123);
	que.print();
	cout << endl;
	cout << "que.front : " << que.front() << endl;
	cout << "que.size : " << que.size() << endl;
	cout << "que.empty : " << boolalpha << que.empty() << endl;


	// 拷贝构造函数测试
	{
		cout << "\n拷贝构造函数测试" << endl;
		auto que1 = que;
		que1.print();
		cout << endl;
		cout << "que1.front : " << que1.front() << endl;
		cout << "que1.size : " << que1.size() << endl;
		cout << "que1.empty : " << boolalpha << que1.empty() << endl;
	}

	// 移动构造函数测试
	{
		cout << "\n移动构造函数测试" << endl;
		auto temp(que);
		auto que2(std::move(temp));
		que2.print();
		cout << endl;
		cout << "que2.front : " << que2.front() << endl;
		cout << "que2.size : " << que2.size() << endl;
		cout << "que2.empty : " << boolalpha << que2.empty() << endl;
	}

	// 拷贝赋值运算符重载测试
	{
		cout << "\n拷贝赋值运算符重载测试" << endl;
		Queue<int> que3;
		que3 = que;
		que3.print();
		cout << endl;
		cout << "que3.front : " << que3.front() << endl;
		cout << "que3.size : " << que3.size() << endl;
		cout << "que3.empty : " << boolalpha << que3.empty() << endl;
	}

	// 移动赋值运算符重载测试
	{
		cout << "\n移动赋值运算符重载测试" << endl;
		auto temp = que;
		Queue<int> que4;
		que4 = std::move(temp);
		que4.print();
		cout << endl;
		cout << "que4.front : " << que4.front() << endl;
		cout << "que4.size : " << que4.size() << endl;
		cout << "que4.empty : " << boolalpha << que4.empty() << endl;
	}


	return 0;
}