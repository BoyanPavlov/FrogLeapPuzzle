#include "MyString.hpp"
#include "StringUtils.hpp"
#pragma warning(disable : 4996)


char* MyString::allocateString(size_t len)
{
	char* tmp = nullptr;
	try
	{
		tmp = new char[len + 1]();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		throw;
	}
	return tmp;
}


void MyString::freeMem()
{
	delete[] _str;
	_str = nullptr;
}

void MyString::resize()
{
	if (!_capacity)
	{
		_capacity = 10;
		_str = allocateString(_capacity);
		return;
	}

	_capacity *= 2;
	try
	{
		char* buffer = allocateString(_capacity);
		strcpy(buffer, _str);
		freeMem();
		_str = buffer;

	}
	catch (...)
	{
		std::cerr << "String wasn't resized\n";
	}
}


MyString::MyString()
	: _str(nullptr), _size(0), _capacity(0)
{
}

MyString::MyString(const MyString& other)
	: _str(nullptr), _capacity(other._size), _size(other._size)
{
	if (other._str)
	{
		try
		{
			_str = allocateString(_size);
			strcpy(_str, other._str);
		}
		catch (...)
		{
			freeMem();
		}
	}
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		freeMem();
		_capacity = other._size;
		_size = other._size;

		try
		{
			_str = allocateString(_size);
			strcpy(_str, other._str);
		}
		catch (...)
		{
			freeMem();
		}
	}

	return *this;
}

MyString::~MyString()
{
	freeMem();
}


MyString::MyString(MyString&& obj)
	:_str(nullptr), _size(0), _capacity(0)
{
	std::swap(_str, obj._str);
	std::swap(_capacity, obj._capacity);
	std::swap(_size, obj._capacity);
}

MyString& MyString::operator=(MyString&& obj)
{
	if (this != &obj)
	{
		freeMem();
		std::swap(_str, obj._str);
		std::swap(_capacity, obj._capacity);
		std::swap(_size, obj._size);
		return *this;
	}
	return *this;
}


MyString::MyString(const char* text)
	: _str(nullptr), _capacity(0), _size(0)
{
	if (text)
	{
		_size = StringUtils::strLen(text);
		_capacity = _size;
		try
		{
			_str = allocateString(_size);
			strcpy(_str, text);
		}
		catch (...)
		{
			std::cerr << "Couldn't copy string\n";
		}
	}
}

MyString& MyString::operator+=(const char& letter)
{
	if (_size == _capacity)
	{
		resize();
	}
	push_back(letter);
	return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{
	while (_capacity < _size + rhs._size)
	{
		resize();
	}

	for (size_t i = 0; i < rhs._size; i++)
	{
		_str[_size++] = rhs[i];
	}

	return *this;
}


MyString MyString::operator+(const MyString& rhs)
{
	char* tmpStr = allocateString(_size + rhs._size);
	int index = 0;

	for (size_t i = 0; i < _size; i++)
	{
		tmpStr[index++] = _str[i];
	}

	for (size_t i = 0; i < rhs._size; i++)
	{
		tmpStr[index++] = rhs[i];
	}

	MyString tmpObj(tmpStr);
	delete[] tmpStr;
	return tmpObj;
}


bool MyString::operator==(const MyString& rhs) const
{
	if (!(StringUtils::strCmp(_str, rhs._str)))
	{
		return true;
	}
	return false;
}

bool MyString::operator!=(const MyString& rhs) const
{
	return !operator==(rhs);
}

bool compareStrings(const MyString& leftStr, const MyString& rightStr, bool asc)
{
	bool result = asc ? leftStr < rightStr : rightStr < leftStr;
	return result;
}

bool MyString::operator>(const MyString& rhs)const
{
	return StringUtils::strGreaterThan(_str, rhs._str);
}

bool MyString::operator<(const MyString& rhs)const
{
	return StringUtils::strGreaterThan(rhs._str, _str);
}


char& MyString::at(size_t pos)
{
	if (pos < 0 || pos >= _size)
	{
		throw std::invalid_argument("Out of range");
	}
	return _str[pos];
}

const char& MyString::at(size_t pos) const
{
	if (pos < 0 || pos >= _size)
	{
		throw std::invalid_argument("Out of range");
	}
	return _str[pos];
}

char& MyString::operator[](size_t pos)
{
	if (pos < 0 || pos >= _size)
	{
		return _str[_size];
	}
	return _str[pos];
}

const char& MyString::operator[](size_t pos) const
{
	if (pos < 0 || pos >= _size)
	{
		return _str[_size];
	}
	return _str[pos];
}


char& MyString::front()
{
	if (!_size)
	{
		throw std::invalid_argument("empty string\n");
	}
	return _str[0];
}

const char& MyString::front() const
{
	if (!_size)
	{
		throw std::invalid_argument("empty string\n");
	}
	return _str[0];
}

char& MyString::back()
{
	if (!_size)
	{
		throw std::invalid_argument("empty string\n");
	}
	return _str[_size - 1];
}

const char& MyString::back() const
{
	if (!_size)
	{
		throw std::invalid_argument("empty string\n");
	}
	return _str[_size - 1];
}

bool MyString::empty() const
{
	if (!_size)
	{
		return true;
	}
	return false;
}

void MyString::clear()
{
	freeMem();
	_str = allocateString(_capacity);
	_size = 0;
}

void MyString::push_back(char c)
{
	if (_size == _capacity)
	{
		resize();
	}
	_str[_size++] = c;
}


void MyString::pop_back()
{
	_str[--_size] = '\0';
}
const char* MyString::c_str() const
{
	return _str;
}

size_t MyString::size() const
{
	return _size;
}

int MyString::find(char c) const
{
	for (size_t i = 0; i < _size; i++)
	{
		if (_str[i] == c)
		{
			return i;
		}
	}
	return -1;
}

int MyString::find_the_first_c(char c) const
{
	return find(c);
}

int MyString::find_the_last_c(char c) const
{
	for (int i = _size - 1; i > 0; i--)
	{
		if (_str[i] == c)
		{
			return i;
		}
	}
	return -1;
}

MyString MyString::getReversedString()
{
	MyString result(*this);

	size_t size = result.size();

	for (size_t i = 0; i < size; i++)
	{
		result[size - i - 1] = this->at(i);
	}

	return result;
}

std::ostream& operator<<(std::ostream& out, const MyString& obj)
{
	if (obj._str)
	{
		out << obj.c_str();
	}
	return out;
}

std::istream& operator>>(std::istream& in, MyString& obj)
{
	char tmp[1000] = {};
	in >> tmp;
	MyString tmpObj(tmp);
	obj = tmp;
	return in;
}