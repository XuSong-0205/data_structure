#ifndef _REDBLACKTREE_H_
#define _REDBLACKTREE_H_

#include <iomanip>
#include <iostream>
#include <functional>
#include <exception>
#include <stack>
#include <queue>
using std::cout;
using std::endl;
using std::setw;
using std::stack;
using std::queue;
using std::function;


// 类模板前置声明
template<typename T>
class RedBlackTree;

// 类模板别名
template<typename T>
using RBTree = RedBlackTree<T>;


template<typename T>
class RedBlackTree
{
private:
	enum RBColor { RED, BLACK };

	struct RBNode
	{
	private:
		RBNode* parent;
		RBColor color;

	public:
		T key;
		RBNode* left;
		RBNode* right;

		RBNode(const T& k, RBColor c = RED, RBNode* l = nullptr, 
			RBNode* r = nullptr, RBNode* p = nullptr)
			:key(k), left(l), right(r), parent(p), color(c) {}

		RBNode(T&& k, RBColor c = RED, RBNode* l = nullptr,
			RBNode* r = nullptr, RBNode* p = nullptr)
			:key(std::move(k)), left(l), right(r), parent(p), color(c) {}

		void setParent(RBNode* par)
		{
			this->parent = par;
		}

		RBNode* getParent()const
		{
			return this->parent;
		}

		void setColor(RBColor c)
		{
			this->color = c;
		}

		RBColor getColor()const
		{
			return this->color;
		}
	};

	RBNode* _root = nullptr;
	size_t  _size = 0;

	friend class const_iterator;
	friend class iterator;

private:
	void printColorKey(const RBNode* node)const
	{
		cout << "\033[" << (node->getColor() == BLACK ? "30m" : "31m")
			<< node->key << "\033[0m ";
	}

	// 非递归前序遍历
	void preOrder(const RBNode* node, const function<void(const RBNode*)>& func)const
	{
		stack<const RBNode*> sta;
		while (node || !sta.empty())
		{
			while (node)
			{
				func(node);

				sta.push(node);
				node = node->left;
			}

			node = sta.top();
			sta.pop();
			node = node->right;
		}
		cout << endl;
	}

	// 非递归中序遍历
	void inOrder(const RBNode* node, const function<void(const RBNode*)>& func)const
	{
		stack<const RBNode*> sta;
		while (node || !sta.empty())
		{
			while (node)
			{
				sta.push(node);
				node = node->left;
			}
			node = sta.top();
			sta.pop();

			func(node);

			node = node->right;
		}
		cout << endl;
	}

	// 非递归后序遍历
	void postOrder(const RBNode* node, const function<void(const RBNode*)>& func)const
	{
		const RBNode* prev = nullptr;
		stack<const RBNode*> sta;
		while (node || !sta.empty())
		{
			while (node)
			{
				sta.push(node);
				node = node->left;
			}
			node = sta.top();

			if (!node->right || node->right == prev)
			{
				sta.pop();

				func(node);

				prev = node;
				node = nullptr;
			}
			else
			{
				node = node->right;
			}
		}
		cout << endl;
	}

	// 层序遍历
	void levelOrder(const RBNode* node, const function<void(const RBNode*)>& func)const
	{
		if (!node) return;

		queue<const RBNode*> que;
		que.push(node);
		while (!que.empty())
		{
			const int size = que.size();
			for (int i = 0; i < size; ++i)
			{
				node = que.front();
				que.pop();

				func(node);

				if (node->left) que.push(node->left);
				if (node->right) que.push(node->right);
			}
			cout << "\n";
		}
	}

	RBNode* clone(const RBNode* node)
	{
		if (node)
		{
			RBNode* curr = new RBNode(node->key, node->getColor(), clone(node->left), clone(node->right), nullptr);
			if (curr->left)  curr->left->setParent(curr);
			if (curr->right) curr->right->setParent(curr);
			return curr;

		}
		else
		{
			return nullptr;
		}
	}

	void makeEmpty(RBNode*& node)
	{
		if (node)
		{
			makeEmpty(node->left);
			makeEmpty(node->right);
			delete node;
			node = nullptr;
		}
	}

