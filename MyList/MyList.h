#ifndef _MYLIST_H_
#define _MYLIST_H_
#include <iostream>
#include <stdexcept>
using std::cout;
using std::endl;



template<typename T>
class MyList
{
private:
	struct Node
	{
		T value;
		Node* next;

		Node(const T& val, Node* n = nullptr)
			:value(val), next(n) {}
	};

	Node* _head;
	Node* _tail;
	size_t _size;

	// 克隆单链表，并将 _tail 设置为正确的指向
	Node* clone(Node* node)
	{
		if (node == nullptr)
		{
			_tail = nullptr;
			return nullptr;
		}

		Node* prev = new Node(node->value);
		Node* newHead = prev;
		node = node->next;

		while (node)
		{
			prev->next = new Node(node->value);
			prev = prev->next;
			node = node->next;
		}
		_tail = prev;										// 设置尾指针指向

		return newHead;
	}

	// 释放单链表
	void makeEmpty(Node* node)
	{
		if (node == nullptr) return;

		Node* temp = node;
		while (node != nullptr)
		{
			temp = node->next;
			delete node;
			node = temp;
		}
	}

	// 返回第 n 个节点的指针
	// 头节点是第 0 个节点
	Node* search(Node* , int n)
	{
		if (n < 0 || n > static_cast<int>(_size)) return nullptr;

		Node* curr = _head;
		while (n-- > 0)
		{
			curr = curr->next;
		}
		return curr;
	}

	// 返回值 val 第一次出现在链表中的位置
	// 未出现返回 -1
	int search(const T& val)const
	{
		Node* curr = _head;
		int index = 0;
		while (curr != nullptr)
		{
			if (curr->value == val) return index;

			curr = curr->next;
			++index;
		}

		return -1;
	}

	// 在头部插入
	void insertHead(Node* node)
	{
		node->next = _head;
		_head = node;
		
		if (_tail == nullptr) _tail = node;					// 尾指针也指向当前节点
	}

	// 在尾部插入
	void insertTail(Node* node)
	{
		if (_tail == nullptr)
		{
			_head = node;
			_tail = node;
		}
		else
		{
			_tail->next = node;
			_tail = _tail->next;
		}
	}

	// 将 node 插入为第 n 个元素
	void insertIndex(Node* node, int n)
	{
		if (node == nullptr) return;
		if (n < 1 || n > static_cast<int>(_size)) return;

		Node* prev = search(_head, n - 1);
		node->next = prev->next;
		prev->next = node;

	}

	// 删除 node 节点的下一个节点
	void eraseNext(Node* node)
	{
		if (node == nullptr) return;

		Node* temp = node->next;							// 指向下一个将要删除的节点
		if (temp->next != nullptr)
		{
			node->next = temp->next;
			delete temp;
			temp = nullptr;
		}
		else
		{
			node->next = nullptr;
			delete temp;
			temp = nullptr;

			_tail = node;
		}
	}

	// 删除头节点
	void eraseHead(Node* node)
	{
		if (node != nullptr) return;

		Node* temp = node->next;
		delete node;
		_head = temp;
		if (_head == nullptr) _tail = nullptr;
	}

public:
	MyList() :_head(nullptr), _tail(nullptr), _size(0) {}

	MyList(const MyList& list): _head(nullptr), _tail(nullptr), _size(0)
	{
		// _tail 在 clone() 中被正确设置指向
		_head = clone(list._head);
		_size = list._size;
	}

	MyList(MyList&& list)noexcept
	{
		_head = list._head;
		_tail = list._tail;
		_size = list._size;

		list._head = nullptr;
		list._tail = nullptr;
		list._size = 0;
	}

	MyList& operator=(const MyList& list)
	{
		if (this != &list)
		{
			Node* temp = clone(list._head);
			makeEmpty(_head);
			_head = temp;
			_size = list._size;
		}

		return *this;
	}

	MyList& operator=(MyList&& list)noexcept
	{
		if (this != &list)
		{
			_head = list._head;
			_tail = list._tail;
			_size = list._size;

			list._head = nullptr;
			list._tail = nullptr;
			list._size = 0;
		}

		return *this;
	}

	~MyList()
	{
		makeEmpty(_head);

		_head = nullptr;
		_tail = nullptr;
		_size = 0;
	}

	// 头插
	void insertHead(const T& val)
	{
		insertHead(new Node(val));
		++_size;
	}

	// 尾插
	void insertTail(const T& val)
	{
		insertTail(new Node(val));
		++_size;
	}

	// 在第 n 个位置插入元素 val
	void insertIndex(const T& val, int n)
	{
		if (n < 0 || n > static_cast<int>(_size)) return;

		Node* node = new Node(val);
		if (n == 0) insertHead(node);							// 头插
		else insertIndex(node, n);								// 将 node 插入为第 n 个元素

		++_size;
	}

	// 删除第一个 val
	void erase(const T& val)
	{
		if (!empty())
		{
			int index = find(val);
			if (index != -1)
			{
				if (index == 0) eraseHead(_head);
				else eraseNext(search(index - 1));

				--_size;
			}
		}
	}

	// 删除第 n 个元素
	void eraseN(int n)
	{
		if (n >= 0 && n <= static_cast<int>(_size))
		{
			if (n == 0) eraseHead(_head);
			else eraseNext(search(n - 1));

			--_size;
		}
	}

	// -1 代表未找到
	int find(const T& val)
	{
		return search(val);
	}

	// 输出第 n 各元素
	// 若 n 小于 0 或大于 _size 将抛出异常
	const T& printN(int n)
	{
		if (n < 0 || n > static_cast<int>(_size)) throw std::exception("out of range");

		return search(_head, n)->value;
	}

	// 输出单链表
	void print()const
	{
		Node* curr = _head;
		while (curr != nullptr)
		{
			cout << curr->value << " ";
			curr = curr->next;
		}
	}

	size_t size()const noexcept
	{
		return _size;
	}

	bool empty()const noexcept
	{
		return _head == nullptr;
	}
};


#endif	// _MYLIST_H_