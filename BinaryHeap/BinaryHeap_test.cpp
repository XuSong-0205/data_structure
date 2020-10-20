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

		cout << "��������������������" << num << "�����ݵ���ȷ�Բ��Կ�ʼ ��������������������" << endl;

		cout << "�����СΪ : " << vec.size() << endl;
		cout << "BinaryHeap ��СΪ : " << binheap.size() << endl;
		cout << "priority_queue ��СΪ : " << prique.size() << endl;

		sort(vec.begin(), vec.end());
		cout << "ǰ 100 С��ֵΪ : " << endl;
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
		cout << "��ǰ�����СΪ : " << vec.size() << endl;
		cout << "��ǰBinaryHeap ��СΪ : " << binheap.size() << endl;
		cout << "��ǰpriority_queue ��СΪ : " << prique.size() << endl;

		cout << "��������������������" << num << "�����ݵ���ȷ�Բ��Խ��� ��������������������\n" << endl;
	};

	const auto Test = [&](int num)
	{
		BinaryHeap<int> binheap;
		priority_queue<int> prique;
		vector<int> vec(num, 0);

		for (auto& x : vec)
			x = Random(0, 100000000);

		cout << num << " �����������Կ�ʼ" << endl;
		cout << "��������������������������������������������������" << endl;
		cout << "|               |    ����	 |    ɾ��	 |" << endl;
		cout << "��������������������������������������������������" << endl;
		cout << "|   BinaryHeap  |";

		// ����
		time_t start_binheap = clock();
		for (auto x : vec)
			binheap.insert(x);
		time_t end_binheap = clock();
		cout << "    " << end_binheap - start_binheap << " ms	 |";

		// ɾ����С��
		start_binheap = clock();
		while (!binheap.empty())
			binheap.deleteMin();
		end_binheap = clock();
		cout << "    " << end_binheap - start_binheap << " ms	 |" << endl;

		cout << "��������������������������������������������������" << endl;
		cout << "| priority_queue|";

		// perority_queue ����
		// ���
		time_t start_prique = clock();
		for (auto x : vec)
			prique.push(x);
		time_t end_prique = clock();
		cout << "    " << end_prique - start_prique << " ms	 |";

		// ����
		start_prique = clock();
		while (!prique.empty())
			prique.pop();
		end_prique = clock();
		cout << "    " << end_prique - start_prique << " ms	 |" << endl;

		cout << "��������������������������������������������������" << endl;
		cout << num << " �����������Խ���...\n\n" << endl;

	};

	// ��ȷ�Բ���
	correctnessTest(test_num_one);
	correctnessTest(test_num_two);
	correctnessTest(test_num_three);

	// �ٶȲ���
	Test(test_num_one);
	Test(test_num_two);
	Test(test_num_three);

	cout << "���в����ѽ��������س�������..." << endl;
	cin.get();
	return 0;
}