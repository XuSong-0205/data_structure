#ifndef _REDBLACKTREE_H_
#define _REDBLACKTREE_H_

#include <iomanip>
#include <iostream>
#include <exception>
#include <stack>
#include <queue>
using std::cout;
using std::endl;
using std::setw;
using std::stack;
using std::queue;


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

		RBNode(const T& k, RBNode* l, RBNode* r, RBNode* p, RBColor c)
			:key(k), left(l), right(r), parent(p), color(c) {}

		RBNode(T&& k, RBNode* l, RBNode* r, RBNode* p, RBColor c)
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

	RBNode* _root;

private:
	void print(RBNode* node, const T& value, int direction)const
	{
		if (node)
		{
			if (direction == 0) 
			{
				cout << setw(2) << node->key << " (B) is root " << endl;
			}
			else 
			{
				cout << setw(2) << node->key << (node->getColor() == RED ? "(R)" : "(B)") << " is "
					<< setw(2) << value << " 's " << setw(12)
					<< (direction == 1 ? " right child " : " left child ") << endl;
			}
			print(node->left, node->key, -1);
			print(node->right, node->key, 1);
		}
	}

	// 非递归前序遍历
	void preOrder(RBNode* node)const
	{
		stack<RBNode*> sta;
		while (node || !sta.empty())
		{
			while (node)
			{
				cout << node->key << " ";

				sta.push(node);
				node = node->left;
			}

			node = sta.top();
			sta.pop();
			node = node->right;
		}
	}

	// 非递归中序遍历
	void inOrder(RBNode* node)const
	{
		stack<RBNode*> sta;
		while (node || !sta.empty())
		{
			while (node)
			{
				sta.push(node);
				node = node->left;
			}
			node = sta.top();
			sta.pop();

			cout << node->key << " ";

			node = node->right;
		}
	}

	// 非递归后序遍历
	void postOrder(RBNode* node)const
	{
		RBNode* prev = nullptr;
		stack<RBNode*> sta;
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

				cout << node->key << " ";

				prev = node;
				node = nullptr;
			}
			else
			{
				node = node->right;
			}
		}
	}

	// 层序遍历
	void levelOrder(RBNode* node)const
	{
		if (!node) return;

		queue<RBNode*> que;
		que.push(node);
		while (!que.empty())
		{
			const int size = que.size();
			for (int i = 0; i < size; ++i)
			{
				node = que.front();
				que.pop();

				cout << node->key << " ";

				if (node->left) que.push(node->left);
				if (node->right) que.push(node->right);
			}
			cout << "\n";
		}
	}

	RBNode* clone(RBNode* node)
	{
		if (node)
		{
			RBNode* curr = new RBNode(node->key, clone(node->left), clone(node->right), nullptr, node->color);
			if (curr->left)  curr->left->setParent(curr);
			if (curr->right) curr->right->setParent(curr);
			return curr;

		}
		else
		{
			return nullptr;
		}

		/*if (node) return new RBNode(node->key, clone(node->left), clone(right), nullptr, color);
		else return nullptr;*/
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

	void leftRotate(RBNode*& tree, RBNode* x)
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

	void rightRotate(RBNode*& tree, RBNode* y)
	{
		RBNode* x = y->left;
		y->left = x->right;

		if (x->right != nullptr) 
		{
			x->right->setParent(x);
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

	void insert(RBNode*& tree, RBNode* node)
	{
		RBNode* temp1 = nullptr;
		RBNode* temp2 = tree;

		while (temp2 != nullptr) 
		{
			temp1 = temp2;
			if (node->key < temp2->key) 
			{
				temp2 = temp2->left;
			}
			else 
			{
				temp2 = temp2->right;
			}
		}

		node->setParent(temp1);

		if (temp1 != nullptr) 
		{
			if (node->key < temp1->key) 
			{
				temp1->left = node;
			}
			else 
			{
				temp1->right = node;
			}
		}
		else 
		{
			_root = node;
		}

		node->setColor(RED);

		insertFixUp(tree, node);
	}

	void insertFixUp(RBNode*& tree, RBNode* node)
	{
		RBNode* p = nullptr;
		RBNode* g = nullptr;
		while ((p = node->getParent()) && (p->getColor() == RED)) 
		{
			g = p->getParent();
			if (p == g->left) {
				//case 1 : uncle is RED
				{
					RBNode* uncle = g->right;
					if ((uncle != nullptr) && (uncle->getColor() == RED)) 
					{
						g->setColor(RED);
						p->setColor(BLACK);
						uncle->setColor(BLACK);

						node = g;
						continue;
					}
				}

				//case 2 : uncle is right child(BLACK)
				if (p->right == node) 
				{
					RBNode* temp = nullptr;
					leftRotate(tree, p);

					temp = p;
					p = node;
					node = temp;
				}

				//case 3 : uncle is left child(BLACK)
				g->setColor(RED);
				p->setColor(BLACK);
				rightRotate(tree, g);

			}
			else 
			{
				//case 1 : uncle is RED
				{
					RBNode* uncle = g->left;
					if (uncle && (uncle->getColor() == RED)) 
					{
						g->setColor(RED);
						p->setColor(BLACK);
						uncle->setColor(BLACK);

						node = g;
						continue;
					}
				}
				//case 2 : uncle is left child(BLACK)
				if (p->left == node) {
					RBNode* temp = nullptr;
					rightRotate(tree, p);

					temp = p;
					p = node;
					node = temp;
				}

				//case 3 : uncle is right child(BLACK)
				g->setColor(RED);
				p->setColor(BLACK);
				leftRotate(tree, g);
			}
		}

		//set root as black color
		_root->setColor(BLACK);
	}

	void erase(RBNode*& tree, RBNode* node)
	{
		RBNode* chd = nullptr;
		RBNode* pat = nullptr;
		RBColor clr = RED;

		//case 1 : the node has left and right child
		if ((node->left != nullptr) && (node->right != nullptr)) 
		{
			//use successor to "replace" the node
			RBNode* rep = node;
			rep = rep->right;
			while (rep->left != nullptr) 
			{
				rep = rep->left;
			}

			if (node->getParent() != nullptr)
			{
				RBNode* temp = node->getParent();
				if (node == temp->left) 
				{
					temp->left = rep;
				}
				else 
				{
					temp->right = rep;
				}
			}
			else 
			{
				_root = node;
			}

			chd = rep->right;
			pat = rep->getParent();
			clr = rep->getColor();

			if (pat == node) 
			{
				pat = rep;
			}
			else 
			{
				if (chd != nullptr) 
				{
					chd->setParent(pat);
				}

				rep->right = node->right;
				node->right->setParent(rep);
			}

			rep->setParent(node->getParent());
			rep->setColor(node->getColor());
			rep->left = node->left;
			node->left->setParent(rep);

			if (clr == BLACK) 
			{
				eraseFixUp(tree, chd, pat);
			}

			delete node;
			return;
		}

		//case 2 : node has only one child
		if (node->left != nullptr) 
		{
			chd = node->left;
		}
		else 
		{
			chd = node->right;
		}

		pat = node->getParent();
		clr = node->getColor();

		if (chd != nullptr) 
		{
			chd->setParent(pat);
		}

		if (pat != nullptr) 
		{
			if (node == pat->left) 
			{
				pat->left = chd;
			}
			else 
			{
				pat->right = chd;
			}
		}
		else 
		{
			_root = chd;
		}
		if (clr == BLACK) 
		{
			eraseFixUp(tree, chd, pat);
		}

		//case 3 : nod is leaf node
		delete node;
	}

	void eraseFixUp(RBNode*& tree, RBNode* node, RBNode* p)
	{
		RBNode* temp = nullptr;
		while (((node == nullptr || (node->getColor() == BLACK))) && (node != tree))
		{
			if (p->left == node) 
			{
				temp = p->right;

				//case 1 : brother node is RED
				if (temp->getColor() == RED) 
				{
					p->setColor(RED);
					temp->setColor(BLACK);

					leftRotate(tree, p);
					temp = p->right;
				}

				//case 2 : brother node is BLACK
				//case 2.1 both two children are BLACK
				if (((temp->left == nullptr)  || (temp->left->getColor() == BLACK)) &&
					((temp->right == nullptr) || (temp->right->getColor() == BLACK)))
				{
					temp->setColor(RED);
					node = p;
					p = node->getParent();
				}
				else 
				{
					//case 2.2 left child is RED, right child is BLACK
					if ((temp->right == nullptr) || (temp->right->getColor() == BLACK))
					{
						temp->left->setColor(BLACK);
						temp->setColor(RED);

						rightRotate(tree, temp);
						temp = p->right;
					}

					//case 2.3 right child is RED
					temp->setColor(p->getColor());
					p->setColor(BLACK);
					temp->right->setColor(BLACK);

					leftRotate(tree, p);
					node = tree;
					break;
				}
			}
			else 
			{
				temp = p->left;

				//case 1 : brother node is RED
				if (temp->getColor() == RED) 
				{
					p->setColor(RED);
					temp->setColor(BLACK);
					
					rightRotate(tree, p);
					temp = p->left;
				}

				//case 2 : brother node is BLACK
				//case 2.1 both two children are BLACK
				if (((temp->left  == nullptr) || (temp->left->getColor() == BLACK)) &&
					((temp->right == nullptr) || (temp->right->getColor() == BLACK)))
				{
					temp->setColor(RED);
					node = p;
					p = node->getParent();
				}
				else 
				{
					//case 2.2 left child is RED, right child is BLACK
					if ((temp->left == nullptr) || (temp->left->getColor() == BLACK))
					{
						temp->right->setColor(BLACK);
						temp->setColor(RED);

						leftRotate(tree, temp);
						temp = p->left;
					}

					//case 2.3 right child is RED
					temp->setColor(p->getColor());
					p->setColor(BLACK);
					temp->left->setColor(BLACK);
					
					rightRotate(tree, p);
					node = tree;
					break;
				}
			}
		}

		if (node != nullptr) 
		{
			node->setColor(BLACK);
		}
	}

public:
	RedBlackTree() :_root(nullptr) {}

	~RedBlackTree()
	{
		makeEmpty();
	}

	RedBlackTree(const RedBlackTree& tree):_root(nullptr)
	{
		_root = clone(tree._root);
	}

	RedBlackTree(RedBlackTree&& tree) = default;

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

	RedBlackTree& operator=(RedBlackTree&& tree) = default;

	void print()const
	{
		if (empty()) cout << "Empty tree!" << endl;
		else print(_root, _root->key, 0);
	}

	void preOrder()const
	{
		preOrder(_root);
	}

	void inOrder()const
	{
		inOrder(_root);
	}

	void postOrder()const
	{
		postOrder(_root);
	}

	void levelOrder()const
	{
		levelOrder(_root);
	}

	void makeEmpty()
	{
		makeEmpty(_root);
	}

	bool contains(const T& key)
	{
		return search(_root, key) != nullptr;
	}

	bool empty()const
	{
		return _root == nullptr;
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
		if (contains(key)) return;

		insert(_root, new RBNode(key, nullptr, nullptr, nullptr, RED));

		++_size;
	}

	void insert(T&& key)
	{
		if (contains(key)) return;

		insert(_root, new RBNode(std::move(key), nullptr, nullptr, nullptr, RED));
		++_size;
	}

	void erase(const T& key)
	{
		if (RBNode* node = search(_root, key))
		{
			erase(_root, node);
			--_size;
		}
	}


	/*************测试方法*************/
	// 测试其是否是二叉搜索树
	bool isBST()const
	{
		T  key = -0x0AAAAAAA;
		return isBST(_root, key);
	}

	size_t size()const
	{
		return _size;
	}

	int height()const
	{
		return height(_root);
	}

private:
	bool isBST(RBNode* node, T& key)const
	{
		if (node)
		{
			isBST(node->left, key);

			if (key != -0x0AAAAAAA && key > node->key) return false;
			key = node->key;

			isBST(node->right, key);
		}

		return true;
	}

	int height(RBNode* node)const
	{
		if (!node) return -1;

		return std::max(height(node->left), height(node->right)) + 1;
	}

	size_t _size = 0;

};

#endif // end _REDBLACKTREE_H_