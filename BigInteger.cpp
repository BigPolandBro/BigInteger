#include "BigInteger.h"


template class BigInteger<1>;
template class BigInteger<2>;
template class BigInteger<3>;
template class BigInteger<4>;
template class BigInteger<5>;
template class BigInteger<6>;
template class BigInteger<7>;
template class BigInteger<8>;
template class BigInteger<9>;

template<int LEN_BASE>
BigInteger<LEN_BASE>::BigInteger()
{
	digits = {};
}

template<int LEN_BASE>
BigInteger<LEN_BASE>::BigInteger(const std::string& s)
{
	digits.clear();
	for (int i = s.size(); i > 0; i -= LEN_BASE)
	{
		int start = i - LEN_BASE >= 0 ? i - LEN_BASE : 0;
		digits.push_back(stoi(s.substr(start, i - start)));
	}
}

template<int LEN_BASE>
BigInteger<LEN_BASE>::BigInteger(char* s)
{
	digits.clear();
	for (int i = strlen(s); i > 0; i -= LEN_BASE)
	{
		char *start = (i - LEN_BASE >= 0 ? s + i - LEN_BASE : s);
		s[i] = 0;
		digits.push_back(atoi(start));
	}
}

template<int LEN_BASE>
BigInteger<LEN_BASE>::BigInteger(int x)
{
	digits.clear();
	digits = { x };
}

template<int LEN_BASE>
BigInteger<LEN_BASE>::BigInteger(const BigInteger<LEN_BASE>& x)
{
	this->digits = x.digits;
}

template<int LEN_BASE>
bool BigInteger<LEN_BASE>::empty() const
{
	return digits.size() == 0;
}

template<int LEN_BASE>
BigInteger<LEN_BASE>& BigInteger<LEN_BASE>::operator=(const BigInteger<LEN_BASE>& x)
{
	if (&x == this)
	{
		return *this;
	}

	digits = x.digits;

	return *this;
}

template<int LEN_BASE>
BigInteger<LEN_BASE>::operator int()
{
	int answer = 0;
	if (!fitsIntoInt(answer))
	{
		throw std::runtime_error("Cannot be converted to int!");
	}
	return answer;
}

//addition

template<int LEN_BASE>
BigInteger<LEN_BASE>& BigInteger<LEN_BASE>::operator+=(const BigInteger<LEN_BASE>& x)
{
	int n = digits.size();
	int m = x.digits.size();

	bool carry = 0;
	for (int i = 0; i < std::max(n, m) || carry; i++)
	{
		if (i >= n)digits.push_back(0);
		digits[i] += (i < m ? x.digits[i] : 0) + carry;

		carry = 0;
		if (digits[i] > BASE)
		{
			digits[i] -= BASE;
			carry = 1;
		}
	}

	return *this;
}

template<int LEN_BASE>
const BigInteger<LEN_BASE> BigInteger<LEN_BASE>::operator+(const BigInteger<LEN_BASE>& x) const
{
	BigInteger<LEN_BASE> res = *this;
	return res += x;
}

template<int LEN_BASE>
BigInteger<LEN_BASE>& BigInteger<LEN_BASE>::operator++()
{
	return *this += 1;
}

template<int LEN_BASE>
const BigInteger<LEN_BASE> BigInteger<LEN_BASE>::operator++(int)
{
	BigInteger<LEN_BASE> tmp = *this;
	*this += 1;
	return tmp;
}

// subtraction

// *this should be >= x
template<int LEN_BASE>
BigInteger<LEN_BASE>& BigInteger<LEN_BASE>::operator-=(const BigInteger<LEN_BASE>& x)
{
	int n = digits.size();
	int m = x.digits.size();

	bool carry = 0;
	for (int i = 0; i < m || carry; i++)
	{
		digits[i] -= carry + (i < m ? x.digits[i] : 0);

		carry = 0;
		if (digits[i] < 0)
		{
			digits[i] += BASE;
			carry = 1;
		}
	}

	removeLeadingZeros();

	return *this;
}

template<int LEN_BASE>
const BigInteger<LEN_BASE> BigInteger<LEN_BASE>::operator-(const BigInteger<LEN_BASE>& x) const
{
	BigInteger<LEN_BASE> res = *this;
	return res -= x;
}

// multiplication

