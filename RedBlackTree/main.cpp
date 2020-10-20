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
������ inset ���� �� insertFixUp��leftRotate,rightRoate �д�������BUG��
�ƶϿ���������ת�� node �ڵ�Ϊ�գ������� insertFixUp ������� getParent()
��ɿ�ָ���쳣������
*/

/*
ɾ�����ֽڵ�֮��ǰ�������ʱ���֣�����һֱ���֣���ѭ��������ɾ��������ɾ����ĵ���������
����ָ��ָ��δ��ȷ���Ļ�����
������ɾ���ڵ��δ��ָ������ָ���޸�
*/

/*
���ڷ�����ɾ���ڵ��BUG!
*/
/***************************************************************************************************/



/**************************************************
 * ���²��Խ��������������ǲ��Գ��������!
 * ���ų�������BUG!
 * ��������ǲ��Ե����⣡����
 * ���Ե����뺯�������(99%)û������
 * ����Ӧ�ö��� eraseFixUp �У�������Ŀǰ���������� BUG!
 * 1.ĳЩ����·����� delete �ڵ�
 * 2.ĳЩ�����ĳ�����ڵ����ӳɻ���
 * 3.ĳЩ����·��ʽڵ�Ϊ nullptr 
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

	cout << "������� " << NUM << " ����" << endl;
	for (int i = 0; i < NUM; ++i)
		rbTree.insert(range(random));

	cout << "ǰ����� : ";
	rbTree.preOrder();
	cout << endl;

	cout << "������� : ";
	rbTree.inOrder();
	cout << endl;

	cout << "������� : ";
	rbTree.postOrder();
	cout << endl;

	cout << "������� : " << endl;
	rbTree.levelOrder();
	cout << endl;

	cout << "min : " << rbTree.min() << endl;
	cout << "max : " << rbTree.max() << endl;
	cout << "rbTree.empty() : " << std::boolalpha << rbTree.empty() << endl;

	vector<int> vec;
	vector<int> temp;
	const int delNum = NUM / 2;
	cout << "�������" << delNum << "������ : ";
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

	cout << "������ɾ������ : ";
	for (auto x : temp) cout << x << " ";
	cout << endl;

	cout << "ǰ����� : ";
	rbTree.preOrder();
	cout << endl;

	cout << "������� : ";
	rbTree.inOrder();
	cout << endl;

	cout << "������� : ";
	rbTree.postOrder();
	cout << endl;

	cout << "������� : " << endl;
	rbTree.levelOrder();
	cout << endl;

	if (rbTree.empty())
	{
		cout << "min : " << rbTree.min() << endl;
		cout << "max : " << rbTree.max() << endl;
	}

	cout << "== ��ϸ��Ϣ : " << endl;
	rbTree.print();

	cout << "���Խ�����" << endl;
	*/

	// ����2
	/*
	constexpr int TEST_NUM = 50;
	constexpr int MAX = 100;
	const auto order_test = [](const RBTree<int>& tree)->void
	{
		cout << "== ǰ����� : " << endl;
		tree.preOrder();
		cout << endl;

		cout << "== ������� : " << endl;
		tree.inOrder();
		cout << endl;

		cout << "== ������� : " << endl;
		tree.postOrder();
		cout << endl;

		cout << "== ������� : " << endl;
		tree.levelOrder();
		cout << endl;

		cout << "== ��ϸ��Ϣ���� : " << endl;
		tree.print();
		cout << endl;

		// �Ƿ���������
		cout << "isBST : " << std::boolalpha << tree.isBST() << endl;

		cout << "tree size = " << tree.size() << endl;
		cout << "tree hegiht = " << tree.height() << endl;
		cout << "================================================================" << endl;
	};

	// ɾ������
	const auto erase_test = [&](RBTree<int>& tree)->void
	{
		cout << "ɾ������1 : ɾ���̶�����" << endl;
		for (int i = 0; i < TEST_NUM / 2; ++i)
		{
			cout << i << " ";
			tree.erase(i);
		}
		cout << endl;

		int min = tree.min();
		int max = tree.max();
		int avg = min + max / 2;
		cout << "ɾ������2 : ɾ�� (min + max) / 2 = "
			<< "(" << min << " + " << max << ") / 2 = "
			<< avg << endl;

		cout << avg << " �Ƿ������� : " << std::boolalpha << tree.contains(avg) << endl;
		cout << "ɾ��ֵ : " << avg << endl;
		tree.erase(avg);
		cout << avg << " �Ƿ������� : " << std::boolalpha << tree.contains(avg) << endl;

		max = tree.max();
		cout << "ɾ������3 : ���(10��)ɾ��ĳ������ֵ max = "<< max << endl;
		cout << max << " �Ƿ������� : " << std::boolalpha << tree.contains(max) << endl;
		for (int i = 0; i < 10; ++i) tree.erase(max);
		cout << max << " �Ƿ������� : " << std::boolalpha << tree.contains(max) << endl;

		order_test(tree);
	};


	// �������
	{
		cout << "�������1 : �������ֵ" << endl;
		RBTree<int> tree;
		for (int i = 0; i < TEST_NUM; ++i) tree.insert(i);

		// ��������
		order_test(tree);

		// ɾ������
		erase_test(tree);
	}

	{
		cout << "�������2 : �������ֵ" << endl;
		RBTree<int> tree;
		for (int i = TEST_NUM - 1; i >= 0; --i) tree.insert(i);

		// ��������
		order_test(tree);
		// ɾ������
		erase_test(tree);
	}

	{
		cout << "�������3 : ������ظ�����ֵ" << endl;
		const int seed = time_point_cast<duration<int, std::milli>>(system_clock::now()).time_since_epoch().count();
		default_random_engine random(seed);
		uniform_int_distribution<int> range(0, MAX);
		set<int> set;
		for (int i = 0; i < TEST_NUM; ++i) set.insert(range(random));

		RBTree<int> tree;
		for (auto x : set) tree.insert(x);

		// ��������
		order_test(tree);
		// ɾ������
		erase_test(tree);
	}

	{
		cout << "�������4 : �������ֵ�����ܴ����ظ�ֵ��" << endl;
		const int seed = time_point_cast<duration<int, std::milli>>(system_clock::now()).time_since_epoch().count();
		default_random_engine random(seed);
		uniform_int_distribution<int> range(0, MAX);
		RBTree<int> tree;
		for (int i = 0; i < TEST_NUM; ++i) tree.insert(range(random));

		// ��������
		order_test(tree);
		// ɾ������
		erase_test(tree);
	}

	// ��������ɾ������
	{
		auto tree = RBTree<int>();
		cout << "tree is empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size = " << tree.size() << endl;
		cout << "tree height = " << tree.height() << endl;
		cout << "���� " << TEST_NUM * 100 << " �����ֵ : " << endl;

		const int seed = time_point_cast<duration<int, std::milli>>(system_clock::now()).time_since_epoch().count();
		default_random_engine random(seed);
		uniform_int_distribution<int> range(0, MAX * 100);
		for (int i = 0; i < TEST_NUM * 100; ++i) tree.insert(range(random));

		cout << "tree is empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size = " << tree.size() << endl;
		cout << "tree height = " << tree.height() << endl;
		cout << "����������Խ�����" << endl;
		cout << "===============================================================\n" << endl;

		cout << "ɾ�� " << TEST_NUM * 100 << "�����ֵ���� : " << endl;
		cout << "tree is empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size = " << tree.size() << endl;
		cout << "tree height = " << tree.height() << endl;

		for (int i = 0; i < TEST_NUM; ++i) tree.erase(range(random));

		cout << "tree is empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size = " << tree.size() << endl;
		cout << "tree height = " << tree.height() << endl;
		cout << "����ɾ�����Խ�����" << endl;
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
		cout << "���� " << TEST_NUM << " ��������ɣ�" << endl;
		cout << "tree empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size : " << tree.size() << endl;
		cout << "tree height : " << tree.height() << endl;
		cout << "=========================================\n" << endl;

		while (!tree.empty()) tree.erase(tree.min());
		cout << "tree ɾ����ɣ�" << endl;
		cout << "tree empty : " << std::boolalpha << tree.empty() << endl;
		cout << "tree size : " << tree.size() << endl;
		cout << "tree height : " << tree.height() << endl;
		cout << "=========================================\n" << endl;
	}

	return 0;
}