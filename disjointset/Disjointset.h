#pragma once
#include <vector>
using std::vector;

class Disjointset
{
private:
	vector<int> data;

public:
	explicit Disjointset(int n) :data(n)
	{
		std::fill(data.begin(), data.end(), -1);
	}

	/**
	 * 采用路径压缩进行一次 find 操作
	 */
	int find(int root)
	{
		if (data.at(root) < 0)
			return root;
		else
			return data.at(root) = find(data.at(root));
	}

	/**
	 * 合并两个并查集
	 */
	void unionSets(int r1, int r2)
	{
		const int root1 = find(r1);
		const int root2 = find(r2);
		if (root1 == root2)
			return;

		if (data.at(root2) < data.at(root1))			// root2 更深
			data.at(root1) = root2;						// root2 为新的根
		else
		{
			if (data.at(root1) == data.at(root2))
				--data.at(root1);						// 如果高度相同，则更新 root1 的高度
			data.at(root2) = root1;						// root1 为新的根
		}

	}

	/**
	 * 判断两元素是否在同一组内
	 */
	bool isConnected(int root1, int root2)
	{
		return find(root1) == find(root2);
	}

	/**
	 * 获取该元素根的大小
	 */
	int getData(int root)
	{
		return data.at(find(root));
	}
};