template<int LEN_BASE>
BigInteger<LEN_BASE>& BigInteger<LEN_BASE>::operator*=(const int& x)
{
	int n = digits.size();

	int carry = 0;
	for (int i = 0; i < n || carry; i++)
	{
		if (i >= digits.size())
		{
			digits.push_back(0);
		}

		long long val = (i < n ? digits[i] : 0);
		val *= x;
		val += carry;

		digits[i] = val % BASE;
		carry = val / BASE;
	}

	removeLeadingZeros();

	return *this;
}

template<int LEN_BASE>
BigInteger<LEN_BASE>& BigInteger<LEN_BASE>::operator*=(const BigInteger<LEN_BASE>& x)
{
	int n = digits.size();
	int m = x.digits.size();

	BigInteger<LEN_BASE> y = *this;
	digits.assign(n + m, 0);

	for (int j = 0; j < m; j++)
	{
		int carry = 0;
			
		for(int i = 0; i < n || carry; i++)
		{
			if (i + j >= digits.size())
			{
				digits.push_back(0);
			}

			long long val = (i < n ? y.digits[i] : 0);
			val *= x.digits[j];
			val += carry;

			digits[i + j] += val % BASE;
			carry = val / BASE;
		}
	}

	removeLeadingZeros();

	return *this;
}

template<int LEN_BASE>
const BigInteger<LEN_BASE> BigInteger<LEN_BASE>::operator*(const int& x) const
{
	BigInteger<LEN_BASE> res = *this;
	return res *= x;
}

template<int LEN_BASE>
const BigInteger<LEN_BASE> BigInteger<LEN_BASE>::operator*(const BigInteger<LEN_BASE>& x) const
{
	BigInteger<LEN_BASE> res = *this;
	return res *= x;
}

// division

template<int LEN_BASE>
BigInteger<LEN_BASE>& BigInteger<LEN_BASE>::operator/=(const int& x)
{
	int carry = 0;
	int n = digits.size();
	for (int i = n - 1; i >= 0; -- i)
	{
		long long val = digits[i] + (long long)BASE*carry;
		digits[i] = val / x;
		carry = val % x;
	}

	removeLeadingZeros();
	return *this;
}

template<int LEN_BASE>
const BigInteger<LEN_BASE> BigInteger<LEN_BASE>::operator/(const int& x) const
{
	BigInteger<LEN_BASE> res = *this;
	return res /= x;
}

template<int LEN_BASE>
BigInteger<LEN_BASE>& BigInteger<LEN_BASE>::operator/=(const BigInteger<LEN_BASE>& x)
{
	if (*this < x)
	{
		*this = "0";
		return *this;
	}

	//this >= x
	int n = digits.size();
	for (int i = n - 1; i >= 0; i--)
	{
		//TO DO
	}
}

// comparison operators

template<int LEN_BASE>
bool BigInteger<LEN_BASE>::operator<(const BigInteger<LEN_BASE>& x) const
{
	int n = digits.size();
	int m = x.digits.size();

	if (n < m)
	{
		return true;
	}

	if (n > m)
	{
		return false;
	}

	//n == m
	for (int i = n - 1; i >= 0; i--)
	{
		if (digits[i] < x.digits[i])
		{
			return true;
		}

		if (digits[i] > x.digits[i])
		{
			return false;
		}
	}
	return false;
}

template<int LEN_BASE>
bool BigInteger<LEN_BASE>::operator>(const BigInteger<LEN_BASE>& x) const
{
	return x < *this;
}

template<int LEN_BASE>
bool BigInteger<LEN_BASE>::operator<=(const BigInteger<LEN_BASE>& x) const
{
	return !(*this > x);
}

template<int LEN_BASE>
bool BigInteger<LEN_BASE>::operator>=(const BigInteger<LEN_BASE>& x) const
{
	return !(*this < x);
}

template<int LEN_BASE>
bool BigInteger<LEN_BASE>::operator==(const BigInteger<LEN_BASE>& x) const
{
	return !(*this < x || *this > x);
}

template<int LEN_BASE>
bool BigInteger<LEN_BASE>::operator!=(const BigInteger<LEN_BASE>& x) const
{
	return !(*this == x);
}

template<int LEN_BASE>
void BigInteger<LEN_BASE>::removeLeadingZeros()
{
	while (digits.size() > 1 && digits.back() == 0)
		digits.pop_back();
}

template<int LEN_BASE>
bool BigInteger<LEN_BASE>::fitsIntoInt(int &x) const
{
	if (digits.empty())
	{
		return true;
	}

	long long ans = 0;
	for (int i = digits.size() - 1; i >= 0; i--)
	{
		ans = ans*BASE + digits[i];
		if (ans > INT_MAX)return false;
	}

	x = ans;
	return true;
}




