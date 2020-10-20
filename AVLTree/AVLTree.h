#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <ctime>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::function;

#define max(x,y) ((x)>(y)?(x):(y))

template<typename T>
class AVLTree
{
public:
	/**
	 * Ĭ�Ϲ��캯��
	 */
	AVLTree()noexcept :root{ nullptr } 
	{

	}

	/**
	 * �������캯��
	 */
	AVLTree(const AVLTree& avl) :root{ nullptr }
	{
		root = clone(avl.root);
	}

	AVLTree(AVLTree&& avl) = default;
	AVLTree& operator=(AVLTree&& avl) = default;

	/**
	 * ��������
	 */
	~AVLTree()
	{
		makeEmpty();
	}

	/**
	 * �ҳ����е���С��
	 */
	const T& findMin()const
	{
		return findMin(root)->element;
	}

	/**
	 * �ҳ����е������
	 */
	const T& findMax()const
	{
		return findMax(root)->element;
	}

	/**
	 * �����в����Ƿ���� x ���������򷵻� true
	 */
	bool contains(const T& x)const
	{
		return contains(x, root);
	}

	/**
	 * �ж����Ƿ�Ϊ��
	 */
	void isEmpty()const
	{
		return root == nullptr;
	}

	/**
	 * ��������������������������ֵ��С���������
	 */
	void printTree(ostream& out = cout)const
	{
		if (root == nullptr)
			out << "Empty tree!";
		else
			printTree(root, out);
	}

	/**
	 * ǰ��������������
	 */
	void printDLRTree(ostream& out = cout)const
	{
		printDLRTree(root, out);
	}

	/**
	 * ���������������
	 */
	void printLRDTree(ostream& out = cout)const
	{
		printLRDTree(root, out);
	}


	/**
	 * �� x ���뵽���У������ظ�Ԫ��
	 */
	void insert(const T& x)
	{
		insert(x, root);
	}

	/**
	 * �� x ���뵽���У������ظ�Ԫ��
	 */
	void insert(T&& x)
	{
		insert(std::move(x), root);
	}

	/**
	 * �� x ������ɾ�������û�ҵ� x ����ʲô������
	 */
	void remove(const T& x)
	{
		remove(x, root);
	}

	/**
	 * �����
	 */
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/**
	 * ������ֵ
	 */
	AVLTree& operator=(const AVLTree& avl)
	{
		if (this != &avl)
		{
			AvlNode* temp = clone(avl.root);
			makeEmpty();
			root = temp;
		}
		return *this;
	}

	/**
	 * �жϸ����Ƿ���AVL��,���� AVL ������ true
	 */
	bool isAvlTree()const
	{
		return isAvlTree(root);
	}

	/**
	 * << ��������أ���ֵ��С����������������
	 */
	friend ostream& operator<<(ostream& out, const AVLTree& avl)
	{
		avl.printTree(out);
		return out;
	}

private:
	struct AvlNode
	{
		T element;
		AvlNode* left;
		AvlNode* right;
		int height;

		AvlNode(const T& ele, AvlNode* lt, AvlNode* rt, int h = 0)
			:element{ ele }, left{ lt }, right{ rt }, height{ h }{}

		AvlNode(T&& ele, AvlNode* lt, AvlNode* rt, int h = 0)noexcept
			:element{ std::move(ele) }, left{ lt }, right{ rt }, height{ h }{}
	};

	AvlNode* root;
	static const int ALLOWED_IMBALANCE = 1;

	/**
	 * ���ؽڵ� t �ĸ߶ȣ������ nullptr �򷵻�-1
	 */
	int height(const AvlNode* t)const noexcept
	{
		return t == nullptr ? -1 : t->height;
	}

	/**
	 * �жϸ������Ƿ���AVL�����ڲ�����
	 */
	bool isAvlTree(AvlNode* t)const
	{
		if (t != nullptr)
		{
			if (!isAvlTree(t->left))
				return false;
			if (!isAvlTree(t->right))
				return false;
			return abs(height(t->left) - height(t->right)) <= 1;
		}
		return true;
	}

