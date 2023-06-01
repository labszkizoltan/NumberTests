
#include "BigDecimal.h"
#include <iostream>
#include <cstdlib>

BigDecimal::BigDecimal()
{
	m_Digits = std::vector<DIGIT_TYPE>(1);
	m_Digits[0] = 0;
}

BigDecimal::BigDecimal(const std::string& number)
{
	int startIdx = 0;
	// 45 is the ascii code for "-"
	if (number[0] == 45)
	{
		m_Sign = false;
		startIdx = 1;
	}
	m_Digits = std::vector<DIGIT_TYPE>(number.length()-startIdx);
	for (int i = 0; i < (number.length() - startIdx); i++)
		m_Digits[number.length() - startIdx - 1 - i] = (DIGIT_TYPE)(number[i+startIdx]-48);
	StripLeadingZeros();
}

int BigDecimal::Digits() const
{
	return m_Digits.size();
}

DIGIT_TYPE BigDecimal::operator[](int i) const
{
	return m_Digits[m_Digits.size() - 1 - i];
	// return m_Digits[i];
}

BigDecimal& BigDecimal::operator+=(const BigDecimal& n)
{
	int maxDigits = std::max<int>(m_Digits.size(), n.Digits());
	while (m_Digits.size() < maxDigits) { m_Digits.push_back(0); }

	int minDigits = std::min<int>(m_Digits.size(), n.Digits());
//	int iterCount = m_Digits.size() < n.Digits() ?
	for (int i = 0; i < minDigits; i++)
		m_Digits[i] += n.m_Digits[i];

	Normalize();
	return *this;
}

BigDecimal& BigDecimal::operator-=(const BigDecimal& n)
{
	// TODO: insert return statement here

	return *this;
}

BigDecimal& BigDecimal::operator*=(const BigDecimal& n)
{
	// TODO: insert return statement here

	return *this;
}

BigDecimal& BigDecimal::operator/=(const BigDecimal& n)
{
	// TODO: insert return statement here

	return *this;
}

void BigDecimal::operator++()
{
	m_Digits[0]++;
	Normalize();
}

bool BigDecimal::operator==(const BigDecimal& other)
{
	if(Digits() != other.Digits())
		return false;

	for (int i = 0; i < Digits(); i++)
	{
		if (m_Digits[i] != other.m_Digits[i])
			return false;
	}

	return true;
}

bool BigDecimal::operator<(const BigDecimal& other)
{
	if(Digits() < other.Digits())
		return true;

	for (int i = 0; i < Digits(); i++)
	{
		// compare the leading digits (if they are different they can decide which number is bigger, otherwise go to the next digit)
		int a = m_Digits[Digits() - 1 - i];
		int b = other.m_Digits[Digits() - 1 - i];
		if (a != b)
			return a < b;
	}

	return false;
}

bool BigDecimal::operator>(const BigDecimal& other)
{
	if (Digits() > other.Digits())
		return true;

	for (int i = 0; i < Digits(); i++)
	{
		int a = m_Digits[Digits() - 1 - i];
		int b = other.m_Digits[Digits() - 1 - i];
		if (a != b)
			return a > b;
	}

	return false;
}

/*
BigDecimal BigDecimal::AbsSum(BigDecimal& other)
{
	return BigDecimal();
}

BigDecimal BigDecimal::AbsDif(BigDecimal& other)
{
	return BigDecimal();
}
*/

void BigDecimal::Normalize()
{
	for (int i = 0; i < m_Digits.size()-1; i++)
	{
		while (m_Digits[i] > 9) { m_Digits[i + 1]++; m_Digits[i] -= 10; }
		while (m_Digits[i] < 0) { m_Digits[i + 1]--; m_Digits[i] += 10; }
	}
	if (m_Digits[m_Digits.size()-1] > 9)
	{
		m_Digits[m_Digits.size() - 1] -= 10;
		m_Digits.push_back(1);
		Normalize();
	}
	else if (m_Digits[m_Digits.size() - 1] < 0)
	{
		// // im not sure yet what to do here
		// m_Digits[m_Digits.size() - 1] -= 10;
		// m_Digits.push_back(1);
		// Normalize();
	}
	StripLeadingZeros();
}

void BigDecimal::StripLeadingZeros()
{
	while (m_Digits[m_Digits.size() - 1] == 0) { m_Digits.pop_back(); }
}

std::ostream& operator<<(std::ostream& stream, const BigDecimal& n)
{
	// if (!n.m_Sign)
	// 	stream << "-";
	for (int i = 0; i < n.Digits(); i++)
		stream << (int)n[i];

	return stream;
}



