#ifndef _MY_VECTOR_
#define _MY_VECTOR_

#include<iostream>
using std::endl;
using std::cout;
using std::cerr;

template<class T>
class MyVector
{
private:

	T* _arr;
	size_t _size;
	size_t _capacity;

	T* allocateArr(size_t initialCapacity);
	void freeMem();
	void resizeVector();

public:

	size_t getSize() const;

	MyVector(std::initializer_list<T> elements);

	//MyVector():MyVector(0){}

	explicit MyVector(int initialCapacity = 10);

	~MyVector();

	MyVector(const MyVector& obj);

	MyVector& operator=(const MyVector& obj);

	template <class Y>
	MyVector(const MyVector<Y>& obj);

	template <class Y>
	MyVector& operator=(const MyVector<Y>& obj);

	void push(const T& element);

	void remove();

	void removeAt(size_t pos);

	void removeSubarray(size_t from, size_t to);

	const T& operator[](size_t index)const;

	T& operator[](size_t index);

	T& at(size_t index);

	bool isTrueForAll(bool(*predicate)(const T&));

	MyVector operator+(const MyVector& obj);

	void map(T(*f)(const T&));

	friend std::ostream& operator<<(std::ostream& out, const MyVector& obj)
	{
		for (size_t i = 0; i < obj.getSize(); i++)
		{
			out << obj._arr[i] << ' ';
		}
		out << '\n';
		return out;
	}
};


template <class T>
T* MyVector<T>::allocateArr(size_t initialCapacity)
{
	T* toAllocate = nullptr;
	try
	{
		toAllocate = new T[initialCapacity];
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		delete[] toAllocate;
		toAllocate = nullptr;
	}
	return toAllocate;
}

template <class T>
void MyVector<T>::freeMem()
{
	delete[] _arr;
	_arr = nullptr;
}

template <class T>
void MyVector<T>::resizeVector()
{
	T* tmp = nullptr;
	_capacity = _capacity * 2 + 1;

	try
	{
		tmp = allocateArr(_capacity);
		for (size_t i = 0; i < _size; i++)
		{
			tmp[i] = _arr[i];
		}
		freeMem();
		_arr = tmp;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
		freeMem();
		delete[] tmp;
	}
}


template <class T>
size_t MyVector<T>::getSize() const
{
	return _size;
}

template <class T>
MyVector<T>::MyVector(std::initializer_list<T> elements)
{
	_size = _capacity = elements.size();
	_arr = allocateArr(_size);
	std::copy(elements.begin(), elements.end(), _arr);
}

//
//template <class T>
//MyVector<T>::MyVector()
//	:_arr(nullptr), _size(0), _capacity(10)
//{
//	_arr = allocateArr(10);
//}


template <class T>
MyVector<T>::MyVector(int initialCapacity)
	: _capacity(initialCapacity), _size(0)
{
	_arr = allocateArr(initialCapacity);
}

template <class T>
MyVector<T>::~MyVector()
{
	freeMem();
}

template <class T>
MyVector<T>::MyVector(const MyVector& obj)
	:_capacity(obj._capacity), _size(obj._size)
{
	_capacity = _capacity ? _capacity : 1;

	_arr = allocateArr(_capacity);
	try
	{
		for (size_t i = 0; i < obj._size; i++)
		{
			_arr[i] = obj._arr[i];
		}
	}
	catch (...)
	{
		freeMem();
		throw;
	}
}

template <class T>
MyVector<T>& MyVector<T>::operator=(const MyVector& obj)
{
	if (this != &obj)
	{
		freeMem();

		_capacity = obj._capacity ? obj._capacity : 1;

		try
		{
			_arr = allocateArr(_capacity);
			_size = obj._size;

			for (size_t i = 0; i < obj._size; i++)
			{
				_arr[i] = obj._arr[i];
			}
		}
		catch (...)
		{
			freeMem();
			throw;
		}
	}
	return *this;
}

template <class T>
template <class Y>
MyVector<T>::MyVector(const MyVector<Y>& obj)
	:_size(obj._size), _capacity(obj._capacity)
{
	_capacity = _capacity ? _capacity : 1;

	try
	{
		_arr = allocateArr(_capacity);
		for (size_t i = 0; i < _size; ++i)
		{
			_arr[i] = obj._arr[i];
		}
	}
	catch (...)
	{
		freeMem();
	}
}

template <class T>
template <class Y>
MyVector<T>& MyVector<T>::operator=(const MyVector<Y>& obj)
{
	if (this != &obj)
	{
		freeMem();
		_capacity = _capacity ? _capacity : 1;

		try
		{
			_arr = allocateArr(_capacity);
			_size = obj._size;

			for (size_t i = 0; i < obj._size; i++)
			{
				_arr[i] = obj._arr[i];
			}
		}
		catch (...)
		{
			freeMem();
		}
	}
	return *this;
}

template <class T>
void MyVector<T>::push(const T& element)
{
	if (_size == _capacity)
	{
		resizeVector();
	}
	_arr[_size++] = element;
}

template <class T>
void MyVector<T>::remove()
{
	removeAt(_size - 1);
}


template <class T>
void MyVector<T>::removeAt(size_t pos)
{
	if (pos >= _size)
	{
		throw std::invalid_argument("Invalid index give\n");
	}

	for (size_t i = pos; i < _size - 1; i++)
	{
		_arr[i] = _arr[i + 1];
	}
	_size--;
}


template <class T>
void MyVector<T>::removeSubarray(size_t from, size_t to)
{
	if (!(0 <= from && from <= _size &&
		0 <= to && to <= _size &&
		from <= to))
	{
		throw std::invalid_argument("Invalid index give\n");
	}

	if (from == to)
	{
		removeAt(from);
		return;
	}

	for (size_t i = from; i <= to; i++)
	{
		removeAt(from);
	}
}

template <class T>
T& MyVector<T>::operator[](size_t index)
{
	return _arr[index];
}

template <class T>
const T& MyVector<T>::operator[](size_t index) const
{
	return _arr[index];
}

template <class T>
T& MyVector<T>::at(size_t index)
{
	if (!(0 <= index && index <= _size))
	{
		throw std::invalid_argument("Invalid index give\n");
	}
	return _arr[index];
}


template <class T>
bool MyVector<T>::isTrueForAll(bool(*predicate)(const T&))
{
	for (size_t i = 0; i < _size; i++)
	{
		if (!predicate(_arr[i]))
		{
			return false;
		}
	}
	return true;
}

template <class T>
MyVector<T> MyVector<T>::operator+(const MyVector& obj)
{
	MyVector toReturn;
	int newCapacity = _size + obj._size;
	T* arrToReturn = allocateArr(newCapacity);
	toReturn._size = newCapacity;
	toReturn._capacity = newCapacity;
	size_t index = 0;

	for (size_t i = 0; i < _size; i++)
	{
		arrToReturn[index] = _arr[i];
		index++;
	}

	for (size_t i = 0; i < obj._size; i++)
	{
		arrToReturn[index] = obj._arr[i];
		index++;
	}

	toReturn._arr = arrToReturn;

	return toReturn;
}


template <class T>
void MyVector<T>::map(T(*f)(const T&))
{
	for (size_t i = 0; i < _size; i++)
	{
		_arr[i] = f(_arr[i]);
	}
}

#endif // !_MY_VECTOR_