	/**
	 * ��һ���������в�����ڲ�����
	 * x ��Ҫ�������
	 * t Ϊ�������ĸ��ڵ�
	 * ���������¸�
	 */ 
	void insert(const T& x, AvlNode*& t)
	{
		if (t == nullptr)
			t = new AvlNode{ x,nullptr,nullptr };
		else if (x < t->element)
			insert(x, t->left);
		else if (t->element < x)
			insert(x, t->right);

		balance(t);
	}

	/**
	 * ��һ���������в�����ڲ�����
	 * x ��Ҫ�������
	 * t Ϊ�������ĸ��ڵ�
	 * ���������¸�
	 */
	void insert(T&& x, AvlNode*& t)
	{
		if (t == nullptr)
			t = new AvlNode{ std::move(x),nullptr,nullptr };
		else if (x < t->element)
			insert(std::move(x), t->left);
		else if (t->element < x)
			insert(std::move(x), t->right);

		balance(t);
	}

	/**
	 * ���� t ��ƽ��ģ�����ƽ��������һ
	 */
	void balance(AvlNode*& t)
	{
		if (t == nullptr)
			return;
		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
		{
			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		}
		else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
		{
			if (height(t->right->right) >= height(t->right->left))
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);
		}

		t->height = max(height(t->left), height(t->right)) + 1;
	}


	/**     LL :            ����ת                                   LL :          ����ת
	 *   ����1 :  k2         ---->          k1                        3             ---->          2
	 *           /  \                      /  \                     /                            /    \
	 *          k1   z                    x    k2                 2                            1        3
	 *         /  \                           /  \               /
	 *        x    y                         y    z            1
	 */

	/**
	 * ���������ת�������Ľڵ�
	 * ���Ƕ� AVL �������� 1 ��һ�ε���ת
	 * ���¸߶ȣ�Ȼ�������¸�
	 */
	void rotateWithLeftChild(AvlNode*& k2)noexcept		// ���ֵ� left right �����Ǹ����ӽ�����ת ��ת����Ϊ�����ֵķ���
	{
		if (k2 == nullptr)
			return;
		AvlNode* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}


	/**      LR :                                                              �� 6 ������              ���� 6 ����     
	 *   ���� 2 :     k3           ---->          k2                      8       ---->         8          ---->          8
	 *              /    \                      /    \                  /   \                 /   \                     /   \   
	 *            k1       d                  k1      k3              7      10             7      15                 6      15
	 *          /    \                      /   \    /  \           /                     /                         /   \
	 *        a        k2                 a      b  c     d       5                     6                         5       7
	 *               /    \                                         \                 /
	 *             b        c                                         6             5
	 *   ע�� : һ��˫��ת�������ε���ת��
	 */

	/**
	 * ˫��ת�������Ľڵ㣺��������Ӻ������Ҷ��ӽ���
	 * Ȼ��ڵ� k3 ���µ�����ӽ���
	 * ���Ƕ� AVL ������ 2 ��һ��˫��ת
	 * ���¸߶ȣ�Ȼ�������¸�
	 */
	void doubleWithLeftChild(AvlNode*& k3)       // ���ֵ� left right �����Ǹ����ӽ�����ת ��ת����Ϊ�����ַ���
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	/**      RR :            ����ת                                LL :          ����ת
	 *   ���� 3 :  k2         ---->          k1                     1             ---->          2
	 *            /  \                      /  \                      \                        /    \
	 *           x   k1                    k2   z                       2                    1        3
	 *              /  \                  /  \                            \
	 *             y    z                x    y                             3
	 */

	/**
	 * ���Ҷ�����ת�������Ľڵ�
	 * ���Ƕ� AVL �������� 3 ��һ�ε���ת
	 * ���¸߶ȣ�Ȼ�������¸�
	 */
	void rotateWithRightChild(AvlNode*& k2)noexcept		// ���ֵ� left right �����Ǹ����ӽ�����ת ��ת����Ϊ�����ַ���
	{
		if (k2 == nullptr)
			return;
		AvlNode* k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(k2->height, height(k1->right)) + 1;
		k2 = k1;
	}


	/**      RL :                                                              �� 9 ������              ���� 9 ����
	 *   ���� 4 :     k3           ---->          k2                      6       ---->         6          ---->          9
	 *              /    \                      /    \                  /   \                 /   \                     /   \
	 *			  a	      k1                  k3      k1              4      12             4       9                 6      12
	 *					/    \              /   \    /  \                  /    \                 /   \              / \    /  \
	 *                 k2      d           a     b  c     d              9       13              7     12           4   7  10  13
	 *               /    \                                            /   \                         /    \
	 *             b        c                                        7      10                     10      13
	 *   ע�� : һ��˫��ת�������ε���ת��
	 */

	/**
	 * ˫��ת�������Ľڵ㣺�����Ҷ��Ӻ���������ӽ���
	 * Ȼ��ڵ� k3 ���µ��Ҷ��ӽ���
	 * ���Ƕ� AVL ������ 4 ��һ��˫��ת
	 * ���¸߶ȣ�Ȼ�������¸�
	 */
	void doubleWithRightChild(AvlNode*& k3)		// ���ֵ� left right �����Ǹ����ӽ�����ת ��ת����Ϊ�����ַ���
	{
		rotateWithLeftChild(k3->right);
		rotateWithRightChild(k3);
	}


	/**
	 * ������ʵʩɾ�����ڲ�����
	 * x ��Ҫ��ɾ������
	 * t Ϊ�������ĸ��ڵ�
	 * ���ø��������¸�
	 */
	void remove(const T& x, AvlNode*& t)
	{
		if (t == nullptr)
			return;			// û����Ҫɾ�����ʲôҲ����

		if (x < t->element)
			remove(x, t->left);
		else if (t->element < x)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr)		// ��������
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else													// һ������
		{
			AvlNode* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}

		balance(t);
	}

	/**
	 * �ҳ����� t ����С����ڲ�����
	 * ���ذ�����С��Ľڵ�
	 */
	AvlNode* findMin(AvlNode* t)const
	{
		if (t != nullptr)
			while (t->left != nullptr)
				t = t->left;
		return t;
	}

	/**
	 * �ҳ����� t ���������ڲ�����
	 * ���ذ��������Ľڵ�
	 */
	AvlNode* findMax(AvlNode* t)const
	{
		if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;
	}

	/**
	 * ����һ���Ƿ����������ڲ�����
	 * x ��Ҫ���ҵ���
	 * t ����Ϊ�������ĸ��Ľڵ�
	 */
	bool contains(const T& x,AvlNode* t)const
	{
		while (t != nullptr)
		{
			if (x < t->element)
				t = t->left;
			else if (t->element < x)
				t = t->right;
			else
				return true;		// ƥ��
		}

		return false;
	}

	/**
	 * ʹ����Ϊ�յ��ڲ�����
	 */
	void makeEmpty(AvlNode*& t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	/**
	 * ��ӡ���������ڲ�����
	 */
	void printTree(AvlNode* t, ostream& out)const
	{
		if (t != nullptr)
		{
			printTree(t->left, out);
			out << t->element << " ";
			printTree(t->right, out);
		}
	}

	/**
	 * ��������������������ڲ�����
	 */
	void printLRDTree(AvlNode* t, ostream& out)const
	{
		if (t != nullptr)
		{
			printLRDTree(t->left, out);
			printLRDTree(t->right, out);
			out << t->element << " ";
		}
	}

	/**
	 * ��ǰ������ķ�ʽ�����������
	 */
	void printDLRTree(AvlNode* t, ostream& out)const
	{
		if (t != nullptr)
		{
			out << t->element << " ";
			printDLRTree(t->left, out);
			printDLRTree(t->right, out);
		}
	}

	/**
	 * ��¡�������ڲ�����
	 */
	AvlNode* clone(AvlNode* t)const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new AvlNode{ t->element,clone(t->left),clone(t->right) };
	}

};