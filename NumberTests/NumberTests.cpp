
#include <iostream>
#include "BigDecimal.h"

int main()
{
	std::string bigDecString = "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	// BigDecimal bd1("00123");
	// BigDecimal bd2("9876543210");
	// BigDecimal bd1("1912");
	// BigDecimal bd2("89234");
	BigDecimal bd1("1000");
	BigDecimal bd2("10000000000000000000000000000000000000000000000000000000000000000000");

	// auto digit1 = bd2[1];
	// 
	std::cout << "bd1: " << bd1 << "\n";
	std::cout << "bd2: " << bd2 << "\n";
	// 
	// bd2 += bd1;
	// std::cout << "bd2 += bd1: " << bd2 << "\n";

	// bd1 += bd2;
	// std::cout << "bd1 += bd2: " << bd1 << "\n";

	// std::cout << "true: " << true << "\n";
	// std::cout << "false: " << false << "\n";
	std::cout << "(bd1 < bd2): " << (bd1 < bd2) << "\n";
	std::cout << "(bd2 < bd1): " << (bd2 < bd1) << "\n";
	std::cout << "(bd2 == bd1): " << (bd2 == bd1) << "\n";
	std::cout << "(123 < 123): " << (BigDecimal("123") < BigDecimal("123")) << "\n";
	std::cout << "(123 > 123): " << (BigDecimal("123") > BigDecimal("123")) << "\n";
	std::cout << "(123 <= 123): " << (BigDecimal("123") <= BigDecimal("123")) << "\n";
	std::cout << "(123 >= 123): " << (BigDecimal("123") >= BigDecimal("123")) << "\n";
	std::cout << "(123 == 123): " << (BigDecimal("123") == BigDecimal("123")) << "\n";

	BigDecimal asd_64("64");
	asd_64.Halve();
	std::cout << "(asd_64.Halved()): " << asd_64 << "\n";

	BigDecimal asd_65("65");
	asd_65.Halve();
	std::cout << "(asd_65.Halved()): " << asd_65 << "\n";

	std::cout << "bd1 * 2: " << (bd1 * 2) << "\n";
	std::cout << "bd2 * 3: " << (bd2 * 3) << "\n";

	std::cout << "(bd1 - bd2): " << (bd1 - bd2) << "\n";
	std::cout << "(bd2 - bd1): " << (bd2 - bd1) << "\n";
	std::cout << "(bd1 - bd1): " << (bd1 - bd1) << "\n";

	std::cout << "(bd1 * bd2): " << (bd1 * bd2) << "\n";
	std::cout << "(bd2 / bd1): " << (bd2 / bd1) << "\n";

	BigDecimal asd_123("123");
	asd_123.Square();
	std::cout << "asd_123.Square(): " << asd_123 << "\n";

	// for (BigDecimal i = BigDecimal(); i < BigDecimal("123"); i.operator++())
	// {
	// 	std::cout << i << "\n";
	// }


	return 0;
}
