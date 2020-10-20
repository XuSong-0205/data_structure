#include <iostream>
#include "Dqeue.h"
using std::cout;
using std::endl;

int main()
{
	Deque<int> deq;
	for (int i = 0; i < 10; ++i)
	{
		deq.push_front(-i);
		deq.push_back(i);
	}

	cout << "push -10 ~ 0, 0 ~10" << endl;
	deq.print();
	cout << "deq empty : " << std::boolalpha << deq.empty() << endl;
	cout << "deq size : " << deq.size() << endl;
	cout << "deq front : " << deq.front() << endl;
	cout << "deq back : " << deq.back() << endl;

	deq.pop_front();
	deq.pop_back();
	cout << "\npop_front pop_back " << endl;
	deq.print();
	cout << "deq empty : " << std::boolalpha << deq.empty() << endl;
	cout << "deq size : " << deq.size() << endl;
	cout << "deq front : " << deq.front() << endl;
	cout << "deq back : " << deq.back() << endl;

	{
		{
			cout << "¿½±´¹¹Ôìº¯Êý²âÊÔ : " << endl;
			auto deq1 = deq;
			deq1.print();
		}

		{
			cout << "ÒÆ¶¯¹¹Ôìº¯Êý²âÊÔ : " << endl;
			auto temp = deq;
			auto deq2 = std::move(temp);
			deq2.print();
		}

		{
			cout << "¿½±´¸³ÖµÔËËã·û²âÊÔ : " << endl;
			Deque<int> deq3;
			deq3 = deq;
			deq3.print();
		}

		{
			cout << "ÒÆ¶¯¸³ÖµÔËËã·û²âÊÔ : " << endl;
			auto temp = deq;
			Deque<int> deq4;
			deq4 = std::move(temp);
			deq4.print();
		}
	}

	return 0;
}