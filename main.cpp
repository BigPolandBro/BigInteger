#include "BigInteger.h"

using StandardBigInt = BigInteger<9>;

int main()
{
	goto test;

	//declaration and input/output
	{
		StandardBigInt x;
		std::cin >> x;
		std::cout << x << '\n';
		return 0;
	}

	//StandardBigInt to int
	//int y = x; --> cannot do it as keyword explicit is used
	{
		StandardBigInt x = std::string("123462386458754658365474746537254635487638476583");
		int y = int(x);
		std::cout << y << '\n';
		return 0;
	}

	//addition
	{
		StandardBigInt x = std::string("123462386458754658365474746537254635487638476583");
		StandardBigInt a = 3'746'373;
		StandardBigInt y = x;
		y += a;
		std::cout << x + a << '\n';
		std::cout << y << '\n';
		return 0;
	}

	//subtraction
	{
		StandardBigInt x = std::string("123462386458754658365474746537254635487638476583");
		StandardBigInt a = 3'746'373;
		x += a;

		StandardBigInt y = x;
		y -= a;

		std::cout << (x - a) << '\n';
		std::cout << y << '\n';
		return 0;
	}

	//multiplication
	{
		StandardBigInt a = std::string("1233465738568765376537864");
		StandardBigInt b = 123;
		//std::cout << a << " " << b << '\n';

		std::cout << a * b << '\n';
		a *= b;
		std::cout << a << '\n';
	}

test:
	//division
	{
		StandardBigInt a = std::string("123456789101112131415348956985829360547348653895462965");
		int b = 3;

		std::cout << a << "\n";
		a *= b;
		std::cout << a << "\n";
		a /= b;
		std::cout << a << "\n";
	}

	return 0;
}