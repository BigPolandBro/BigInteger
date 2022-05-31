#include "BigInteger.h"

//-----------------------------------------------------------------
//default constructor
BigInteger::BigInteger()
{
num = {};
}

//
//constructors
//

//-----------------------------------------------------------------
BigInteger::BigInteger(const std::string &s)
{
	num.clear();
	for (int i = s.size(); i > 0; i -= lenBase)
	{
		int start = i - lenBase >= 0 ? i - lenBase : 0;
		num.push_back(stoi(s.substr(start, i - start)));
	}
}

//-----------------------------------------------------------------
BigInteger::BigInteger(char* s)
{
	num.clear();
	for (int i = strlen(s); i > 0; i -= lenBase)
	{
		char *start = (i - lenBase >= 0 ? s + i - lenBase : s);
		s[i] = 0;
		num.push_back(atoi(start));
	}
}

//-----------------------------------------------------------------
BigInteger::BigInteger(int x)
{
	num.clear();
	num = { x };
}

//-----------------------------------------------------------------
//copy constructor
BigInteger::BigInteger(const BigInteger &x)
{
	this->num = x.num;
}

//-----------------------------------------------------------------
//destructor
BigInteger::~BigInteger()
{
	num.clear();
}

//-----------------------------------------------------------------
//check if it is empty
bool BigInteger::empty() const
{
	return num.size() == 0;
}

//
//operators
//

//-----------------------------------------------------------------
BigInteger& BigInteger::operator=(const BigInteger &x)
{
	if (&x == this)return *this;

	num = x.num;

	return *this;
}

//-----------------------------------------------------------------
//c-style cast
BigInteger::operator int()
{
	try
	{
		if (num.size() > 2)
		{
			throw(-1);
		}
	}
	catch (int x)
	{
		std::cout << "Cannot fit in integer type\n";
		return x;
	}

	if (num.empty())return 0;

	int ans = num[0];

	if (num.size() == 1)
	{
		return ans;
	}
	else
	{
		try
		{
			if (num[1] > 2 || ans > INT_MAX - num[1] * base)
			{
				throw(-1);
			}
			else
			{
				ans += num[1] * base;
				return ans;
			}
		}
		catch (int x)
		{
			std::cout << "Cannot fit in integer type\n";
			return x;
		}
	}
}

//
//addition
//

//-----------------------------------------------------------------
BigInteger& BigInteger::operator+=(const BigInteger& x)
{
	int n = num.size();
	int m = x.num.size();

	int carry = 0;
	for (int i = 0; i < std::max(n, m) || carry; i++)
	{
		if (i >= n)num.push_back(0);
		num[i] += (i < m ? x.num[i] : 0) + carry;

		carry = 0;
		if (num[i] > base)
		{
			num[i] -= base;
			carry = 1;
		}
	}

	return *this;
}

//-----------------------------------------------------------------
const BigInteger BigInteger::operator+(const BigInteger& x) const
{
	BigInteger res = *this;
	return res += x;
}

//-----------------------------------------------------------------
//pre-increment
BigInteger& BigInteger::operator++()
{
	return *this += 1;
}

//-----------------------------------------------------------------
//post-increment
const BigInteger BigInteger::operator++(int)
{
	BigInteger tmp = *this;
	*this += 1;
	return tmp;
}

//
//subtraction
//

//-----------------------------------------------------------------
//if *this >= x
BigInteger& BigInteger::operator-=(const BigInteger& x)
{
	int n = num.size();
	int m = x.num.size();

	int carry = 0;
	for (int i = 0; i < m || carry; i++)
	{
		num[i] -= carry + (i < m ? x.num[i] : 0);

		carry = 0;
		if (num[i] < 0)
		{
			num[i] += base;
			carry = 1;
		}
	}

	removeLeadingZeros();

	return *this;
}

//-----------------------------------------------------------------
const BigInteger BigInteger::operator-(const BigInteger& x) const
{
	BigInteger res = *this;
	return res -= x;
}

//
//multiplication
//

