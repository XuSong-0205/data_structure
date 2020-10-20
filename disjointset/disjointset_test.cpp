#include <iostream>
#include <random>
#include <chrono>
#include "Disjointset.h"
using std::cout;
using std::endl;
using std::default_random_engine;
using std::uniform_int_distribution;
using namespace std::chrono;

constexpr int TEST_NUM = 10000 * 10;

int main()
{
	const auto now = time_point_cast<milliseconds>(system_clock::now());
	const auto val = now.time_since_epoch().count() & 0xffffffff;
	default_random_engine random(val);
	const uniform_int_distribution<int> range(0, TEST_NUM - 1);
	Disjointset dis(TEST_NUM);

	const auto start = time_point_cast<milliseconds>(steady_clock::now());
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < TEST_NUM / 10; ++j)
		{
			const int a = range(random);
			const int b = range(random);

			// 查
			dis.find(a);
			dis.find(b);
			// 查询是否在同一集合内
			dis.isConnected(a, b);
			// 并
			dis.unionSets(a, b);
		}
	}
	const auto end = time_point_cast<milliseconds>(steady_clock::now());
	cout << "并查集 " << TEST_NUM << " 测试用时 : " << (end - start).count() << " ms" << endl;


	for (int i = 0; i < 100; ++i)
	{
		const int x = range(random);
		const int y = range(random);

		cout << endl;
		cout << "find(" << x << ") : \t" << dis.find(x) << "  根的深度为 : " << -dis.getData(x) << endl;
		cout << "find(" << y << ") : \t" << dis.find(y) << "  根的深度为 : " << -dis.getData(y) << endl;
		cout << "(" << x << "," << y << ") 在同一集合内 : " << std::boolalpha << dis.isConnected(x, y) << endl;
		dis.unionSets(x, y);
		cout << "合并" << "(" << x << "," << y << ") 后" << endl;
		cout << "find(" << x << ") : \t" << dis.find(x) << "  根的深度为 : " << -dis.getData(x) << endl;
		cout << "find(" << y << ") : \t" << dis.find(y) << "  根的深度为 : " << -dis.getData(y) << endl;
		cout << "(" << x << "," << y << ") 在同一集合内 : " << std::boolalpha << dis.isConnected(x, y) << endl;
	}

	return 0;
}