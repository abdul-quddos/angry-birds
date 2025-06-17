#include<iostream>
using namespace std;
#include"mystring.h"


int String::getlen(const char* arr)
{
	int i = 0;
	for (; arr[i] != '\0'; i++) {}
	return i;
}
String::String() :len{ 0 }, cap{ 0 }, str{ nullptr } {}

String::String(const char* arr)
{
	this->len = getlen(arr);
	this->cap = this->len * 2;
	this->str = new char[this->cap];
	for (int i = 0; i < this->len; i++)
		this->str[i] = arr[i];
	this->str[this->len] = '\0';
}

String operator +(const String& s1, const String& s2)
{
	String res;
	res.cap = s1.cap + s2.cap;
	res.len = s1.len + s2.len;
	res.str = new char[res.cap];
	for (int i = 0; i < s1.len; i++)
		res.str[i] = s1.str[i];
	for (int i = 0; i < s2.len; i++)
		res.str[i + s1.len] = s2.str[i];
	res.str[res.len] = '\0';
	return res;
}
String::String(const String& other)
{
	this->len = other.len;
	this->cap = other.cap;
	this->str = new char[this->cap];
	for (int i = 0; i < other.len; i++)
		this->str[i] = other.str[i];
	this->str[other.len] = '\0';
}

String& String::operator =(const String& other)
{
	this->len = other.len;
	this->cap = other.cap;
	this->str = new char[this->cap];
	for (int i = 0; i < other.len; i++)
		this->str[i] = other.str[i];
	this->str[other.len] = '\0';
	return *this;
}

String::String(int num)
{
	*this = itos(num);
}

String String::itos(int num)
{
	int n = num, count = 0;
	if (num == 0)
		return String("0");

	while (n)
	{
		count++;
		n /= 10;
	}
	char* temp = new char[count + 1];
	temp[count] = '\0';
	n = num;
	while (n)
	{
		temp[--count] = '0' + (n % 10);
		n /= 10;
	}
	String result(temp);
	delete[] temp;
	return result;
}

void String::replacefirst(char c)
{
	if (this->str && this->len > 0)
		this->str[0] = c;
}

String::String(int n, char c)
{
	len = n;
	cap = len * 2;
	str = new char[cap];
	for (int i = 0; i < len; i++)
		str[i] = c;
	str[len] = '\0';
}

int String::stoi() const
{
	int res = 0;
	int i = 0;
	bool negative = false;
	if (str[i] == '-')
	{
		negative = true;
		i++;
	}
	while (str[i] != '\0')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (negative)
		return -res;
	else
		return res;

}

