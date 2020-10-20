#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include "RedBlackTree.h"
using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;
using namespace std::chrono;

/***************************************************************************************************/
/*
测试在 inset 函数 或 insertFixUp，leftRotate,rightRoate 中存在严重BUG！
推断可能是树旋转后 node 节点为空，调用了 insertFixUp 后调用了 getParent()
造成空指针异常！！！
*/

/*
删除部分节点之后前序遍历有时出现（不是一直出现）死循环，疑似删除操作或删除后的调整操作后
部分指针指向未正确更改或有误！
可能是删除节点后未将指向它的指针修改
*/

/*
存在访问已删除节点的BUG!
*/
/***************************************************************************************************/



/**************************************************
 * 最新测试结果表明，大概率是测试程序的问题!
 * 不排除程序还有BUG!
 * 极大可能是测试的问题！！！
 * 测试到插入函数大概率(99%)没有问题
 * 问题应该都在 eraseFixUp 中，截至到目前测试有以下 BUG!
 * 1.某些情况下访问已 delete 节点
 * 2.某些情况下某几个节点连接成环！
 * 3.某些情况下访问节点为 nullptr 
 **************************************************/






int main()
{
	/*
	constexpr int NUM = 400;
	constexpr int MAX = 10000;
	const int seed = time_point_cast<duration<int, std::milli>>(system_clock::now()).time_since_epoch().count();
	default_random_engine random(seed);
	uniform_int_distribution<int> range(0, MAX);

	RBTree<int> rbTree;
	cout << "rbTree.empty() : " << std::boolalpha << rbTree.empty() << endl;

	cout << "随机插入 " << NUM << " 个数" << endl;
	for (int i = 0; i < NUM; ++i)
		rbTree.insert(range(random));

	cout << "前序遍历 : ";
	rbTree.preOrder();
	cout << endl;

	cout << "中序遍历 : ";
	rbTree.inOrder();
	cout << endl;

	cout << "后序遍历 : ";
	rbTree.postOrder();
	cout << endl;

	cout << "层序遍历 : " << endl;
	rbTree.levelOrder();
	cout << endl;

	cout << "min : " << rbTree.min() << endl;
	cout << "max : " << rbTree.max() << endl;
	cout << "rbTree.empty() : " << std::boolalpha << rbTree.empty() << endl;

	vector<int> vec;
	vector<int> temp;
	const int delNum = NUM / 2;
	cout << "随机生成" << delNum << "个数字 : ";
	for (int i = 0; i < delNum; ++i) vec.push_back(range(random));
	for (auto x : vec) cout << x << " ";
	cout << endl;

	for (auto x : vec)
	{
		if (rbTree.contains(x))
		{
			temp.push_back(x);
			rbTree.erase(x);
		}
	}

	cout << "从树中删除的有 : ";
	for (auto x : temp) cout << x << " ";
	cout << endl;

	cout << "前序遍历 : ";
	rbTree.preOrder();
	cout << endl;

	cout << "中序遍历 : ";
	rbTree.inOrder();
	cout << endl;

	cout << "后序遍历 : ";
	rbTree.postOrder();
	cout << endl;

	cout << "层序遍历 : " << endl;
	rbTree.levelOrder();
	cout << endl;

	if (rbTree.empty())
	{
		cout << "min : " << rbTree.min() << endl;
		cout << "max : " << rbTree.max() << endl;
	}

	cout << "== 详细信息 : " << endl;
	rbTree.print();

	cout << "测试结束！" << endl;
	*/

	// 测试2
	/*
	constexpr int TEST_NUM = 50;
	constexpr int MAX = 100;
	const auto order_test = [](const RBTree<int>& tree)->void
	{
		cout << "== 前序遍历 : " << endl;
		tree.preOrder();
		cout << endl;

		cout << "== 中序遍历 : " << endl;
		tree.inOrder();
		cout << endl;

		cout << "== 后序遍历 : " << endl;
		tree.postOrder();
		cout << endl;

		cout << "== 层序遍历 : " << endl;
		tree.levelOrder();
		cout << endl;

		cout << "== 详细信息测试 : " << endl;
		tree.print();
		cout << endl;

		// 是否是树测试
		cout << "isBST : " << std::boolalpha << tree.isBST() << endl;

		cout << "tree size = " << tree.size() << endl;
		cout << "tree hegiht = " << tree.height() << endl;
		cout << "================================================================" << endl;
	};

	// 删除测试
	const auto erase_test = [&](RBTree<int>& tree)->void
	{
		cout << "删除测试1 : 删除固定序列" << endl;
		for (int i = 0; i < TEST_NUM / 2; ++i)
		{
			cout << i << " ";
			tree.erase(i);
		}
		cout << endl;

		int min = tree.min();
		int max = tree.max();
		int avg = min + max / 2;
		cout << "删除测试2 : 删除 (min + max) / 2 = "
			<< "(" << min << " + " << max << ") / 2 = "
			<< avg << endl;

		cout << avg << " 是否在树中 : " << std::boolalpha << tree.contains(avg) << endl;
		cout << "删除值 : " << avg << endl;
		tree.erase(avg);
		cout << avg << " 是否在树中 : " << std::boolalpha << tree.contains(avg) << endl;

		max = tree.max();
		cout << "删除测试3 : 多次(10次)删除某个给定值 max = "<< max << endl;
		cout << max << " 是否在树中 : " << std::boolalpha << tree.contains(max) << endl;
		for (int i = 0; i < 10; ++i) tree.erase(max);
		cout << max << " 是否在树中 : " << std::boolalpha << tree.contains(max) << endl;

		order_test(tree);
	};


	// 插入测试
	{
		cout << "插入测试1 : 升序插入值" << endl;
		RBTree<int> tree;
		for (int i = 0; i < TEST_NUM; ++i) tree.insert(i);

		// 遍历测试
		order_test(tree);

		// 删除测试
		erase_test(tree);
	}

	{
		cout << "插入测试2 : 降序插入值" << endl;
		RBTree<int> tree;
		for (int i = TEST_NUM - 1; i >= 0; --i) tree.insert(i);

		// 遍历测试
		order_test(tree);
		// 删除测试
		erase_test(tree);
	}

	{
		cout << "插入测试3 : 随机无重复插入值" << endl;
		const int seed = time_point_cast<duration<int, std::milli>>(system_clock::now()).time_since_epoch().count();
		default_random_engine random(seed);
		uniform_int_distribution<int> range(0, MAX);
		set<int> set;
		for (int i = 0; i < TEST_NUM; ++i) set.insert(range(random));

		RBTree<int> tree;
		for (auto x : set) tree.insert(x);

		// 遍历测试
		order_test(tree);
		// 删除测试
		erase_test(tree);
	}

	{
		cout << "插入测试4 : 随机插入值（可能存在重复值）" << endl;
		const int seed = time_point_cast<duration<int, std::milli>>(system_clock::now()).time_since_epoch().count();
		default_random_engine random(seed);
		uniform_int_distribution<int> range(0, MAX);
		RBTree<int> tree;
		for (int i = 0; i < TEST_NUM; ++i) tree.insert(range(random));

		// 遍历测试
		order_test(tree);
		// 删除测试
		erase_test(tree);
	}

	// 大量插入删除测试
	{
		auto tree = RBTree<int>();
		cout << "tree is empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size = " << tree.size() << endl;
		cout << "tree height = " << tree.height() << endl;
		cout << "插入 " << TEST_NUM * 100 << " 个随机值 : " << endl;

		const int seed = time_point_cast<duration<int, std::milli>>(system_clock::now()).time_since_epoch().count();
		default_random_engine random(seed);
		uniform_int_distribution<int> range(0, MAX * 100);
		for (int i = 0; i < TEST_NUM * 100; ++i) tree.insert(range(random));

		cout << "tree is empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size = " << tree.size() << endl;
		cout << "tree height = " << tree.height() << endl;
		cout << "大量插入测试结束！" << endl;
		cout << "===============================================================\n" << endl;

		cout << "删除 " << TEST_NUM * 100 << "个随机值测试 : " << endl;
		cout << "tree is empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size = " << tree.size() << endl;
		cout << "tree height = " << tree.height() << endl;

		for (int i = 0; i < TEST_NUM; ++i) tree.erase(range(random));

		cout << "tree is empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size = " << tree.size() << endl;
		cout << "tree height = " << tree.height() << endl;
		cout << "大量删除测试结束！" << endl;
		cout << "===============================================================\n" << endl;
	}
	*/


	{
		constexpr int TEST_NUM = 10000;
		constexpr int MAX = 10000;
		const int seed = time_point_cast<duration<int, std::milli>>(system_clock::now()).time_since_epoch().count();
		default_random_engine random(seed);
		uniform_int_distribution<int> range(0, MAX);

		RBTree<int> tree;
		for (int i = 0; i < TEST_NUM; ++i) tree.insert(range(random));
		cout << "插入 " << TEST_NUM << " 个数据完成！" << endl;
		cout << "tree empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size : " << tree.size() << endl;
		cout << "tree height : " << tree.height() << endl;
		cout << "=========================================\n" << endl;

		while (!tree.empty()) tree.erase(tree.min());
		cout << "tree 删除完成！" << endl;
		cout << "tree empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size : " << tree.size() << endl;
		cout << "tree height : " << tree.height() << endl;
		cout << "=========================================\n" << endl;
	}

	return 0;
}