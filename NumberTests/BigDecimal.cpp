
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
	m_Digits = std::vector<DIGIT_TYPE>(number.length()-startIdx);
	for (int i = 0; i < (number.length() - startIdx); i++)
		m_Digits[number.length() - startIdx - 1 - i] = (DIGIT_TYPE)(number[i+startIdx]-48);
	StripLeadingZeros();
}

BigDecimal::BigDecimal(const BigDecimal& other)
{
	m_Digits = std::vector<DIGIT_TYPE>(other.Digits());
	for (int i = 0; i < Digits(); i++)
		m_Digits[i] = other.m_Digits[i];
}

int BigDecimal::Digits() const
{
	return m_Digits.size();
}

DIGIT_TYPE BigDecimal::operator[](int i) const
{
//	if ((m_Digits.size() - 1 - i) >= m_Digits.size())
//		return 0;
//	return m_Digits[m_Digits.size() - 1 - i];
	if (m_Digits.size() <= i) { return 0; }
	return m_Digits[i];
}

BigDecimal& BigDecimal::operator+=(const BigDecimal& n)
{
	int maxDigits = std::max<int>(Digits(), n.Digits());
	while (Digits() < maxDigits) { m_Digits.push_back(0); }
	for (int i = 0; i < Digits(); i++)
		m_Digits[i] += n[i];

	Normalize();
	return *this;
}

BigDecimal& BigDecimal::operator-=(const BigDecimal& n)
{
	int maxDigits = std::max<int>(Digits(), n.Digits());
	while (Digits() < maxDigits) { m_Digits.push_back(0); }
	for (int i = 0; i < Digits(); i++)
		m_Digits[i] -= n[i];

	Normalize();
	StripLeadingZeros();
	return *this;
}

BigDecimal& BigDecimal::operator*=(const BigDecimal& n)
{
	// TODO: insert return statement here - this will be complicated,
	// for the simpler solution i need a BigDecimal * DIGIT_TYPE = BigDecimal type of function
	// the more advanced solution is the Karatsuba algorithm

	BigDecimal resultSum;

	for (int i = 0; i < n.Digits(); i++)
	{
		BigDecimal tmp = (*this * n[i]);
		tmp.ShiftDigits(i);
		resultSum += tmp; // here we have a problem with the += operator
	}

	m_Digits = resultSum.m_Digits;
	return *this;
}

BigDecimal& BigDecimal::operator/=(const BigDecimal& n)
{
	// TODO: insert return statement here - this is also complicated,
	// I need to repeatedly subtract n, until the remainder is smaller than n
	/*
def Divide(A, B):
	if A<B:
		return [0, A]
	
	result = 0
	remainder = A
	subtractor = B
	incrementor = 1 # subtractor/B
	
	while B <= remainder:
		if subtractor < remainder:
			remainder -= subtractor
			result += incrementor
	
		if remainder < subtractor and B < subtractor:
			subtractor /= 2
			incrementor /= 2
		else
			subtractor *= 2
			incrementor *= 2
	
	return [result, remainder]
	*/

	if (*this < n)
	{
		m_Digits = std::vector<DIGIT_TYPE>(1);
		return *this;
	}





	return *this;
}

void BigDecimal::operator++()
{
	m_Digits[0]++;
	Normalize();
}

bool BigDecimal::operator==(const BigDecimal& other) const
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

