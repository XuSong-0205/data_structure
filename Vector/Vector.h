#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;


template<typename Object>
class Vector
{
private:
	int theSize = 0;
	int theCapacity = 0;
	Object* objects;

public:
	explicit Vector(int Size = 0)
		:theSize{ Size }, theCapacity{ Size + SPARE_CAPACITY }							// 默认构造函数
	{
		objects = new Object[theCapacity];
	}

	Vector(const Vector& v0) 
		:theSize{ v0.theSize }, theCapacity{ v0.theCapacity }, objects{ nullptr }		// 拷贝构造函数
	{
		objects = new Object[theCapacity];
	}

	~Vector()																					// 析构函数
	{
		delete[] objects;
	}

	Vector& operator=(const Vector& v0)															// 拷贝赋值
	{
		if (v0 == (*this))
			return *this;

		Vector copy = v0;
		std::swap(*this, copy);
		return *this;
	}

	Vector(Vector&& v0) 
		:theSize{ v0.theSize }, theCapacity{ v0.theCapacity },							// 移动构造函数
		objects{ v0.objects }
	{
		v0.theSize = 0;
		v0.theCapacity = 0;
		v0.objects = nullptr;
	}

	Vector& operator=(Vector&& v0)																// 移动赋值
	{
		std::swap(theSize, v0.theSize);
		std::swap(theCapacity, v0.theCapacity);
		std::swap(objects, v0.objects);

		return *this;
	}

	void resize(int newSize)
	{
		if (newSize > theCapacity)
			reserve(newSize * 2);

		theSize = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
			return;

		Object* newArray = new Object[newCapacity];
		for (int i = 0; i < theSize; ++i)
			newArray[i] = std::move(objects[i]);

		theCapacity = newCapacity;
		std::swap(objects, newArray);
		delete[] newArray;
	}

	Object& operator[](int index)
	{
		return objects[index];
	}

	const Object& operator[](int index)const
	{
		return objects[index];
	}

	Object& at(int index)
	{
		if (index < 0 || index >= theSize)
			throw std::exception("out_of_range");

		return objects[index];
	}

	const Object& at(int index)const
	{
		if (index < 0 || index >= theSize)
			throw std::exception("out_of_range");

		return objects[index];
	}

	bool empty()const noexcept
	{
		return theSize == 0;
	}

	int size()const noexcept
	{
		return theSize;
	}

	int capacity()const noexcept
	{
		return theCapacity;
	}

	void push_back(const Object& v0)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);

		objects[theSize++] = v0;
	}

	void push_back(Object&& v0)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);

		objects[theSize++] = std::move(v0);
	}

	void pop_back()noexcept
	{
		--theSize;
	}

	const Object& back()const
	{
		return objects[theSize - 1];
	}

	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator begin()
	{
		return &objects[0];
	}

	const_iterator begin()const
	{
		return &objects[0];
	}

	iterator end()
	{
		return &objects[theSize];
	}

	const_iterator end()const
	{
		return &objects[theSize];
	}

	static const int SPARE_CAPACITY = 16;
};