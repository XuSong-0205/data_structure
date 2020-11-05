#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "RedBlackTree.h"
using std::cout;
using std::endl;
using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;
using namespace std::chrono;


int main()
{
	constexpr int TEST_NUM = 10000 * 500;
	constexpr int MAX = 10000 * 100000;

	RBTree<int> tree;

	{
		const int seed = time_point_cast<duration<int, std::milli>>(system_clock::now()).time_since_epoch().count();
		default_random_engine random(seed);
		uniform_int_distribution<int> range(0, MAX);

		auto start = std::chrono::time_point_cast<milliseconds>(steady_clock::now());
		for (int i = 0; i < TEST_NUM; ++i) tree.insert(range(random));
		auto end = std::chrono::time_point_cast<milliseconds>(steady_clock::now());

		cout << "插入 " << TEST_NUM << " 个数据完成！" << endl;
		cout << "插入用时 : " << (end - start).count() << " ms" << endl;
		cout << "tree empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size : " << tree.size() << endl;
		cout << "tree height : " << tree.height() << endl;
		cout << "tree is RBTree : " << std::boolalpha << tree.isRBBST() << endl;
		cout << "======================================================\n" << endl;

		int num = 0;
		start = std::chrono::time_point_cast<milliseconds>(steady_clock::now());
		for (const auto& x : tree) num = x;
		end = std::chrono::time_point_cast<milliseconds>(steady_clock::now());
		cout << "迭代用时 : " << (end - start).count() << " ms\n" << endl;

		int size = tree.size();
		start = std::chrono::time_point_cast<milliseconds>(steady_clock::now());
		for (int i = 0; i < size; ++i) tree.erase(tree.min());
		end = std::chrono::time_point_cast<milliseconds>(steady_clock::now());

		cout << "tree 删除完成！" << endl;
		cout << "删除用时 : " << (end - start).count() << " ms" << endl;
		cout << "tree empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size : " << tree.size() << endl;
		cout << "tree height : " << tree.height() << endl;
		cout << "tree is RBTree : " << std::boolalpha << tree.isRBBST() << endl;
		cout << "======================================================\n\n" << endl;
	}


	for (int i = 0; i < 1000; ++i)
	{
		tree.insert(i);
	}

	{
		auto tree1 = tree;
		tree1.inOrder();
		cout << "tree1 is RBTree : " << std::boolalpha << tree1.isRBBST() << endl;
	}

	{
		auto temp = tree;
		auto tree2 = std::move(temp);
		tree2.inOrder();
		cout << "tree2 is RBTree : " << std::boolalpha << tree2.isRBBST() << endl;
	}

	{
		RBTree<int> tree3;
		tree3 = tree;
		tree3.inOrder();
		cout << "tree3 is RBTree : " << std::boolalpha << tree3.isRBBST() << endl;
	}

	{
		auto temp = tree;
		RBTree<int> tree4;
		tree4 = std::move(temp);
		tree4.inOrder();
		cout << "tree4 is RBTree : " << std::boolalpha << tree4.isRBBST() << endl;
	}

	cout << "tree 迭代器遍历 : " << endl;
	for (auto& x : tree) cout << x << " ";
	cout << endl;

	auto it = tree.begin();
	tree.erase(it);


	return 0;
}