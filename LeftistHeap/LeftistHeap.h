#pragma once
#include <stdexcept>
#include <iostream>
using std::ostream;

template<typename Comparable>
class LeftistHeap
{
public:
	/**
	 * 默认构造函数
	 */
	LeftistHeap()noexcept :root{ nullptr } {}

	/**
	 * 拷贝构造函数
	 */
	LeftistHeap(const LeftistHeap& rhs) 
	{
		root = clone(rhs.root); 
	}

	/**
	 * 移动构造函数
	 */
	LeftistHeap(LeftistHeap&& rhs) 
	{
		root = rhs.root;
		rhs.root = nullptr;
	}

	/**
	 * 析构函数
	 */
	~LeftistHeap() 
	{ 
		makeEmpty(); 
	}

	/**
	 * 拷贝赋值
	 * rhs 必须不同于 this
	 */
	LeftistHeap& operator=(const LeftistHeap& rhs)
	{
		if (this == &rhs)
			return *this;

		makeEmpty();
		root = clone(rhs->root);
		return *this;
	}

	/**
	 * 移动赋值
	 * rhs 必须不同于 this
	 */
	LeftistHeap& operator=(LeftistHeap&& rhs)
	{
		if (this == &rhs)
			return *this;

		makeEmpty();
		root = rhs.root;
		rhs.root = nullptr;
	}

	/**
	 * 输出流运算符重载
	 * 按值的大小依序输出
	 */
	friend ostream& operator<<(ostream& os, const LeftistHeap& rhs)
	{
		LeftistHeap heap(rhs);
		while (!heap.isEmpty())
		{
			os << heap.findMin() << " ";
			heap.deleteMin();
		}
		return os;
	}

	/**
	 * 判断 LeftistHeap 是否为空
	 */
	bool isEmpty()const noexcept
	{ 
		return root == nullptr; 
	}

	/**
	 * 判断左式堆是否成立的方法
	 * 返回 true 或 false
	 */
	bool isLeftistHeap()const
	{
		return isLeftistHeap(root);
	}

	/**
	 * 查找最小项
	 * 若为空，则抛出 underflow_error 异常
	 */
	const Comparable& findMin()const
	{
		if (isEmpty())
			throw std::underflow_error("The LeftistHeap is empty.");

		return root->element;
	}

	/**
	 * 打印输出左式堆
	 * 按大小排序输出
	 */
	void print()const
	{
		std::cout << *this << std::endl;
	}

	/**
	 * 插入 x，允许项重复
	 */
	void insert(const Comparable& x)
	{
		root = merge(new LeftistNode(x), root);
	}

	/**
	 * 插入 x，允许项重复
	 */
	void insert(Comparable&& x)
	{
		root = merge(new LeftistNode(std::move(x)), root);
	}

	/**
	 * 删除最小项
	 * 若为空，则抛出 underflow_error 异常
	 */
	void deleteMin()
	{
		if (isEmpty())
			throw std::underflow_error("The LeftistHeap is empty.");

		LeftistNode* oldRoot = root;
		root = merge(root->left, root->right);
		delete oldRoot;
	}

	/**
	 * 删除最小项
	 * 若为空，则抛出 underflow_error 异常
	 */
	void deleteMin(Comparable& minItem)
	{
		minItem = findMin();
		deleteMin();
	}

	/**
	 * 使 LeftistHeap 为空
	 */
	void makeEmpty()
	{
		reclaimMemory(root);
		root = nullptr;
	}

	/**
	 * 将 rhs 合并到优先队列
	 * rhs 变为空，rhs 必须不同于 this
	 */
	void merge(LeftistHeap& rhs) 
	{
		if (this == &rhs)
			return;

		root = merge(root, rhs.root);
		rhs.root = nullptr;
	}


private:
	struct LeftistNode
	{
		Comparable element;
		LeftistNode* left;
		LeftistNode* right;
		int npl;

		LeftistNode(const Comparable& e, LeftistNode* lt = nullptr,
			LeftistNode* rt = nullptr,int np = 0)
			:element{ e }, left{ lt }, right{ rt }, npl{ np }{}

		LeftistNode(Comparable&& e,LeftistNode* lt = nullptr,
			LeftistNode* rt = nullptr,int np = 0)
			:element{ std::move(e) }, left{ lt }, right{ rt }, npl{ np }{}
	};

	LeftistNode* root;

	/**
	 * 获取左式堆的 npl 长的方法
	 * nullptr 的 npl 为 -1
	 */
	int getNpl(LeftistNode* node)const
	{
		if (node == nullptr)
			return -1;

		return node->npl;
	}

	/**
	 * 判断左式堆是否成立的实现
	 * 返回 true 或 false
	 */
	bool isLeftistHeap(LeftistNode* node)const
	{
		if (node == nullptr)
			return true;

		return isLeftistHeap(node->left) && isLeftistHeap(node->right) &&
			getNpl(node->left) >= getNpl(node->right);
	}

	/**
	 * 合并两个根的内部方法
	 * 处理不正常情形并调用递归的 merge1
	 */
	LeftistNode* merge(LeftistNode* h1, LeftistNode* h2)
	{
		if (h1 == nullptr)
			return h2;
		if (h2 == nullptr)
			return h1;
		if (h1->element < h2->element)
			return merge1(h1, h2);
		else
			return merge1(h2, h1);
	}

	/**
	 * 合并两个根的内部方法
	 * 假设树非空，并设 h1 的根包含最小项
	 */
	LeftistNode* merge1(LeftistNode* h1, LeftistNode* h2)
	{
		if (h1->left == nullptr)		// 单节点
			h1->left = h2;				// h1 中其他的域已经精确
		else
		{
			h1->right = merge(h1->right, h2);
			if (h1->left->npl < h1->right->npl)
				swapChildren(h1);
			h1->npl = h1->right->npl + 1;
		}
		return h1;
	}

	/**
	 * 交换树左右子树的方法
	 */
	void swapChildren(LeftistNode* t)noexcept
	{
		if (t == nullptr)
			return;

		std::swap(t->left, t->right);
	}

	/**
	 * 释放树内存的方法
	 */
	void reclaimMemory(LeftistNode* t)
	{
		if (t == nullptr)
			return;

		reclaimMemory(t->left);
		reclaimMemory(t->right);
		delete t;
	}

	/**
	 * 克隆树的方法
	 */
	LeftistNode* clone(LeftistNode* t)const
	{
		if (t == nullptr)
			return nullptr;

		return new LeftistNode(t->element, clone(t->left), clone(t->right), t->npl);
	}
};