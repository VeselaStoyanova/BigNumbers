#pragma once
#include <iostream>
using namespace std;

template<class T>
class Vector
{
public:
	class Iterator
	{
	private:
		Vector<T> vec;
		size_t position;

	public:
		Iterator(Vector<T>& vec, size_t position)
		{
			this->vec = vec;
			this->position = position;
		}

		Iterator(const Iterator& other) = default;
		Iterator& operator=(const Iterator& other) = default;

		bool operator!=(const Iterator& other)
		{
			return this->position != other.position;
		}

		Iterator& operator++()
		{
			this->position++;
			return *this;
		}

		T operator*()
		{
			return vec[position];
		}
	};

private:
	T* data;
	size_t size;
	size_t capacity;

	void copy(const Vector<T>& other)
	{
		this->data = new T[other.capacity];

		for (size_t i = 0; i < other.size; i++)
		{
			this->data[i] = other.data[i];
		}

		this->size = other.size;
		this->capacity = other.capacity;
	}

	void resize()
	{
		this->capacity = this->capacity * 2;
		T* bigger_buffer = new T[this->capacity];

		for (size_t i = 0; i < this->size; i++)
		{
			bigger_buffer[i] = this->data[i];
		}

		this->destroy();
		this->data = bigger_buffer;
	}

	void move(Vector<T>& other)
	{
		this->data = other.data;
		this->size = other.size;
		this->capacity = other.capacity;
		other.data = nullptr;
	}

	void destroy()
	{
		delete[] this->data;
	}

public:
	Vector()
	{
		this->size = 0;
		this->capacity = 8;
		this->data = new T[this->capacity];
	}

	Vector(const Vector<T>& other)
	{
		this->copy(other);
	}

	Vector& operator=(const Vector<T>& other)
	{
		if (this != &other)
		{
			this->destroy();
			this->copy(other);
		}

		return *this;
	}

	bool operator==(const Vector<T>& other)
	{
		if (this->size != other.size && this->capacity != other.capacity)
		{
			return false;
		}

		for (int i = 0; i < this->size; i++)
		{
			if (this->data[i] != other.data[i])
			{
				return false;
			}
		}

		return true;
	}

	T operator[](size_t idx)
	{
		return this->data[idx];
	}

	~Vector()
	{
		this->destroy();
	}

	Vector& push_back(const T& newObject)
	{
		if (size == capacity)
		{
			resize();
		}

		this->data[size] = newObject;
		this->size++;

		return *this;
	}

	void pop_back()
	{
		if (this->size <= 0)
		{
			return;
		}
		this->size--;
	}

	void pop_front()
	{
		if (this->size <= 0)
		{
			return;
		}

		for (int i = 0; i < this->size - 1; i++)
		{
			this->data[i] = this->data[i + 1];
		}
		this->size--;
	}

	size_t length()
	{
		return this->size;
	}

	void print()
	{
		for (int i = 0; i < this->length(); i++)
		{
			cout << this->data[i] << " ";
		}
		cout << endl;
	}

	void swapValues(int i, int j)
	{
		T temp = this->data[i];
		this->data[i] = this->data[j];
		this->data[j] = temp;
	}

	Iterator begin()
	{
		return Iterator(*this, 0);
	}

	Iterator end()
	{
		return Iterator(*this, this->size);
	}

	T last()
	{
		return this->data[size - 1];
	}

	T first()
	{
		return this->data[0];
	}
};