#pragma once
#include <list>

template<typename Object>
class List
{
private:
	struct Node
	{
		Object data;
		Node* prev;
		Node* next;

		Node(const Object& obj = Object(), Node* p = nullptr, Node* n = nullptr)
			:data(obj), prev(p), next(n) {}
		Node(Object&& obj, Node* p = nullptr, Node* n = nullptr)
			:data(std::move(obj)), prev(p), next(n) {}
	};

	int theSize;
	Node* head;
	Node* tail;

public:
	class const_iterator
	{
	public:
		const_iterator() :current(nullptr) {}

		const Object& operator*()const
		{
			return retrieve();
		}

		const_iterator& operator++()
		{
			current = current->next;
			return *this;
		}

		const_iterator operator++(int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}

		bool operator==(const const_iterator& rhs)const
		{
			return current == rhs.current;
		}

		bool operator!=(const const_iterator& rhs)const
		{
			return !(*this == rhs);
		}

	protected:
		Node* current;

		Object& retrieve()const
		{
			return current->data;
		}

		const_iterator(Node* p) :current(p) {}

		friend class List;
	};

	class iterator : public const_iterator
	{
	public:
		iterator() {}

		Object& operator*()
		{
			return const_iterator::retrieve();
		}

		const Object& operator*()const
		{
			return const_iterator::operator*();
		}

		iterator operator++()
		{
			this->current = this->current->next;
			return *this;
		}

		iterator operator++(int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}

	protected:
		iterator(Node* p) :const_iterator(p) {}

		friend class List;
	};


public:
	using value_type = Object;


	List()
	{
		init();
	}

	List(const List& list)
	{
		init();
		for (auto& x : list)
			push_back(x);
	}

	List(List&& list)
		:theSize(list.theSize), head(list.head), tail(list.tail)
	{
		list.theSize = 0;
		list.head = nullptr;
		list.tail = nullptr;
	}

	List& operator=(const List& list)
	{
		List copy = list;
		std::swap(*this, copy);
		return *this;
	}

	List& operator=(List&& list)
	{
		std::swap(theSize, list.theSize);
		std::swap(head, list.head);
		std::swap(tail, list.tail);
	}

	~List()
	{
		clear();
	}

	iterator begin()
	{
		return { head->next };
	}

	iterator end()
	{
		return { tail };
	}

	const_iterator begin()const
	{
		return { head->next };
	}

	const_iterator end()const
	{
		return { tail };
	}

	constexpr int size()const noexcept
	{
		return theSize;
	}

	constexpr bool empty()const noexcept
	{
		return size() == 0;
	}

	void clear()
	{
		while (!empty())
			pop_front();
	}

	Object& front()
	{
		return *begin();
	}

	const Object& front()const
	{
		return *begin();
	}

	Object& back()
	{
		return *--end();
	}

	const Object& back()const
	{
		return *--end();
	}

	void push_front(const Object& obj)
	{
		insert(begin(), obj);
	}

	void push_front(Object&& obj)
	{
		insert(begin(), std::move(obj));
	}

	void push_back(const Object& obj)
	{
		insert(end(), obj);
	}

	void push_back(Object&& obj)
	{
		insert(end(), std::move(obj));
	}

	void pop_front()
	{
		erase(begin());
	}

	void pop_back()
	{
		erase(--end());
	}

	// ÔÚ itr Ç°²åÈë obj
	iterator insert(iterator itr, const Object& obj)
	{
		Node* p = itr.current;
		++theSize;
		return { p->prev = p->prev->next = new Node(obj, p->prev, p) };
	}

	iterator insert(iterator itr, Object&& obj)
	{
		Node* p = itr.current;
		++theSize;
		return { p->prev = p->prev->next = new Node(std::move(obj), p->prev, p) };
	}

	iterator erase(iterator itr)
	{
		Node* p = itr.current;
		iterator retVal(p->next);
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		--theSize;

		return retVal;
	}

	iterator erase(iterator from, iterator to)
	{
		for (iterator itr = from; itr != to;)
			itr = erase(itr);

		return to;
	}


private:
	void init()
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}
};

