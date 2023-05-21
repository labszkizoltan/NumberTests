
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
	m_Digits = std::vector<DIGIT_TYPE>(number.length());
	for (int i = 0; i < number.length(); i++)
	{
		m_Digits[number.length() - 1 - i] = (int)number[i]-48;
	}
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
	{
		m_Digits[i] += n.m_Digits[i];
	}

	Normalize();
	return *this;
}

void BigDecimal::operator++()
//BigDecimal& BigDecimal::operator++()
{
	m_Digits[0]++;
	Normalize();
	// return *this;
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
		// if (m_Digits[Digits() - 1 - i] < other.m_Digits[Digits() - 1 - i])
		// return true;
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

void BigDecimal::Normalize()
{
	for (int i = 0; i < m_Digits.size()-1; i++)
	{
		while (m_Digits[i] > 9) { m_Digits[i+1]++; m_Digits[i] -= 10; }
	}
	if (m_Digits[m_Digits.size()-1] > 9)
	{
		m_Digits[m_Digits.size() - 1] -= 10;
		m_Digits.push_back(1);
		// // this seems to be working, but perhaps a bit overcomplicated, I dont think the remainder can be more than 10
		// m_Digits.push_back(m_Digits[m_Digits.size() - 1] / 10);
		// m_Digits[m_Digits.size() - 2] -= 10 * m_Digits[m_Digits.size() - 1];
		Normalize();
	}

}

void BigDecimal::StripLeadingZeros()
{
	while (m_Digits[m_Digits.size() - 1] == 0) { m_Digits.pop_back(); }
}

std::ostream& operator<<(std::ostream& stream, const BigDecimal& n)
{
	for (int i = 0; i < n.Digits(); i++)
	{
		stream << n[i];
		// stream << n[n.Digits()-1-i];
	}
	return stream;
}

// bool operator<(BigDecimal& n1, BigDecimal& n2)
// {
// 	return n1<n2;
// }