	RBNode* search(RBNode* node, const T& key)
	{
		while (node && node->key != key)
		{
			if (key < node->key) node = node->left;
			else node = node->right;
		}

		return node;
	}

	RBNode* min(RBNode* node)const
	{
		if (!node) return node;

		while (node->left)
		{
			node = node->left;
		}
		return node;
	}

	RBNode* max(RBNode* node)const
	{
		if (!node) return node;

		while (node->right)
		{
			node = node->right;
		}
		return node;
	}

	void leftRotate(RBNode* x)
	{
		RBNode* y = x->right;
		x->right = y->left;
		
		if (y->left != nullptr)
		{
			y->left->setParent(x);
		}

		y->setParent(x->getParent());
		if (x->getParent() == nullptr) 
		{
			_root = y;
		}
		else 
		{
			if (x == x->getParent()->left)
			{
				x->getParent()->left = y;
			}
			else 
			{
				x->getParent()->right = y;
			}

		}

		y->left = x;
		x->setParent(y);
	}

	void rightRotate(RBNode* y)
	{
		RBNode* x = y->left;
		y->left = x->right;

		if (x->right != nullptr) 
		{
			x->right->setParent(y);
		}

		x->setParent(y->getParent());

		if (y->getParent() == nullptr) 
		{
			_root = x;
		}
		else 
		{
			if (y == y->getParent()->left) 
			{
				y->getParent()->left = x;
			}
			else 
			{
				y->getParent()->right = x;
			}
		}

		x->right = y;
		y->setParent(x);
	}

	void insert(const T& key, bool isMove) 
	{
		RBNode* prev = nullptr;
		RBNode* curr = _root;
		while (curr)
		{
			prev = curr;
			if (key == curr->key) return;
			else if (key < curr->key) curr = curr->left;
			else if (key > curr->key) curr = curr->right;
		}

		auto node = isMove ? new RBNode(std::move(key)) : new RBNode(key);
		if (!node) return;
		node->setParent(prev);
		++_size;

		if (prev)
		{
			if (node->key < prev->key)	prev->left  = node;
			else						prev->right = node;
		}
		else
		{
			node->setColor(BLACK);
			_root = node;
			return;
		}

		while (node->getParent() && node->getParent()->getColor() == RED && node->getParent() != _root)
		{
			auto par = node->getParent();
			auto gpa = par->getParent();
			bool parIsRight = gpa->right == par ? true : false;
			auto uncle = parIsRight ? gpa->left : gpa->right;
			if (uncle && uncle->getColor() == RED)
			{
				par->setColor(BLACK); 
				uncle->setColor(BLACK);
				gpa->setColor(RED);
				node = gpa;
				continue;
			}
			else
			{
				parIsRight  && node == par->left  ? rightRotate(par) : void();
				!parIsRight && node == par->right ? leftRotate(par)  : void();
				parIsRight ? par = gpa->right : par = gpa->left;
				parIsRight ? leftRotate(gpa) : rightRotate(gpa);
				gpa->setColor(RED);
				par->setColor(BLACK);
				return;
			}
		}

		_root->setColor(BLACK);
	}

