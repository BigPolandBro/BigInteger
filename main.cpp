#include "BigInteger.h"

int main()
{
	goto test;

	//declaration and input/output
	{
		BigInteger x;
		std::cin >> x;
		std::cout << x << '\n';
		return 0;
	}

	//BigInteger to int
	//int y = x; --> cannot do it as keyword explicit is used
	{
		BigInteger x = std::string("123462386458754658365474746537254635487638476583");
		int y = int(x);
		std::cout << y << '\n';
		return 0;
	}

	//addition
	{
		BigInteger x = std::string("123462386458754658365474746537254635487638476583");
		BigInteger a = 3'746'373;
		BigInteger y = x;
		y += a;
		std::cout << x + a << '\n';
		std::cout << y << '\n';
		return 0;
	}

	//subtraction
	{
		BigInteger x = std::string("123462386458754658365474746537254635487638476583");
		BigInteger a = 3'746'373;
		x += a;

		BigInteger y = x;
		y -= a;

		std::cout << (x - a) << '\n';
		std::cout << y << '\n';
		return 0;
	}

	//multiplication
	{
		BigInteger a = std::string("1233465738568765376537864");
		BigInteger b = 123;
		//std::cout << a << " " << b << '\n';

		std::cout << a * b << '\n';
		a *= b;
		std::cout << a << '\n';
	}

test:
	//division
	{
		BigInteger a = std::string("123456789101112131415");
		int b = 3;

		std::cout << a << "\n";
		a *= b;
		std::cout << a << "\n";
		a /= b;
		std::cout << a << "\n";
	}

	return 0;
}