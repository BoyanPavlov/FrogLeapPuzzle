#include <iostream>
using std::size_t;

#ifndef _MY_STRING_
#define _MY_STRING_

class MyString
{
private:
	char* _str; // Pointer to the first character of the string
	size_t _size; // Length of the string
	size_t _capacity; // Length of the string

	char* allocateString(size_t len); // Allocates memory for the string
	void freeMem(); //Frees allocated mem for the string
	void resize(); //Makes an attempt to double the capacity of the string

public:
	MyString(); // Default constructor
	MyString(const MyString& other); // Copy constructor
	MyString& operator=(const MyString& other); // Copy assignment operator
	~MyString(); // Destructor

	MyString(MyString&& obj);
	MyString& operator=(MyString&& obj);

	MyString(const char* text); // Constructor with a C-string parameter
	MyString& operator+=(const char& letter); // Appends a character to the end of the string
	MyString& operator+=(const MyString& rhs); // Appends another string to the end of the string

	MyString operator+(const MyString& rhs);

	bool operator==(const MyString& rhs) const; // Equality comparison operator
	bool operator!=(const MyString& rhs) const; // Equality comparison operator

	friend bool compareStrings(const MyString& leftStr, const MyString& rightStr, bool asc);//string comparator by the given flag
	bool operator>(const MyString& rhs)const; //Operator >
	bool operator<(const MyString& rhs)const; //Operator <

	char& at(size_t pos); // Returns a reference to the character at a specified position
	const char& at(size_t pos) const; // Returns a const reference to the character at a specified position

	char& operator[](size_t pos); // Returns a reference to the character at a specified position
	const char& operator[](size_t pos) const; // Returns a const reference to the character at a specified position

	char& front(); // Returns a reference to the first character
	const char& front() const; // Returns a const reference to the first character

	char& back(); // Returns a reference to the last character
	const char& back() const; // Returns a const reference to the last character

	bool empty() const; // Returns true if the string is empty, false otherwise

	void clear(); // Clears the string

	void push_back(char c); // Appends a character to the end of the string
	void pop_back(); // Removes the last character from the string
	const char* c_str() const; // Returns a pointer to the C-string representation of the string

	size_t size() const; // Returns the length of the string

	int find(char c) const; // Returns the position of the first occurrence of a character in the string, or -1 if not found
	int find_the_first_c(char c) const; // Returns the position of the first occurrence of a character in the string, or -1 if not found
	int find_the_last_c(char c) const; // Returns the position of the last occurrence of a character in the string, or -1 if not found

	MyString getReversedString();

	friend std::ostream& operator<<(std::ostream& out, const MyString& obj);
	friend std::istream& operator>>(std::istream& in, MyString& obj);
};

#endif // _MY_STRING_