	void erase(RBNode* node)
	{
		if (node->getColor() == RED)
		{
			if (!node->left && !node->right)
			{
				auto par = node->getParent();
				par->left == node ? par->left = nullptr : par->right = nullptr;
				delete node;
				return;
			}
			else
			{
				auto del = min(node->right);
				node->key = std::move(del->key);
				erase(del);
				return;
			}
		}
		else
		{
			if (node->left && node->right)
			{
				auto del = min(node->right);
				node->key = std::move(del->key);
				erase(del);
				return;
			}
			else if (node->left || node->right)
			{
				auto del = node->left ? node->left : node->right;
				node->left ? node->left = nullptr : node->right = nullptr;
				node->key = std::move(del->key);
				delete del;
				return;
			}
			else
			{
				auto par = node->getParent();
				if (!par)
				{
					delete _root;
					_root = nullptr;
					return;
				}

				bool isLeft = par->left == node ? true : false;
				isLeft ? par->left = nullptr : par->right = nullptr;
				delete node;

				while (true)
				{
					auto bro = isLeft ? par->right : par->left;
					if (bro->getColor() == RED)
					{
						isLeft ? leftRotate(par) : rightRotate(par);
						par->setColor(RED);
						bro->setColor(BLACK);
						if (!bro->getParent()) _root = bro;
						isLeft ? bro = par->right : bro = par->left;
					}
					
					if (bro->getColor() == BLACK)
					{
						if ((isLeft ? bro->left : bro->right) && (isLeft ? bro->left : bro->right)->getColor() == RED)
						{
							auto temp = isLeft ? bro->left : bro->right;
							isLeft ? rightRotate(bro) : leftRotate(bro);
							isLeft ? leftRotate(par)  : rightRotate(par);
							temp->setColor(par->getColor());
							par->setColor(BLACK);
							return;
						}
						else if ((isLeft ? bro->right : bro->left) && (isLeft ? bro->right : bro->left)->getColor() == RED)
						{
							auto temp = isLeft ? bro->right : bro->left;
							isLeft ? leftRotate(par) : rightRotate(par);
							bro->setColor(par->getColor());
							par->setColor(BLACK);
							temp->setColor(BLACK);
							return;
						}
						else if (par->getColor() == RED)
						{
							par->setColor(BLACK);
							bro->setColor(RED);
							return;
						}
						else
						{
							bro->setColor(RED);
							if (par->getParent()) isLeft = par->getParent()->left == par ? true : false;
							else return;
							par = par->getParent();
							continue;
						}
					}
				}
			}
		}
	}

public:
	class const_iterator
	{
	public:
		const_iterator() = default;

		const T& operator*()const
		{
			return current->key;
		}

		const_iterator& operator++()
		{
			return getNext();
		}

		const_iterator operator++(int)
		{
			auto old = *this;
			++(*this);
			return old;
		}

		bool operator==(const const_iterator& iter)const
		{
			return current == iter.current;
		}

		bool operator!=(const const_iterator& iter)const
		{
			return !(*this == iter);
		}


	protected:
		const RBNode* current = nullptr;

		explicit const_iterator(const RBNode* node) :current(node) {}

		const_iterator& getNext()
		{
			const RBNode* next = current->right;
			if (next)
			{
				while (next->left) next = next->left;
			}

			if (next) current = next;
			else
			{
				auto par = current->getParent();
				while (par && par->key < current->key)
				{
					par = par->getParent();
				}
				current = par;
			}
			return *this;
		}

		friend class RedBlackTree;
	};

	class iterator : public const_iterator 
	{
	public:
		iterator() = default;

	protected:
		explicit iterator(const RBNode* node) : const_iterator(node) {}

		friend class RedBlackTree;
	};


public:
	RedBlackTree() = default;

	~RedBlackTree()
	{
		makeEmpty();
	}

	RedBlackTree(const RedBlackTree& tree):_root(nullptr)
	{
		_root = clone(tree._root);
	}

	RedBlackTree(RedBlackTree&& tree)noexcept : _root(tree._root), _size(tree._size)
	{
		tree._root = nullptr;
		tree._size = 0;
	}

	RedBlackTree& operator=(const RedBlackTree& tree)
	{
		if (this != &tree)
		{
			RBNode* temp = clone(tree._root);
			makeEmpty(_root);
			_root = temp;
		}

		return *this;
	}

	RedBlackTree& operator=(RedBlackTree&& tree)noexcept
	{
		if (this != &tree)
		{
			_root = tree._root;
			_size = tree._size;
			tree._root = nullptr;
			tree._size = 0;
		}

		return *this;
	}

	iterator begin()
	{
		return iterator(min(_root));
	}

	iterator end()
	{
		return iterator();
	}

	const_iterator begin()const
	{
		return const_iterator(min(_root));
	}

	const_iterator end()const
	{
		return const_iterator();
	}

	void print()const
	{
		if (empty()) cout << "Empty tree!" << endl;
		else inOrder();
	}

	void preOrder()const
	{
		preOrder(_root, [this](const RBNode* node) {printColorKey(node); });
	}

	void inOrder()const
	{
		inOrder(_root, [this](const RBNode* node) {printColorKey(node); });
	}

	void postOrder()const
	{
		postOrder(_root, [this](const RBNode* node) {printColorKey(node); });
	}

