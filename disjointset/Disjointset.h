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
	 * ����·��ѹ������һ�� find ����
	 */
	int find(int root)
	{
		if (data.at(root) < 0)
			return root;
		else
			return data.at(root) = find(data.at(root));
	}

	/**
	 * �ϲ��������鼯
	 */
	void unionSets(int r1, int r2)
	{
		const int root1 = find(r1);
		const int root2 = find(r2);
		if (root1 == root2)
			return;

		if (data.at(root2) < data.at(root1))			// root2 ����
			data.at(root1) = root2;						// root2 Ϊ�µĸ�
		else
		{
			if (data.at(root1) == data.at(root2))
				--data.at(root1);						// ����߶���ͬ������� root1 �ĸ߶�
			data.at(root2) = root1;						// root1 Ϊ�µĸ�
		}

	}

	/**
	 * �ж���Ԫ���Ƿ���ͬһ����
	 */
	bool isConnected(int root1, int root2)
	{
		return find(root1) == find(root2);
	}

	/**
	 * ��ȡ��Ԫ�ظ��Ĵ�С
	 */
	int getData(int root)
	{
		return data.at(find(root));
	}
};

