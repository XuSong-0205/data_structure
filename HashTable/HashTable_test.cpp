#include "HashTable.h"

int main()
{
	system("color 0A");

	constexpr int test_num_one = 50000;
	constexpr int test_num_two = 50000 * 10;
	constexpr int test_num_three = 50000 * 100;

	const auto Test = [&](int num)
	{
		HashTable<int> myhashtable;
		unordered_set<int> stlhashtable;

		default_random_engine random(time(nullptr) & 0xffffffff);
		const uniform_int_distribution<int> range(0, 100000000);

		vector<int> vec(num, 0);
		for (size_t i = 0; i < vec.size(); ++i)
			vec.at(i) = random();

		cout << num << " �����������Կ�ʼ" << endl;
		cout << "����������������������������������������������������������������-" << endl;
		cout << "|               |   ����	|   ����	|   ɾ��	|" << endl;
		cout << "����������������������������������������������������������������-" << endl;
		cout << "|   HashTable   |";

		// ����
		time_t start_myhashtable = clock();
		for (auto x : vec)
			myhashtable.insert(x);
		time_t end_myhashtable = clock();
		cout << "   " << end_myhashtable - start_myhashtable << " ms	|";

		// ����
		int findnum = 0;
		start_myhashtable = clock();
		for (auto x : vec)
			if (myhashtable.contains(x))
				++findnum;
		end_myhashtable = clock();
		cout << "   " << end_myhashtable - start_myhashtable << " ms	|";

		// ɾ��
		int delenum = 0;
		start_myhashtable = clock();
		for (auto x : vec)
			if (myhashtable.remove(x))
				++delenum;
		end_myhashtable = clock();
		cout << "   " << end_myhashtable - start_myhashtable << " ms	|" << endl;


		// STL ����
		cout << "����������������������������������������������������������������-" << endl;
		cout << "| unordered_set |";

		// ���� 
		time_t start_stlhashtable = clock();
		for (auto x : vec)
			stlhashtable.insert(x);
		time_t end_stlhashtable = clock();
		cout << "   " << end_stlhashtable - start_stlhashtable << " ms	|";

		// ����
		findnum = 0;
		start_stlhashtable = clock();
		for (auto x : vec)
			if (stlhashtable.count(x))
				++findnum;
		end_stlhashtable = clock();
		cout << "   " << end_stlhashtable - start_stlhashtable << " ms	|";

		// ɾ��
		delenum = 0;
		start_stlhashtable = clock();
		for (auto x : vec)
			if (stlhashtable.erase(x))
				++delenum;
		end_stlhashtable = clock();
		cout << "   " << end_stlhashtable - start_stlhashtable << " ms	|" << endl;
		cout << "����������������������������������������������������������������-" << endl;

		cout << num << " �����������Խ���...\n" << endl;
	};

	Test(test_num_one);
	Test(test_num_two);
	Test(test_num_three);

	cout << "���в��Խ��������س����˳�..." << endl;
	cin.get();
	return 0;
}