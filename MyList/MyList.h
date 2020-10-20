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

	// ��¡���������� _tail ����Ϊ��ȷ��ָ��
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
		_tail = prev;										// ����βָ��ָ��

		return newHead;
	}

	// �ͷŵ�����
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

	// ���ص� n ���ڵ��ָ��
	// ͷ�ڵ��ǵ� 0 ���ڵ�
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

	// ����ֵ val ��һ�γ����������е�λ��
	// δ���ַ��� -1
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

	// ��ͷ������
	void insertHead(Node* node)
	{
		node->next = _head;
		_head = node;
		
		if (_tail == nullptr) _tail = node;					// βָ��Ҳָ��ǰ�ڵ�
	}

	// ��β������
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

	// �� node ����Ϊ�� n ��Ԫ��
	void insertIndex(Node* node, int n)
	{
		if (node == nullptr) return;
		if (n < 1 || n > static_cast<int>(_size)) return;

		Node* prev = search(_head, n - 1);
		node->next = prev->next;
		prev->next = node;

	}

	// ɾ�� node �ڵ����һ���ڵ�
	void eraseNext(Node* node)
	{
		if (node == nullptr) return;

		Node* temp = node->next;							// ָ����һ����Ҫɾ���Ľڵ�
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

	// ɾ��ͷ�ڵ�
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
		// _tail �� clone() �б���ȷ����ָ��
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

	// ͷ��
	void insertHead(const T& val)
	{
		insertHead(new Node(val));
		++_size;
	}

	// β��
	void insertTail(const T& val)
	{
		insertTail(new Node(val));
		++_size;
	}

	// �ڵ� n ��λ�ò���Ԫ�� val
	void insertIndex(const T& val, int n)
	{
		if (n < 0 || n > static_cast<int>(_size)) return;

		Node* node = new Node(val);
		if (n == 0) insertHead(node);							// ͷ��
		else insertIndex(node, n);								// �� node ����Ϊ�� n ��Ԫ��

		++_size;
	}

	// ɾ����һ�� val
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

	// ɾ���� n ��Ԫ��
	void eraseN(int n)
	{
		if (n >= 0 && n <= static_cast<int>(_size))
		{
			if (n == 0) eraseHead(_head);
			else eraseNext(search(n - 1));

			--_size;
		}
	}

	// -1 ����δ�ҵ�
	int find(const T& val)
	{
		return search(val);
	}

	// ����� n ��Ԫ��
	// �� n С�� 0 ����� _size ���׳��쳣
	const T& printN(int n)
	{
		if (n < 0 || n > static_cast<int>(_size)) throw std::exception("out of range");

		return search(_head, n)->value;
	}

	// ���������
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