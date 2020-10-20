#include "AVLTree.h"

constexpr int data = 10000 * 100;

int main()
{
	srand(time(nullptr) & 0xffffffff);
	system("color 0A");
	AVLTree<int> avl;
	
	const auto RANDOM_INT = [](int x, int y) noexcept ->int
	{
		return rand() * rand() % (y - x) + x + 1;
	};
	const auto INSERT = [&](int num)
	{
		for (int i = 0; i < num; ++i)
		{
			avl.insert(RANDOM_INT(0, 1000000000));
		}
	};
	const auto REMOVE = [&]()
	{
		avl.makeEmpty();
	};

	time_t totalTime_insert = 0;
	time_t totalTime_remove = 0;
	
	for (int i = 0; i < 10; ++i)
	{
		cout << "第 " << i + 1 << " 次" << endl;
	
		cout << "After insert : \n";
		time_t start = clock();
		INSERT(data);		
		time_t end = clock();
		cout << "Spend time : " << end - start << "ms" << endl;
		totalTime_insert += end - start;
	
		const auto ISTRUE = [](bool t)->string {return t ? "true" : "false"; };
		cout << "该树是否是 AVL 树 : " << ISTRUE(avl.isAvlTree()) << endl;
	
		cout << "After makeEmpty : \n";
		start = clock();
		REMOVE();
		end = clock();
		cout << "Spend time : " << end - start << "ms" << endl;
		totalTime_remove += end - start;
		cout << avl << endl;
		cout << endl;
	}
	
	cout << "十次 " << data << " (" << data / 10000 << ")万 数据的插入操作平均用时 : " 
		<< totalTime_insert / 10.0 << " ms" << endl;
	cout << "十次 " << data << " (" << data / 10000 << ")万 数据的删除操作平均用时 : " 
		<< totalTime_remove / 10.0 << " ms" << endl;
	return 0;
}