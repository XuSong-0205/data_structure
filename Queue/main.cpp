#include <iostream>
#include "Queue.h"
using namespace std;

int main()
{
	Queue<int> que;
	cout << "push 10 ����" << endl;
	for (int i = 0; i < 10; ++i) que.push(i);
	que.print();
	cout << endl;
	cout << "que.front : " << que.front() << endl;
	cout << "que.size : " << que.size() << endl;
	cout << "que.empty : " << boolalpha << que.empty() << endl;

	cout << "\n�ٴ� push 20 ����" << endl;
	for (int i = 0; i < 20; ++i) que.push(i << 1);
	que.print();
	cout << endl;
	cout << "que.front : " << que.front() << endl;
	cout << "que.size : " << que.size() << endl;
	cout << "que.empty : " << boolalpha << que.empty() << endl;

	cout << "\npop 15 ����" << endl;
	for (int i = 0; i < 15; ++i) que.pop();
	que.print();
	cout << endl;
	cout << "que.front : " << que.front() << endl;
	cout << "que.size : " << que.size() << endl;
	cout << "que.empty : " << boolalpha << que.empty() << endl;

	cout << "\nһ�� pop һ�� push 10 ����" << endl;
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

	cout << "\n�ٴ� push 30 ����" << endl;
	for (int i = 0; i < 30; ++i) que.push(123);
	que.print();
	cout << endl;
	cout << "que.front : " << que.front() << endl;
	cout << "que.size : " << que.size() << endl;
	cout << "que.empty : " << boolalpha << que.empty() << endl;


	// �������캯������
	{
		cout << "\n�������캯������" << endl;
		auto que1 = que;
		que1.print();
		cout << endl;
		cout << "que1.front : " << que1.front() << endl;
		cout << "que1.size : " << que1.size() << endl;
		cout << "que1.empty : " << boolalpha << que1.empty() << endl;
	}

	// �ƶ����캯������
	{
		cout << "\n�ƶ����캯������" << endl;
		auto temp(que);
		auto que2(std::move(temp));
		que2.print();
		cout << endl;
		cout << "que2.front : " << que2.front() << endl;
		cout << "que2.size : " << que2.size() << endl;
		cout << "que2.empty : " << boolalpha << que2.empty() << endl;
	}

	// ������ֵ��������ز���
	{
		cout << "\n������ֵ��������ز���" << endl;
		Queue<int> que3;
		que3 = que;
		que3.print();
		cout << endl;
		cout << "que3.front : " << que3.front() << endl;
		cout << "que3.size : " << que3.size() << endl;
		cout << "que3.empty : " << boolalpha << que3.empty() << endl;
	}

	// �ƶ���ֵ��������ز���
	{
		cout << "\n�ƶ���ֵ��������ز���" << endl;
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