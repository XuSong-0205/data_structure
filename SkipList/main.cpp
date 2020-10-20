#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <set>
#include "SkipList.h"
using namespace std;
using namespace std::chrono;


int main()
{
	{
		vector<int> vec;
		for (int i = 0; i < 10; ++i) vec.push_back(i);
		cout << "vec : ";
		for (auto x : vec) cout << x << " ";
		cout << endl;

		SkipList<int> skip;
		cout << "�Ȳ������� : ";
		for (int i = 1; i < 10; i += 2) skip.insert(i);
		for (auto x : skip) cout << x << " ";
		cout << endl;

		cout << "skip size : " << skip.size() << endl;
		cout << "�ٲ���ż�� : ";
		for (int i = 0; i < 10; i += 2) skip.insert(i);
		for (auto x : skip) cout << x << " ";
		cout << endl;
		cout << "skip size : " << skip.size() << endl;

		{
			cout << "�������캯������ : ";
			auto skip1 = skip;
			for (auto x : skip1) cout << x << " ";
			cout << endl;

			cout << "ɾ������ : ";
			for (int i = 0; i < 10; i += 2) skip1.erase(i);
			for (auto x : skip1) cout << x << " ";
			cout << endl;
		}

		{
			cout << "�ƶ����캯������ : ";
			auto temp = skip;
			auto skip2 = std::move(temp);
			for (auto x : skip2) cout << x << " ";
			cout << endl;
		}

		{
			cout << "������ֵ��������ز��� : ";
			SkipList<int> skip3;
			skip3 = skip;
			for (auto x : skip3) cout << x << " ";
			cout << endl;
		}

		{
			cout << "�ƶ���ֵ��������ز��� : ";
			auto temp = skip;
			SkipList<int> skip4;
			skip4 = std::move(temp);
			for (auto x : skip4) cout << x << " ";
			cout << endl;
		}

		cout << "\n\n���������� : ";
		for (auto x : skip) cout << x << " ";
		cout << endl;


		cout << "\n������ϣ�" << endl;

	}


	{
		cout << "\n\n\n" << endl;

		constexpr int TEST_NUM = 10000 * 500;
		const auto seed = static_cast<int>(duration_cast<milliseconds>
						(steady_clock::now().time_since_epoch()).count());
		default_random_engine engine(seed);
		uniform_int_distribution<int> range(0, TEST_NUM);
		vector<int> vec;
		for (int i = 0; i < TEST_NUM; ++i) vec.push_back(range(engine));
		auto start = time_point_cast<milliseconds>(steady_clock::now());
		sort(vec.begin(), vec.end());
		auto end = time_point_cast<milliseconds>(steady_clock::now());
		cout << "vec size : " << vec.size() << " ������ʱ : "
			<< (end - start).count() << " ms" << endl;

		// SkipList
		{
			SkipList<int> skip;
			{
				SkipList<int> temp;
				start = time_point_cast<milliseconds>(steady_clock::now());
				for (const auto& x : vec) temp.insert(x);
				end = time_point_cast<milliseconds>(steady_clock::now());
				cout << "temp size : " << temp.size() << " ������ʱ : "
					<< (end - start).count() << " ms" << endl;
				skip = temp;
			}

			cout << "���Ҳ��� : " << endl;
			start = time_point_cast<milliseconds>(steady_clock::now());
			for (const auto& x : vec) skip.find(x);
			end = time_point_cast<milliseconds>(steady_clock::now());
			cout << "������ʱ : " << (end - start).count() << " ms" << endl;

			cout << "ɾ��һ����� : " << endl;
			start = time_point_cast<milliseconds>(steady_clock::now());
			for (size_t i = 0; i < vec.size() >> 1; ++i) skip.erase(vec.at(i));
			end = time_point_cast<milliseconds>(steady_clock::now());
			cout << "ɾ����ʱ : " << (end - start).count() << " ms" << endl;

			cout << "���Ҳ��� : " << endl;
			start = time_point_cast<milliseconds>(steady_clock::now());
			for (const auto& x : vec) skip.find(x);
			end = time_point_cast<milliseconds>(steady_clock::now());
			cout << "������ʱ : " << (end - start).count() << " ms" << endl;

			cout << "ɾ��һ����� : " << endl;
			start = time_point_cast<milliseconds>(steady_clock::now());
			for (size_t i = vec.size() >> 1; i < vec.size(); ++i) skip.erase(vec.at(i));
			end = time_point_cast<milliseconds>(steady_clock::now());
			cout << "ɾ����ʱ : " << (end - start).count() << " ms" << endl;
			cout << "skip size : " << skip.size() << endl;
			cout << "skip empty : " << boolalpha << skip.empty() << endl;
		}

		// multiset
		{
			multiset<int> myset;
			start = time_point_cast<milliseconds>(steady_clock::now());
			for (const auto& x : vec) myset.insert(x);
			end = time_point_cast<milliseconds>(steady_clock::now());
			cout << "myset size : " << myset.size() << " ������ʱ : "
				<< (end - start).count() << " ms" << endl;

			cout << "���Ҳ��� : " << endl;
			start = time_point_cast<milliseconds>(steady_clock::now());
			for (const auto& x : vec) auto temp = myset.find(x);
			end = time_point_cast<milliseconds>(steady_clock::now());
			cout << "������ʱ : " << (end - start).count() << " ms" << endl;

			cout << "ɾ������ : " << endl;
			start = time_point_cast<milliseconds>(steady_clock::now());
			for (size_t i = 0; i < vec.size() >> 1; ++i) myset.erase(vec.at(i));
			end = time_point_cast<milliseconds>(steady_clock::now());
			cout << "ɾ����ʱ : " << (end - start).count() << " ms" << endl;

			cout << "���Ҳ��� : " << endl;
			start = time_point_cast<milliseconds>(steady_clock::now());
			for (const auto& x : vec) auto temp = myset.find(x);
			end = time_point_cast<milliseconds>(steady_clock::now());
			cout << "������ʱ : " << (end - start).count() << " ms" << endl;

			cout << "ɾ������ : " << endl;
			start = time_point_cast<milliseconds>(steady_clock::now());
			for (size_t i = vec.size() >> 1; i < vec.size(); ++i) myset.erase(vec.at(i));
			end = time_point_cast<milliseconds>(steady_clock::now());
			cout << "ɾ����ʱ : " << (end - start).count() << " ms" << endl;
			cout << "myset size : " << myset.size() << endl;
			cout << "myset empty : " << boolalpha << myset.empty() << endl;
		}
	}


	return 0;
}