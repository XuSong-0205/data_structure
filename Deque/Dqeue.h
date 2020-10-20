#ifndef _DEQUE_H_
#define _DEQUE_H_
#include <iostream>
#include <stdexcept>

template<typename T>
class Deque
{
private:
	T* _date;
	int _capacity;
	int _front;
	int _rear;

	T* clone(const Deque& deq)
	{
		T* temp = new T[deq._capacity];
		for (int i = 0; i < deq._capacity; ++i) temp[i] = deq._date[i];

		return temp;
	}

	void makeEmpty()
	{
		delete[] _date;
		_date = nullptr;
	}

	void resize()
	{
		int newSize = _capacity << 1;
		T* temp = new T[newSize];

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

		_front = 0;
		_rear = _capacity - 1;
		_date = temp;
		_capacity = newSize;
	}

public:
	explicit Deque(int size = 16)
		:_date(nullptr), _capacity(size), _front(0), _rear(0)
	{
		if (_capacity < 16) _capacity = 16;

		_date = new T[_capacity];
	}

	Deque(const Deque& deq)
	{
		_date = clone(deq);
		_capacity = deq._capacity;
		_front = deq._front;
		_rear = deq._rear;
	}

	Deque(Deque&& deq)
	{
		_date = deq._date;
		_capacity = deq._capacity;
		_front = deq._front;
		_rear = deq._rear;

		deq._date = nullptr;
		deq._front = 0;
		deq._rear = 0;
	}

	Deque& operator=(const Deque& deq)
	{
		if (this != &deq)
		{
			_date = clone(deq);
			_capacity = deq._capacity;
			_front = deq._front;
			_rear = deq._rear;
		}

		return *this;
	}

	Deque& operator=(Deque&& deq)
	{
		if (this != &deq)
		{
			_date = deq._date;
			_capacity = deq._capacity;
			_front = deq._front;
			_rear = deq._rear;

			deq._date = nullptr;
			deq._front = 0;
			deq._rear = 0;
		}

		return *this;
	}

	~Deque()
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
		if (empty()) throw std::exception("Deque is empty");

		return _date[_front];
	}

	const T& back()const
	{
		if (empty()) throw std::exception("Deque is empty");

		return _date[(_rear - 1 + _capacity) % _capacity];
	}

	void push_front(const T& val)
	{
		if (full()) resize();

		_front = (_front - 1 + _capacity) % _capacity;
		_date[_front] = val;
 	}

	void push_back(const T& val)
	{
		if (full()) resize();

		_date[_rear] = val;
		_rear = (_rear + 1) % _capacity;
	}

	void pop_front()
	{
		if (empty()) throw std::exception("Deque is empty");

		_front = (_front + 1) % _capacity;
	}

	void pop_back()
	{
		if (empty()) throw std::exception("Deque is empty");

		_rear = (_rear - 1 + _capacity) % _capacity;
	}

	void print()const
	{
		if (_front < _rear)
		{
			for (int i = _front; i < _rear; ++i) std::cout << _date[i] << " ";
		}
		else
		{
			for(int i = _front; i < _capacity; ++i) std::cout << _date[i] << " ";
			for (int i = 0; i < _rear; ++i) std::cout << _date[i] << " ";
		}
		std::cout << std::endl;
	}
};


#endif // _DEQUE_H_