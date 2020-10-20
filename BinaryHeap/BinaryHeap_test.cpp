#include "BinaryHeap.h"

int main()
{
	srand(time(nullptr) & 0xffffffff);
	const auto Random = [](int a, int b)noexcept ->int
	{
		return rand() * rand() % (b - a + 1) + a;
	};
	system("color 0A"); 

	constexpr int test_num_one = 10000;
	constexpr int test_num_two = 10000 * 10;
	constexpr int test_num_three = 10000 * 100;

	const auto correctnessTest = [&](int num)
	{
		BinaryHeap<int> binheap;
		priority_queue<int, vector<int>, std::greater<int>> prique;
		vector<int> vec(num, 0);

		for (auto& x : vec)
		{
			x = Random(0, 100000000);
			binheap.insert(x);
			prique.push(x);
		}

		cout << "——————————" << num << "个数据的正确性测试开始 ——————————" << endl;

		cout << "数组大小为 : " << vec.size() << endl;
		cout << "BinaryHeap 大小为 : " << binheap.size() << endl;
		cout << "priority_queue 大小为 : " << prique.size() << endl;

		sort(vec.begin(), vec.end());
		cout << "前 100 小的值为 : " << endl;
		int temp_binheap = 0;
		int temp_prique = 0;
		for (int k = 0; k < 10; ++k)
		{
			// vector
			cout << "vector :         ";
			for (int i = 0; i < 10; ++i)
			{
				cout << vec.at(k * 10 + i) << "	";
			}
			cout << endl;

			// BinaryHeap
			cout << "BinaryHeap :     ";
			for (int i = 0; i < 10; ++i)
			{
				binheap.deleteMin(temp_binheap);
				cout << temp_binheap << "	";
			}
			cout << endl;

			// priority_queue
			cout << "priority_queue : ";
			for (int i = 0; i < 10; ++i)
			{
				temp_prique = prique.top();
				prique.pop();
				cout << temp_prique << "	";
			}
			cout << endl;
		}
		
		cout << endl;
		cout << "当前数组大小为 : " << vec.size() << endl;
		cout << "当前BinaryHeap 大小为 : " << binheap.size() << endl;
		cout << "当前priority_queue 大小为 : " << prique.size() << endl;

		cout << "——————————" << num << "个数据的正确性测试结束 ——————————\n" << endl;
	};

	const auto Test = [&](int num)
	{
		BinaryHeap<int> binheap;
		priority_queue<int> prique;
		vector<int> vec(num, 0);

		for (auto& x : vec)
			x = Random(0, 100000000);

		cout << num << " 个数据量测试开始" << endl;
		cout << "—————————————————————————" << endl;
		cout << "|               |    插入	 |    删除	 |" << endl;
		cout << "—————————————————————————" << endl;
		cout << "|   BinaryHeap  |";

		// 插入
		time_t start_binheap = clock();
		for (auto x : vec)
			binheap.insert(x);
		time_t end_binheap = clock();
		cout << "    " << end_binheap - start_binheap << " ms	 |";

		// 删除最小项
		start_binheap = clock();
		while (!binheap.empty())
			binheap.deleteMin();
		end_binheap = clock();
		cout << "    " << end_binheap - start_binheap << " ms	 |" << endl;

		cout << "—————————————————————————" << endl;
		cout << "| priority_queue|";

		// perority_queue 测试
		// 入队
		time_t start_prique = clock();
		for (auto x : vec)
			prique.push(x);
		time_t end_prique = clock();
		cout << "    " << end_prique - start_prique << " ms	 |";

		// 出队
		start_prique = clock();
		while (!prique.empty())
			prique.pop();
		end_prique = clock();
		cout << "    " << end_prique - start_prique << " ms	 |" << endl;

		cout << "—————————————————————————" << endl;
		cout << num << " 个数据量测试结束...\n\n" << endl;

	};

	// 正确性测试
	correctnessTest(test_num_one);
	correctnessTest(test_num_two);
	correctnessTest(test_num_three);

	// 速度测试
	Test(test_num_one);
	Test(test_num_two);
	Test(test_num_three);

	cout << "所有测试已结束，按回车键继续..." << endl;
	cin.get();
	return 0;
}