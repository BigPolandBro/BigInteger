#pragma once

#include "iostream"
#include "vector"
#include "string"
#include "algorithm"

template<int LEN_BASE>
class BigInteger
{
public:
	BigInteger();

	BigInteger(const std::string& s);

	BigInteger(char* s);

	BigInteger(int x);

	BigInteger(const BigInteger& x);

	bool empty() const;

	BigInteger& operator=(const BigInteger& x);

	explicit operator int();

	// addition

	BigInteger& operator+=(const BigInteger& x);

	const BigInteger operator+(const BigInteger& x) const;

	BigInteger& operator++();

	const BigInteger operator++(int);

	// subtraction

	// *this should be >= x

	BigInteger& operator-=(const BigInteger& x);

	const BigInteger operator-(const BigInteger& x) const;

	// multiplication

	BigInteger& operator*=(const int& x);

	BigInteger& operator*=(const BigInteger& x);

	const BigInteger operator*(const int& x) const;

	const BigInteger operator*(const BigInteger& x) const;

	// division

	BigInteger& operator/=(const int& x);

	const BigInteger operator/(const int& x) const;

	BigInteger& operator/=(const BigInteger& x);

	// comparison operators

	bool operator<(const BigInteger& x) const;

	bool operator>(const BigInteger& x) const;

	bool operator<=(const BigInteger& x) const;

	bool operator>=(const BigInteger& x) const;

	bool operator==(const BigInteger& x) const;

	bool operator!=(const BigInteger& x) const;

	// input-output

	friend std::ostream& operator<<(std::ostream& out, const BigInteger<LEN_BASE>& x)
	{
		out << (x.empty() ? 0 : x.digits.back());
		for (int i = (int)x.digits.size() - 2; i >= 0; --i)
		{
			std::string s = std::to_string(x.digits[i]);
			std::string t;
			int leadingZeros = LEN_BASE - s.size();
			while (leadingZeros--) t += '0';
			t += s;

			out << t;
		}
		return out;
	}

	friend std::istream& operator>>(std::istream& in, BigInteger& x)
	{
		std::string s;
		in >> s;
		x = BigInteger(s);
		return in;
	}

private:
	std::vector<int> digits;
	const int BASE = pow(10, LEN_BASE);

	void removeLeadingZeros();

	bool fitsIntoInt(int &x) const;
};