String& String::trim()
{
	int start = 0, end = len - 1;

	while (start < len && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n'))
		start++;
	while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n'))
		end--;

	int new_len = end - start + 1;
	char* temp = new char[new_len + 1];

	for (int i = 0; i < new_len; i++)
		temp[i] = str[start + i];
	temp[new_len] = '\0';

	delete[] str;
	str = temp;
	len = new_len;

	return *this;
}

const char& String::operator[](int i) const
{
	if (i >= 0 && i < this->len)
		return this->str[i];

}

char& String::operator[](int i)
{
	if (i >= 0 && i < this->len)
		return this->str[i];
	else
	{
		static char ch = '\0';
		return ch;
	}
}

String* String::split(char delim, int& count) const
{
	count = 0;
	bool flag = false;
	for (int i = 0; i < len; i++)
	{
		if (str[i] != delim && !flag)
		{
			count++;
			flag = true;
		}
		else if (str[i] == delim)
			flag = false;
	}
	String* parts = new String[count];
	int idx = 0, start = 0;
	flag = false;
	for (int i = 0; i < len; i++)
	{
		if (str[i] != delim && !flag)
		{
			start = i;
			flag = true;
		}
		else if (str[i] == delim && flag)
		{
			int new_len = i - start;
			char* temp = new char[new_len + 1];
			for (int j = 0; j < new_len; j++)
				temp[j] = str[start + j];
			temp[new_len] = '\0';
			parts[idx++] = String(temp);
			delete[] temp;
			flag = false;
		}
	}
	if (flag)
	{
		int new_len = len - start;
		char* temp = new char[new_len + 1];
		for (int j = 0; j < new_len; j++)
			temp[j] = str[start + j];
		temp[new_len] = '\0';
		parts[idx] = String(temp);
		delete[] temp;
	}
	return parts;
}

bool String::is_delim(char ch, const char* delim) const
{
	for (int i = 0; delim[i] != '\0'; i++)
		if (delim[i] == ch)
			return true;
	return false;
}

String* String::tokenize(const char* delim, int& count) const
{
	count = 0;
	bool flag = false;
	for (int i = 0; i < len; i++)
	{
		if (!is_delim(str[i], delim) && !flag)
		{
			count++;
			flag = true;
		}
		else if (is_delim(str[i], delim))
			flag = false;
	}
	String* tokens = new String[count];
	int idx = 0, start = 0;
	for (int i = 0; i <= len; i++)
	{
		if (i == len || is_delim(str[i], delim))
		{
			if (start < i)
			{
				int new_len = i - start;
				char* temp = new char[new_len + 1];
				for (int j = 0; j < new_len; j++)
					temp[j] = str[start + j];
				temp[new_len] = '\0';
				tokens[idx++] = String(temp);
				delete[] temp;
			}
			start = i + 1;
		}
	}
	return tokens;
}

String String::concat(const String& s2) const
{
	int new_len = this->len + s2.len;
	char* temp = new char[new_len + 1];
	for (int i = 0; i < this->len; i++)
		temp[i] = this->str[i];
	for (int i = 0; i < s2.len; i++)
		temp[this->len + i] = s2.str[i];
	temp[new_len] = '\0';
	String result(temp);
	delete[] temp;
	return result;
}

String& String::append(const String& s2)
{
	int new_len = this->len + s2.len;
	char* temp = new char[new_len + 1];
	for (int i = 0; i < this->len; i++)
		temp[i] = this->str[i];
	for (int i = 0; i < s2.len; i++)
		temp[len + i] = s2.str[i];
	temp[new_len] = '\0';
	delete[] str;
	str = temp;
	len = new_len;
	cap = new_len * 2;
	return *this;
}

int* String::all_sub_strings(const String& other, int& count) const
{
	count = 0;
	if (this->len == 0 || other.len == 0 || other.len > this->len)
		return nullptr;
	for (int i = 0; i <= this->len - other.len; i++)
	{
		bool flag = true;
		for (int j = 0; j < other.len; j++)
		{
			if (this->str[i + j] != other.str[j])
				flag = false;
		}
		if (flag)
			count++;
	}
	if (count == 0)
		return nullptr;
	int* parts = new int[count];
	int idx = 0;
	for (int i = 0; i <= this->len - other.len; i++)
	{
		bool flag = true;
		for (int j = 0; j < other.len; j++)
		{
			if (this->str[i + j] != other.str[j])
				flag = false;
		}
		if (flag)
			parts[idx++] = i;
	}
	return parts;

}

int String::find_first(char ch) const
{
	for (int i = 0; i < this->len; i++)
	{
		if (this->str[i] == ch)
			return i;
	}
	return -1;
}

int String::find_first(const String& other) const
{
	if (this->len == 0 || other.len == 0 || other.len > this->len)
		return -1;
	for (int i = 0; i <= this->len - other.len; i++)
	{
		bool flag = true;
		for (int j = 0; j < other.len; j++)
		{
			if (this->str[i + j] != other.str[j])
				flag = false;
		}
		if (flag)
			return i;
	}
	return -1;
}

int String::find_last(char ch) const
{
	for (int i = this->len - 1; i >= 0; i--)
	{
		if (this->str[i] == ch)
			return i;
	}
	return -1;
}

int String::find_last(const String& other) const
{
	if (this->len == 0 || other.len == 0 || other.len > this->len)
		return -1;
	for (int i = this->len - other.len; i >= 0; i++)
	{
		bool flag = true;
		for (int j = 0; j < other.len; j++)
		{
			if (this->str[i + j] != other.str[j])
				flag = false;
		}
		if (flag)
			return i;
	}
	return -1;
}

int* String::find_all(char ch, int& C) const
{
	C = 0;
	for (int i = 0; i < len; i++)
		if (str[i] == ch)
			C++;
	if (C == 0)
		return nullptr;
	int* parts = new int[C];
	int idx = 0;
	for (int i = 0; i < len; i++)
		if (str[i] == ch)
			parts[idx++] = i;

	return parts;
}

int* String::find_all(const String& other, int& C) const
{
	C = 0;
	if (this->len == 0 || other.len == 0 || other.len > this->len)
		return nullptr;
	for (int i = 0; i <= this->len - other.len; i++)
	{
		bool flag = true;
		for (int j = 0; j < other.len; j++)
		{
			if (this->str[i + j] != other.str[j])
				flag = false;
		}
		if (flag)
			C++;
	}
	if (C == 0)
		return nullptr;
	int* parts = new int[C];
	int idx = 0;
	for (int i = 0; i <= this->len - other.len; i++)
	{
		bool flag = true;
		for (int j = 0; j < other.len; j++)
		{
			if (this->str[i + j] != other.str[j])
				flag = false;
		}
		if (flag)
			parts[idx++] = i;
	}
	return parts;
}

bool String::is_less(const String& other)
{
	for (int i = 0; i < this->len && i < other.len; i++)
	{
		if (this->str[i] != other.str[i])
			return this->str[i] < other.str[i];
	}
	return this->len < other.len;
}

bool String::is_greater(const String& other)
{
	for (int i = 0; i < this->len && i < other.len; i++)
	{
		if (this->str[i] != other.str[i])
			return this->str[i] > other.str[i];
	}
	return this->len > other.len;
}

bool String::is_equal(const String& other)
{
	if (this->len != other.len)
		return false;

	for (int i = 0; i < len; i++) {
		if (this->str[i] != other.str[i])
			return false;
	}
	return true;
}

ostream& operator <<(ostream& os, const String& _s)
{
	os << _s.str;
	return os;
}
istream& operator >>(istream& is, String& _s)
{
	char temp[100];
	cin.getline(temp, 100);
	_s = String(temp);
	return is;
}

void String::shiftright(int idx, int noOftimes)
{
	if (idx >= len || noOftimes <= 0)
		return;
	int new_len = len + noOftimes;
	if (new_len >= cap)
	{
		cap = new_len * 2;
		char* new_str = new char[cap];
		*this = String(new_str);
	}
	for (int i = len - 1; i >= idx; i--)
		str[i + noOftimes] = str[i];
	for (int i = 0; i < noOftimes; i++)
		str[idx + i] = ' ';
	len = new_len;
	str[len] = '\0';
}

void String::shiftleft(int idx, int noOftimes)
{
	if (idx >= len || noOftimes <= 0)
		return;
	for (int i = idx; i < len - noOftimes; i++)
		str[i] = str[i + noOftimes];
	len -= noOftimes;
	str[len] = '\0';
}

void String::remove_at(int idx)
{
	if (idx < 0 || idx >= len)
		return;
	shiftleft(idx, 1);
}

void String::insert_at(int idx, char ch)
{
	if (idx < 0 || idx > len)
		return;
	shiftright(idx, 1);
	str[idx] = ch;
}
void String::insert_at(int idx, const String& sub)
{
	if (idx < 0 || idx > len)
		return;
	shiftright(idx, sub.len);
	for (int i = 0; i < sub.len; i++)
		str[idx + i] = sub.str[i];
}

void String::remove_first(char ch)
{
	for (int i = 0; i < len; i++)
	{
		if (str[i] == ch)
		{
			shiftleft(i, 1);
			return;
		}
	}
}

void String::remove_last(char ch)
{
	for (int i = len - 1; i >= 0; i--)
	{
		if (str[i] == ch)
		{
			shiftleft(i, 1);
			return;
		}
	}
}

void String::remove_all(char ch)
{
	for (int i = 0; i < len; )
	{
		if (str[i] == ch)
			shiftleft(i, 1);
		else
			i++;
	}
}

void String::clear()
{
	len = 0;
	str[0] = '\0';
}

void String::toUpper()
{
	for (int i = 0; i < len; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
}

void String::toLower()
{
	for (int i = 0; i < len; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
}


String::~String()
{
	delete[] this->str;
}

