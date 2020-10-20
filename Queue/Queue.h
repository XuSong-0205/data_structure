#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <iostream>
#include <stdexcept>


template<typename T>
class Queue
{
private:
	T* _date;
	int _capacity;
	int _front;
	int _rear;

	T* clone(const Queue& que)
	{
		T* temp = new T[que._capacity];
		for (int i = 0; i < que._capacity; ++i) temp[i] = que._date[i];

		return temp;
	}

	void makeEmpty()
	{
		delete[] _date;
		_date = nullptr;
		_front = 0;
		_rear = 0;
	}

	void resize()
	{
		int size = _capacity << 1;
		T* temp = new T[size];

		if (_front < _rear)
		{
			for (int i = 0; i < _capacity; ++i) temp[i] = std::move(_date[i]);
		}
		else
		{
			int index = 0;
			for (int i = _front; i < _capacity; ++i) temp[index++] = std::move(_date[i]);
			for (int i = 0; i < _rear; ++i) temp[index++] = std::move(_date[i]);
		}

		delete[] _date;

		_front = 0;
		_rear = _capacity - 1;
		_date = temp;
		_capacity = size;
	}

public:
	explicit Queue(int size = 16) :
		_date(nullptr), _capacity(size), _front(0), _rear(0)
	{
		if (_capacity < 16) _capacity = 16;

		_date = new T[_capacity];
	}

	Queue(const Queue& que) 
	{
		_date = clone(que);
		_capacity = que._capacity;
		_front = que._front;
		_rear = que._rear;
	}

	Queue(Queue&& que)
	{
		_date = que._date;
		_capacity = que._capacity;
		_front = que._front;
		_rear = que._rear;

		que._date = nullptr;
		que._front = 0;
		que._rear = 0;
	}

	Queue& operator=(const Queue& que)
	{
		if (this != &que)
		{
			T* temp = clone(que);
			makeEmpty();

			_date = temp;
			_capacity = que._capacity;
			_front = que._front;
			_rear = que._rear;
		}

		return *this;
	}

	Queue& operator=(Queue&& que)
	{
		if (this != &que)
		{
			_date = que._date;
			_capacity = que._capacity;
			_front = que._front;
			_rear = que._rear;

			que._date = nullptr;
			que._front = 0;
			que._rear = 0;
		}

		return *this;
	}

	~Queue()
	{
		makeEmpty();
	}

	bool empty()const noexcept
	{
		return _front == _rear;
	}

	bool full()const noexcept
	{
		return (_rear + 1) % _capacity == _front;
	}

	int size()const noexcept
	{
		return (_rear - _front + _capacity) % _capacity;
	}

	const T& front()const
	{
		if (empty()) throw std::exception("Queue is empty");

		return _date[_front];
	}

	void push(const T& val)
	{
		if (full()) resize();

		_date[_rear] = val;
		_rear = (_rear + 1) % _capacity;
	}

	void pop()
	{
		if (empty()) throw std::exception("Queue is empty");

		_front = (_front + 1) % _capacity;
	}

	void print()const
	{
		if (_front < _rear)
		{
			for (int i = _front; i < _rear; ++i) std::cout << _date[i] << " ";
		}
		else
		{
			for (int i = _front; i < _capacity; ++i) std::cout << _date[i] << " ";
			for (int i = 0; i < _rear; ++i) std::cout << _date[i] << " ";
		}
	}
};

#endif // _QUEUE_H_