//-----------------------------------------------------------------
BigInteger& BigInteger::operator*=(const int& x)
{
	int n = num.size();

	int carry = 0;
	for (int i = 0; i < n || carry; i++)
	{
		if (i >= num.size())
		{
			num.push_back(0);
		}

		long long val = (i < n ? num[i] : 0);
		val *= x;
		val += carry;

		num[i] = val % base;
		carry = val / base;
	}

	removeLeadingZeros();

	return *this;
}

//-----------------------------------------------------------------
BigInteger& BigInteger::operator*=(const BigInteger& x)
{
	int n = num.size();
	int m = x.num.size();

	BigInteger y = *this;
	num.assign(n + m, 0);

	for (int j = 0; j < m; j++)
	{
		int carry = 0;
			
		for(int i = 0; i < n || carry; i++)
		{
			if (i + j >= num.size())
			{
				num.push_back(0);
			}

			long long val = (i < n ? y.num[i] : 0);
			val *= x.num[j];
			val += carry;

			num[i + j] += val % base;
			carry = val / base;
		}
	}

	removeLeadingZeros();

	return *this;
}

//-----------------------------------------------------------------
const BigInteger BigInteger::operator*(const int& x)const
{
	BigInteger res = *this;
	return res *= x;
}

//-----------------------------------------------------------------
const BigInteger BigInteger::operator*(const BigInteger& x)const
{
	BigInteger res = *this;
	return res *= x;
}

//
//division
//

//-----------------------------------------------------------------
BigInteger& BigInteger::operator/=(const int& x)
{
	int carry = 0;
	int n = num.size();
	for (int i = n - 1; i >= 0; -- i)
	{
		long long val = num[i] + base*carry;
		num[i] = val / x;
		carry = val % x;
	}

	removeLeadingZeros();
	return *this;
}

//-----------------------------------------------------------------
const BigInteger BigInteger::operator/(const int& x)const
{
	BigInteger res = *this;
	return res /= x;
}

//-----------------------------------------------------------------
BigInteger& BigInteger::operator/=(const BigInteger& x)
{
	if (*this < x)
	{
		*this = "0";
		return *this;
	}

	//this >= x
	int n = num.size();
	for (int i = n - 1; i >= 0; i--)
	{
		//TO DO
	}
}

//
//comparison operators
//

//-----------------------------------------------------------------
bool BigInteger::operator<(const BigInteger& x) const
{
	int n = num.size();
	int m = x.num.size();

	if (n < m)return true;
	if (n > m)return false;

	//n == m
	for (int i = n - 1; i >= 0; i--)
	{
		if (num[i] < x.num[i])return true;
		if (num[i] > x.num[i])return false;
	}
	return false;
}

//-----------------------------------------------------------------
bool BigInteger::operator>(const BigInteger& x)const
{
	return x < *this;
}

//-----------------------------------------------------------------
bool BigInteger::operator<=(const BigInteger& x)const
{
	return !(*this > x);
}

//-----------------------------------------------------------------
bool BigInteger::operator>=(const BigInteger& x)const
{
	return !(*this < x);
}

//-----------------------------------------------------------------
bool BigInteger::operator==(const BigInteger& x)const
{
	return !(*this < x || *this > x);
}

//-----------------------------------------------------------------
bool BigInteger::operator!=(const BigInteger& x)const
{
	return !(*this == x);
}

//
//input-output
//

//-----------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const BigInteger& x)
{
	out << (x.empty() ? 0 : x.num.back());
	for (int i = (int)x.num.size() - 2; i >= 0; --i)
	{
		std::string s = std::to_string(x.num[i]);
		std::string t;
		int leadingZeros = BigInteger::lenBase - s.size();
		while (leadingZeros--) t += '0';
		t += s;

		out << t;
	}
	return out;
}

//-----------------------------------------------------------------
std::istream& operator>>(std::istream& in, BigInteger& x)
{
	std::string s;
	in >> s;
	x = BigInteger(s);
	return in;
}

//-----------------------------------------------------------------
void BigInteger::removeLeadingZeros()
{
	while (num.size() > 1 && num.back() == 0)
		num.pop_back();
}




