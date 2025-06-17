#ifndef MYSTRING_H
#define MYSTRING_H


#include<iostream>
using namespace std;

class String {
	int len;
	int cap;
	char* str;
	int getlen(const char* arr);
public:
	String();
	String(const char* arr);
	String(const String& other);
	String& operator =(const String& other);
	String(int num);
	String itos(int num);
	void replacefirst(char c);
	String(int n, char c);
	int stoi() const;
	String& trim();
	const char& operator[](int i) const;
	char& operator[](int i);
	String* split(char delim, int& count) const;
	bool is_delim(char ch, const char* delim) const;
	String* tokenize(const char* delim, int& count) const;
	String concat(const String& s2) const;
	String& append(const String& s2);
	int* all_sub_strings(const String& other, int& count) const;
	int find_first(char ch) const;
	int find_first(const String& other) const;
	int find_last(char ch) const;
	int find_last(const String& other) const;
	int* find_all(char ch, int& C) const;
	int* find_all(const String& other, int& C) const;
	bool is_less(const String& other);
	bool is_greater(const String& other);
	bool is_equal(const String& other);
	friend ostream& operator <<(ostream& os, const String& _s);
	friend istream& operator >>(istream& is, String& _s);
	void shiftright(int idx, int noOftimes);
	void shiftleft(int idx, int noOftimes);
	void remove_at(int idx);
	void insert_at(int idx, char ch);
	void insert_at(int idx, const String& sub);
	void remove_first(char ch);
	void remove_last(char ch);
	void remove_all(char ch);
	void clear();
	void toUpper();
	void toLower();
	friend String operator +(const String& s1, const String& s2);
	~String();

};

#endif MYSTRING_H#pragma once
