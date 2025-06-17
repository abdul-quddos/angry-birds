#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include<iostream>
using namespace std;
template<class T>
class Dynamic_array {
private:
	T* data;
	int len;
	int cap;

	// Doubles the current capacity when needed
	void double_capacity()
	{
		this->cap *= 2;
		T* newdata = new T[cap];
		for (int i = 0; i < this->len; i++)
			newdata[i] = data[i];
		delete[]data;
		data = newdata;
	}

public:
	// Constructors & Destructor
	Dynamic_array() :len{ 0 }, cap{ 0 }, data{ nullptr } {} // Default constructor
	Dynamic_array(int count, T value)   // Fill constructor
	{
		this->len = count;
		this->cap = count * 2;
		this->data = new T[cap];
		for (int i = 0; i < this->len; i++)
			this->data[i] = value;
	}
	Dynamic_array(const Dynamic_array& other) // Copy constructor
	{
		if (this != &other)
		{
			this->len = other.len;
			this->cap = other.cap;
			clear();
			this->data = new T[cap];
			for (int i = 0; i < this->len; i++)
				this->data[i] = other.data[i];
		}
	}
	~Dynamic_array()  // Destructor
	{
		delete[]data;
	}

	// Operators
	Dynamic_array& operator=(const Dynamic_array& other)  // Copy assignment
	{
		if (this != &other)
		{
			this->len = other.len;
			this->cap = other.cap;
			clear();
			this->data = new T[cap];
			for (int i = 0; i < this->len; i++)
				this->data[i] = other.data[i];
		}
		return *this;
	}
	T& operator[](int index)                          // Subscript operator
	{
		if (index >= 0 && index < len)
			return this->data[index];
		else
			cout << "Given Index is out of Range\n";
	}
	const T& operator[](int index) const           // Const subscript operator
	{
		if (index >= 0 && index < len)
			return this->data[index];
		else
			cout << "Given Index is out of Range\n";
	}
	bool operator==(const Dynamic_array& other) const // Equality comparison
	{
		if (this->len != other.len)
			return false;
		for (int i = 0; i < this->len; i++)
			if (this->data[i] != other.data[i])
				return false;
		return true;
	}
	bool operator!=(const Dynamic_array& other) const // Inequality comparison
	{
		if (*this == other)
			return false;
		else
			return true;
	}
	Dynamic_array operator+(const Dynamic_array& other) const  // Concatenation
	{
		Dynamic_array res;
		res.cap = this->cap + other.cap;
		res.len = this->len + other.len;
		res.data = new T[res.cap];
		for (int i = 0; i < this->len; i++)
			res.data[i] = this->data[i];
		for (int i = 0; i < other.len; i++)
			res.data[i + this->len] = other.data[i];
		return res;
	}
	Dynamic_array& operator+=(const Dynamic_array& other)   // Append
	{
		while (this->cap < this->len + other.len)
			double_capacity();
		for (int i = 0; i < other.len; i++)
			this->data[i + this->len] = other.data[i];
		this->len += other.len;
		return *this;
	}

	// Modifiers
	void push(T value)                 // Adds an element to the end
	{
		if (this->len == this->cap)
			double_capacity();
		this->data[len] = value;
		this->len++;
	}
	void pop()                        // Removes the last element
	{
		if (this->len > 0)
			this->len--;
	}
	void insert_at(int index, T value)  // Inserts value at index
	{
		if (index < 0 || index > len)
			return;
		if (len == cap)
			double_capacity();
		for (int i = len; i > index; i--)
			data[i] = data[i - 1];
		data[index] = value;
		len++;
	}
	void delete_at(int index)            // Deletes value at index
	{
		if (index < 0 || index >= len)
			return;
		for (int i = index; i < len - 1; i++)
			data[i] = data[i + 1];
		len--;
	}
	void reserve(int new_capacity)     // Reserves a new capacity
	{
		if (new_capacity <= len)
			return;
		T* newdata = new T[new_capacity];
		for (int i = 0; i < len; i++)
			newdata[i] = data[i];
		delete[]data;
		data = newdata;
		cap = new_capacity;
	}
	void clear()                       // Clears all elements
	{
		this->cap = 0;
		this->len = 0;
		delete[] this->data;
		data = nullptr;
	}
	void swap(Dynamic_array& other)    // Swaps with another array
	{
		T* tempdata = this->data;
		this->data = other.data;
		other.data = tempdata;
		int tempcap = this->cap;
		this->cap = other.cap;
		other.cap = tempcap;
		int templen = this->len;
		this->len = other.len;
		other.len = templen;
	}
	void shrink_to_fit()                // Reduces capacity to match size
	{
		reserve(len);
	}
	void reverse()                   // Reverses the array elements
	{
		for (int i = 0, j = len - 1; i < j; i++, j--)
		{
			T temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}
	// Accessors
	bool empty() const // Checks if array is empty
	{
		if (this->len == 0)
			return true;
		else
			return false;
	}
	int size() const  // Returns current size
	{
		return len;
	}

	T& at(int index)   // Bounds-checked element access
	{
		if (index >= 0 && index < len)
			return data[index];
	}
	const T& at(int index) const
	{
		if (index >= 0 && index < len)
			return data[index];
	}

	T& front()  // Returns first element
	{
		return at(0);
	}
	const T& front() const
	{
		return at(0);
	}

	T& back()  // Returns last element
	{
		return at(len - 1);
	}
	const T& back() const
	{
		return at(len - 1);
	}

	int find(T value) const // Return index of first instance, or -1 if non-existent
	{
		for (int i = 0; i < len; i++)
			if (data[i] == value)
				return i;
		return -1;
	}
};

#endif DYNAMIC_ARRAY_H