	void levelOrder()const
	{
		levelOrder(_root, [this](const RBNode* node) {printColorKey(node); });
	}

	void makeEmpty()
	{
		makeEmpty(_root);
	}

	bool contains(const T& key)
	{
		return search(_root, key) != nullptr;
	}

	bool empty()const noexcept
	{
		return _root == nullptr;
	}

	size_t size()const noexcept
	{
		return _size;
	}

	const T& min()const
	{
		if (empty()) throw std::exception("Empty RedBlackTree!");

		return min(_root)->key;
	}

	const T& max()const
	{
		if (empty()) throw std::exception("Empty RedBlackTree!");

		return max(_root)->key;
	}

	void insert(const T& key)
	{
		insert(key, false);
	}

	void insert(T&& key)
	{
		insert(key, true);
	}

	void erase(const T& key)
	{
		if (RBNode* node = search(_root, key))
		{
			erase(node);
			--_size;
		}
	}

	void erase(const_iterator iter)
	{
		if (iter != end())
		{
			erase(const_cast<RBNode*>(iter.current));
			--_size;
		}
	}


	/*************测试方法*************/
	// 测试其是否是二叉搜索树
	bool isRBBST()const
	{
		return isRBBST(_root);
	}

	int height()const
	{
		return height(_root);
	}

private:
	// 测试其是否是二叉搜索树
	bool isRBBST(const RBNode* node)const
	{
		// 检查根节点是否是黑色
		if (_root && _root->getColor() != BLACK)
		{
			cout << "Root Error : Root not's BLACK!" << endl;
			return false;
		}

		// 非递归中序遍历判断是否是二叉搜索树
		{
			stack<T> nums;
			stack<RBNode*> sta;
			auto node = _root;
			while (node || !sta.empty())
			{
				while (node)
				{
					sta.push(node);
					node = node->left;
				}

				node = sta.top();
				sta.pop();
				if (!nums.empty() && node->key <= nums.top())
				{
					cout << "BST Error : prev(" << nums.top()
						<< ") node(" << node->key << ")" << endl;
					return false;
				}

				nums.push(node->key);

				node = node->right;
			}
		}

		cout << "BST性质检查完毕" << endl;


		// 前序遍历检查父节点指针
		{
			preOrder(_root, [=](const RBNode* node)
				{
					if (!node) return;

					if (node->left)
					{
						if (node->left->getParent() != node)
						{
							cout << "\033[031mError Par(" << node->key << ") : " << node
								<< " left(" << node->left->key << ") : " << node->left
								<< " left's par(" << (node->getParent() ? node->getParent()->key : -1)
								<< ") : " << node->left->getParent()
								<< "\033[0m" << endl;
							levelOrder();
						}
					}

					if (node->right)
					{
						if (node->right->getParent() != node)
						{
							cout << "\033[031mError Par(" << node->key << ") : " << node
								<< " left(" << node->right->key << ") : " << node->right
								<< " left's par(" << (node->getParent() ? node->getParent()->key : -1)
								<< ") : " << node->right->getParent()
								<< "\033[0m" << endl;
							levelOrder();
						}
					}
				});
		}

		cout << "父指针检查完毕" << endl;

		// 检查性质，红色节点只有0或2个黑色子节点
		{
			preOrder(_root, [](const RBNode* node)
				{
					if (!node) return;

					if (node->getColor() == RED)
					{
						// 仅有左子节点
						if (node->left && !node->right)
						{
							cout << "\033[31mError Color : node(RED) "
								<< " node->left(" << (node->left->getColor() == BLACK ? "BLACK" : "RED")
								<< ")\033[0m" << endl;
						}

						// 仅有有子节点
						if (!node->left && node->right)
						{
							cout << "\033[31mError Color : node(RED) "
								<< " node->right(" << (node->right->getColor() == BLACK ? "BLACK" : "RED")
								<< ")\033[0m" << endl;
						}
					}
				});
		}

		cout << "红色节点仅有0或2个黑色节点性质检查完毕" << endl;
		cout << "size : " << size() << endl;

		return true;
	}

	int height(const RBNode* node)const
	{
		if (!node) return -1;

		return std::max(height(node->left), height(node->right)) + 1;
	}

};

#endif // end _REDBLACKTREE_H_