bool BigDecimal::operator<(const BigDecimal& other) const
{
	if (Digits() < other.Digits())
		return true;
	else if (Digits() > other.Digits())
		return false;

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

bool BigDecimal::operator>(const BigDecimal& other) const
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

bool BigDecimal::operator<=(const BigDecimal& other) const
{
	if ((*this) < other)
		return true;
	if ((*this) == other)
		return true;

	return false;
}

bool BigDecimal::operator>=(const BigDecimal& other) const
{
	if ((*this) > other)
		return true;
	if ((*this) == other)
		return true;

	return false;
}


BigDecimal BigDecimal::operator*(const DIGIT_TYPE c)
{
	BigDecimal result(*this);
	for (int i = 0; i < Digits(); i++)
		result.m_Digits[i] *= c;

	result.Normalize();
	return result;
}

void BigDecimal::ShiftDigits(int i)
{
	for (int k = 0; k < i; k++)
		m_Digits.push_back(0);
	std::rotate(m_Digits.rbegin(), m_Digits.rbegin() + i, m_Digits.rend());
}

void BigDecimal::Double()
{
	for (int i = 0; i < m_Digits.size(); i++) { m_Digits[i] *= 2; }
	Normalize();
}

void BigDecimal::Halve()
{
	DIGIT_TYPE leastSignificantDigitHalf = m_Digits[0]/2;
	for (int i = 0; i < (m_Digits.size() - 1); i++) { m_Digits[i] = m_Digits[i + 1] * 5; } // shift and multiply elements

	m_Digits.pop_back();
	if (m_Digits.size() == 0)
		m_Digits.push_back(leastSignificantDigitHalf);
	else
		m_Digits[0] += leastSignificantDigitHalf;

	Normalize();
}

void BigDecimal::Square()
{
	BigDecimal clone(*this);
	*this *= clone;
}

void BigDecimal::SquareRoot()
{
	// do this iteratively:
	// x_n+1 = 0.5*(x_n+A/x_n)

}

void BigDecimal::Normalize()
{
	// in case of most digits, just subtract ten from the digits until we get to the 0-9 interval
	// and each time add one to the next digit
	for (int i = 0; i < m_Digits.size()-1; i++)
	{
		while (m_Digits[i] > 9) { m_Digits[i + 1]++; m_Digits[i] -= 10; }
		while (m_Digits[i] < 0) { m_Digits[i + 1]--; m_Digits[i] += 10; }
	}
	// when the last digit is more than 10, create one more digit and put the carry-over term into it
	if (m_Digits[m_Digits.size()-1] > 9)
	{
		m_Digits[m_Digits.size() - 1] -= 10;
		m_Digits.push_back(1);
		Normalize();
	}
	// when the digit at the largest decimal is negative after normalizing everything before,
	// than the whole number is negative, that I dont want to allow, so I floor the result at 0
	else if (m_Digits[m_Digits.size() - 1] < 0)
	{
		// // im not sure yet what to do here
		// m_Digits[m_Digits.size() - 1] -= 10;
		// m_Digits.push_back(1);
		// Normalize();
		m_Digits = std::vector<DIGIT_TYPE>(1);
	}
	StripLeadingZeros();
}

void BigDecimal::StripLeadingZeros()
{
	while (m_Digits[m_Digits.size() - 1] == 0 && m_Digits.size() > 1) { m_Digits.pop_back(); }
}



//-----------------------------------------//
//----- Related, non-member functions -----//
//-----------------------------------------//


std::ostream& operator<<(std::ostream& stream, const BigDecimal& n)
{
	for (int i = 0; i < n.Digits(); i++)
		stream << (int)n[n.Digits()-1-i];

	return stream;
}

BigDecimal operator+(const BigDecimal& n1, const BigDecimal& n2)
{
	BigDecimal result = BigDecimal(n1);
	result += n2;
	return result;
}

BigDecimal operator-(const BigDecimal& n1, const BigDecimal& n2)
{
	BigDecimal result = BigDecimal(n1);
	result -= n2;
	return result;
}

BigDecimal operator*(const BigDecimal& n1, const BigDecimal& n2)
{
	BigDecimal result = BigDecimal(n1);
	result *= n2;
	return result;
}

BigDecimal operator/(const BigDecimal& n1, const BigDecimal& n2)
{
	/*
def Divide(A, B):
	if A<B:
		return [0, A]

	result = 0
	remainder = A
	subtractor = B
	incrementor = 1 # subtractor/B

	while B <= remainder:
		if subtractor < remainder:
			remainder -= subtractor
			result += incrementor

		if remainder < subtractor and B < subtractor:
			subtractor /= 2
			incrementor /= 2
		else
			subtractor *= 2
			incrementor *= 2

	return [result, remainder]
	*/
	if (n1 < n2) { return BigDecimal(); }
	BigDecimal result;
	BigDecimal remainder(n1);
	BigDecimal subtractor(n2);
	BigDecimal incrementor("1"); // incrementor is always = subtractor / n2

	while (n2 <= remainder)
	{
		if (subtractor <= remainder)
		{
			remainder -= subtractor;
			result += incrementor;
		}

		if (remainder < subtractor && n2 < subtractor)
		{
			subtractor.Halve();
			incrementor.Halve();
		}
		else
		{
			subtractor *= BigDecimal("2");
			incrementor *= BigDecimal("2");
		}
	}

	return result;
}



