#pragma once

#include "iostream"
#include "vector"
#include "string"
#include "algorithm"

class BigInteger
{
public:
	BigInteger();

	//constructors
	BigInteger(const std::string &s);

	BigInteger(char* s);

	BigInteger(int x);

	//copy constructor

	BigInteger(const BigInteger &x);

	//destructor

	~BigInteger();

	//check if it is empty
	bool empty() const;

	//operators

	BigInteger& operator=(const BigInteger &x);

	//c-style cast

	explicit operator int();

	//addition

	BigInteger& operator+=(const BigInteger& x);

	const BigInteger operator+(const BigInteger& x) const;

	//pre-increment
	BigInteger& operator++();

	//post-increment
	const BigInteger operator++(int);

	//subtraction

	//if *this >= x
	BigInteger& operator-=(const BigInteger& x);

	const BigInteger operator-(const BigInteger& x) const;

	//multiplication

	BigInteger& operator*=(const int& x);

	BigInteger& operator*=(const BigInteger& x);

	const BigInteger operator*(const int& x)const;

	const BigInteger operator*(const BigInteger& x)const;

	//division

	BigInteger& operator/=(const int& x);

	const BigInteger operator/(const int& x)const;

	BigInteger& operator/=(const BigInteger& x);

	//comparison operators

	bool operator<(const BigInteger& x) const;

	bool operator>(const BigInteger& x)const;

	bool operator<=(const BigInteger& x)const;

	bool operator>=(const BigInteger& x)const;

	bool operator==(const BigInteger& x)const;

	bool operator!=(const BigInteger& x)const;

	//input-output

	friend std::ostream& operator<<(std::ostream& out, const BigInteger& x);

	friend std::istream& operator>>(std::istream& in, BigInteger& x);

private:
	std::vector<int> num;
	static const int base = 1000 * 1000 * 1000;
	static const int lenBase = 9;
	//static const int base = 10;
	//static const int lenBase = 1;

	void removeLeadingZeros();
};




