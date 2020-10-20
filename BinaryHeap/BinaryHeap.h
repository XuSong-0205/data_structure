#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::priority_queue;

template<typename Comparable>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 100)noexcept :heapArray(capacity) {}
	explicit BinaryHeap(const vector<Comparable>& items)
		:heapArray(items.size()+10),currentSize(items.size())
	{
		for (int i = 0; i < items.size(); ++i)
		{
			heapArray.at(i + 1) = items.at(i);
		}
		buildHeap();
	}

	bool empty()const noexcept
	{
		return currentSize == 0;
	}
	const Comparable& findMin()const
	{
		return heapArray.at(1);
	}

	/**
	 * 将项 x 插入，允许重复元
	 */
	void insert(const Comparable& x)
	{
		if (currentSize == heapArray.size() - 1)
			heapArray.resize(heapArray.size() * 2);

		// 上滤
		int hole = ++currentSize;
		Comparable copy = x;

		heapArray.at(0) = std::move(copy);
		for (; x < heapArray.at(hole / 2); hole /= 2)
			heapArray.at(hole) = std::move(heapArray.at(hole / 2));

		heapArray.at(hole) = std::move(heapArray.at(0));
	}

	void insert(Comparable&& x)
	{
		if (currentSize == heapArray.size() - 1)
			heapArray.resize(heapArray.size() * 2);

		// 上滤
		int hole = ++currentSize;

		heapArray.at(0) = std::move(x);
		for (; x < heapArray.at(hole / 2); hole /= 2)
			heapArray.at(hole) = std::move(heapArray.at(hole / 2));

		heapArray.at(hole) = std::move(heapArray.at(0));
	}

	/**
	 * 删除最小项
	 * 若为空则抛出异常
	 */
	void deleteMin()
	{
		if (empty())
			throw "The BinaryHeap is empty...";

		heapArray.at(1) = std::move(heapArray.at(currentSize--));
		percolateDown(1);
	}

	/**
	 * 删除最小项并将其放在 minItem 处
	 * 若为空则抛出异常
	 */
	void deleteMin(Comparable& minItem)
	{
		if(empty())
			throw "The BinaryHeap is empty...";

		minItem = std::move(heapArray.at(1));
		heapArray.at(1) = std::move(heapArray.at(currentSize--));
		percolateDown(1);
	}

	/**
	 * 将堆置空
	 */
	void makeEmpty()
	{
		heapArray.clear();
		currentSize = 0;
	}

	size_t size()const noexcept
	{
		return currentSize;
	}
private:
	int currentSize = 0;			// 堆中元素的个数
	vector<Comparable> heapArray;	// 堆的数组

	/**
	 * 从项的任何一排列建立堆序性质
	 * 以线性时间运行
	 */
	void buildHeap()
	{
		for (int i = currentSize / 2; i > 0; --i)
			percolateDown(i);
	}

	/**
	 * 从堆中进行下滤的内部方法
	 * 空穴是下滤开始处的下标
	 */
	void percolateDown(int hole)
	{
		int child = 0;
		Comparable temp = std::move(heapArray.at(hole));

		for (; hole * 2 <= currentSize; hole = child)
		{
			child = hole * 2;
			if (child != currentSize && heapArray.at(child + 1) < heapArray.at(child))
				++child;
			if (heapArray.at(child) < temp)
				heapArray.at(hole) = std::move(heapArray.at(child));
			else
				break;
		}
		heapArray.at(hole) = std::move(temp);
	}
};

