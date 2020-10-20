#pragma once
#include <stdexcept>
#include <iostream>
using std::ostream;

template<typename Comparable>
class LeftistHeap
{
public:
	/**
	 * Ĭ�Ϲ��캯��
	 */
	LeftistHeap()noexcept :root{ nullptr } {}

	/**
	 * �������캯��
	 */
	LeftistHeap(const LeftistHeap& rhs) 
	{
		root = clone(rhs.root); 
	}

	/**
	 * �ƶ����캯��
	 */
	LeftistHeap(LeftistHeap&& rhs) 
	{
		root = rhs.root;
		rhs.root = nullptr;
	}

	/**
	 * ��������
	 */
	~LeftistHeap() 
	{ 
		makeEmpty(); 
	}

	/**
	 * ������ֵ
	 * rhs ���벻ͬ�� this
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
	 * �ƶ���ֵ
	 * rhs ���벻ͬ�� this
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
	 * ��������������
	 * ��ֵ�Ĵ�С�������
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
	 * �ж� LeftistHeap �Ƿ�Ϊ��
	 */
	bool isEmpty()const noexcept
	{ 
		return root == nullptr; 
	}

	/**
	 * �ж���ʽ���Ƿ�����ķ���
	 * ���� true �� false
	 */
	bool isLeftistHeap()const
	{
		return isLeftistHeap(root);
	}

	/**
	 * ������С��
	 * ��Ϊ�գ����׳� underflow_error �쳣
	 */
	const Comparable& findMin()const
	{
		if (isEmpty())
			throw std::underflow_error("The LeftistHeap is empty.");

		return root->element;
	}

	/**
	 * ��ӡ�����ʽ��
	 * ����С�������
	 */
	void print()const
	{
		std::cout << *this << std::endl;
	}

	/**
	 * ���� x���������ظ�
	 */
	void insert(const Comparable& x)
	{
		root = merge(new LeftistNode(x), root);
	}

	/**
	 * ���� x���������ظ�
	 */
	void insert(Comparable&& x)
	{
		root = merge(new LeftistNode(std::move(x)), root);
	}

	/**
	 * ɾ����С��
	 * ��Ϊ�գ����׳� underflow_error �쳣
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
	 * ɾ����С��
	 * ��Ϊ�գ����׳� underflow_error �쳣
	 */
	void deleteMin(Comparable& minItem)
	{
		minItem = findMin();
		deleteMin();
	}

	/**
	 * ʹ LeftistHeap Ϊ��
	 */
	void makeEmpty()
	{
		reclaimMemory(root);
		root = nullptr;
	}

	/**
	 * �� rhs �ϲ������ȶ���
	 * rhs ��Ϊ�գ�rhs ���벻ͬ�� this
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
	 * ��ȡ��ʽ�ѵ� npl ���ķ���
	 * nullptr �� npl Ϊ -1
	 */
	int getNpl(LeftistNode* node)const
	{
		if (node == nullptr)
			return -1;

		return node->npl;
	}

	/**
	 * �ж���ʽ���Ƿ������ʵ��
	 * ���� true �� false
	 */
	bool isLeftistHeap(LeftistNode* node)const
	{
		if (node == nullptr)
			return true;

		return isLeftistHeap(node->left) && isLeftistHeap(node->right) &&
			getNpl(node->left) >= getNpl(node->right);
	}

	/**
	 * �ϲ����������ڲ�����
	 * �����������β����õݹ�� merge1
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
	 * �ϲ����������ڲ�����
	 * �������ǿգ����� h1 �ĸ�������С��
	 */
	LeftistNode* merge1(LeftistNode* h1, LeftistNode* h2)
	{
		if (h1->left == nullptr)		// ���ڵ�
			h1->left = h2;				// h1 �����������Ѿ���ȷ
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
	 * ���������������ķ���
	 */
	void swapChildren(LeftistNode* t)noexcept
	{
		if (t == nullptr)
			return;

		std::swap(t->left, t->right);
	}

	/**
	 * �ͷ����ڴ�ķ���
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
	 * ��¡���ķ���
	 */
	LeftistNode* clone(LeftistNode* t)const
	{
		if (t == nullptr)
			return nullptr;

		return new LeftistNode(t->element, clone(t->left), clone(t->right), t->npl);
	}
};