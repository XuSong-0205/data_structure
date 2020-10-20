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
	 * 默认构造函数
	 */
	AVLTree()noexcept :root{ nullptr } 
	{

	}

	/**
	 * 拷贝构造函数
	 */
	AVLTree(const AVLTree& avl) :root{ nullptr }
	{
		root = clone(avl.root);
	}

	AVLTree(AVLTree&& avl) = default;
	AVLTree& operator=(AVLTree&& avl) = default;

	/**
	 * 析构函数
	 */
	~AVLTree()
	{
		makeEmpty();
	}

	/**
	 * 找出树中的最小项
	 */
	const T& findMin()const
	{
		return findMin(root)->element;
	}

	/**
	 * 找出树中的最大项
	 */
	const T& findMax()const
	{
		return findMax(root)->element;
	}

	/**
	 * 在树中查找是否存在 x ，若存在则返回 true
	 */
	bool contains(const T& x)const
	{
		return contains(x, root);
	}

	/**
	 * 判断树是否为空
	 */
	void isEmpty()const
	{
		return root == nullptr;
	}

	/**
	 * 遍历输出整棵树（中序遍历，按值从小到大输出）
	 */
	void printTree(ostream& out = cout)const
	{
		if (root == nullptr)
			out << "Empty tree!";
		else
			printTree(root, out);
	}

	/**
	 * 前序遍历输出整颗树
	 */
	void printDLRTree(ostream& out = cout)const
	{
		printDLRTree(root, out);
	}

	/**
	 * 后续遍历输出该树
	 */
	void printLRDTree(ostream& out = cout)const
	{
		printLRDTree(root, out);
	}


	/**
	 * 将 x 插入到树中，忽略重复元素
	 */
	void insert(const T& x)
	{
		insert(x, root);
	}

	/**
	 * 将 x 插入到树中，忽略重复元素
	 */
	void insert(T&& x)
	{
		insert(std::move(x), root);
	}

	/**
	 * 将 x 从树中删除，如果没找到 x ，则什么都不做
	 */
	void remove(const T& x)
	{
		remove(x, root);
	}

	/**
	 * 清空树
	 */
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/**
	 * 拷贝赋值
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
	 * 判断该树是否是AVL树,若是 AVL 树返回 true
	 */
	bool isAvlTree()const
	{
		return isAvlTree(root);
	}

	/**
	 * << 运算符重载，按值从小到大输出，中序遍历
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
	 * 返回节点 t 的高度，如果是 nullptr 则返回-1
	 */
	int height(const AvlNode* t)const noexcept
	{
		return t == nullptr ? -1 : t->height;
	}

	/**
	 * 判断该子树是否是AVL树的内部方法
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
	 * 像一颗子树进行插入的内部方法
	 * x 是要插入的项
	 * t 为该子树的根节点
	 * 置子树的新根
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
	 * 像一颗子树进行插入的内部方法
	 * x 是要插入的项
	 * t 为该子树的根节点
	 * 置子树的新根
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
	 * 假设 t 是平衡的，或与平衡相差不超过一
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


	/**     LL :            右旋转                                   LL :          右旋转
	 *   情形1 :  k2         ---->          k1                        3             ---->          2
	 *           /  \                      /  \                     /                            /    \
	 *          k1   z                    x    k2                 2                            1        3
	 *         /  \                           /  \               /
	 *        x    y                         y    z            1
	 */

	/**
	 * 用左儿子旋转二叉树的节点
	 * 这是对 AVL 树再情形 1 的一次单旋转
	 * 更新高度，然后设置新根
	 */
	void rotateWithLeftChild(AvlNode*& k2)noexcept		// 名字的 left right 代表那个儿子进行旋转 旋转方向为其名字的反向
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


	/**      LR :                                                              在 6 先左旋              再在 6 右旋     
	 *   情形 2 :     k3           ---->          k2                      8       ---->         8          ---->          8
	 *              /    \                      /    \                  /   \                 /   \                     /   \   
	 *            k1       d                  k1      k3              7      10             7      15                 6      15
	 *          /    \                      /   \    /  \           /                     /                         /   \
	 *        a        k2                 a      b  c     d       5                     6                         5       7
	 *               /    \                                         \                 /
	 *             b        c                                         6             5
	 *   注意 : 一次双旋转等于两次单旋转！
	 */

	/**
	 * 双旋转二叉树的节点：首先左儿子和它的右儿子进行
	 * 然后节点 k3 和新的左儿子进行
	 * 这是对 AVL 树情形 2 的一次双旋转
	 * 更新高度，然后设置新根
	 */
	void doubleWithLeftChild(AvlNode*& k3)       // 名字的 left right 代表那个儿子进行旋转 旋转方向为其名字反向
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	/**      RR :            左旋转                                LL :          左旋转
	 *   情形 3 :  k2         ---->          k1                     1             ---->          2
	 *            /  \                      /  \                      \                        /    \
	 *           x   k1                    k2   z                       2                    1        3
	 *              /  \                  /  \                            \
	 *             y    z                x    y                             3
	 */

	/**
	 * 用右儿子旋转二叉树的节点
	 * 这是对 AVL 树再情形 3 的一次单旋转
	 * 更新高度，然后设置新根
	 */
	void rotateWithRightChild(AvlNode*& k2)noexcept		// 名字的 left right 代表那个儿子进行旋转 旋转方向为其名字反向
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


	/**      RL :                                                              在 9 先右旋              再在 9 左旋
	 *   情形 4 :     k3           ---->          k2                      6       ---->         6          ---->          9
	 *              /    \                      /    \                  /   \                 /   \                     /   \
	 *			  a	      k1                  k3      k1              4      12             4       9                 6      12
	 *					/    \              /   \    /  \                  /    \                 /   \              / \    /  \
	 *                 k2      d           a     b  c     d              9       13              7     12           4   7  10  13
	 *               /    \                                            /   \                         /    \
	 *             b        c                                        7      10                     10      13
	 *   注意 : 一次双旋转等于两次单旋转！
	 */

	/**
	 * 双旋转二叉树的节点：首先右儿子和它的左儿子进行
	 * 然后节点 k3 和新的右儿子进行
	 * 这是对 AVL 树情形 4 的一次双旋转
	 * 更新高度，然后设置新根
	 */
	void doubleWithRightChild(AvlNode*& k3)		// 名字的 left right 代表那个儿子进行旋转 旋转方向为其名字反向
	{
		rotateWithLeftChild(k3->right);
		rotateWithRightChild(k3);
	}


	/**
	 * 从子树实施删除的内部方法
	 * x 是要被删除的项
	 * t 为该子树的根节点
	 * 设置该子树的新根
	 */
	void remove(const T& x, AvlNode*& t)
	{
		if (t == nullptr)
			return;			// 没发现要删除的项，什么也不做

		if (x < t->element)
			remove(x, t->left);
		else if (t->element < x)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr)		// 两个儿子
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else													// 一个儿子
		{
			AvlNode* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}

		balance(t);
	}

	/**
	 * 找出子树 t 中最小项的内部方法
	 * 返回包含最小项的节点
	 */
	AvlNode* findMin(AvlNode* t)const
	{
		if (t != nullptr)
			while (t->left != nullptr)
				t = t->left;
		return t;
	}

	/**
	 * 找出子树 t 上最大项的内部方法
	 * 返回包含最大想的节点
	 */
	AvlNode* findMax(AvlNode* t)const
	{
		if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;
	}

	/**
	 * 测试一项是否在子树的内部方法
	 * x 是要查找的项
	 * t 是作为该子树的根的节点
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
				return true;		// 匹配
		}

		return false;
	}

	/**
	 * 使子树为空的内部方法
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
	 * 打印整棵树的内部方法
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
	 * 后续遍历输出该子树的内部方法
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
	 * 以前序遍历的方式输出整颗子树
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
	 * 克隆子树的内部方法
	 */
	AvlNode* clone(AvlNode* t)const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new AvlNode{ t->element,clone(t->left),clone(t->right) };
	}

};