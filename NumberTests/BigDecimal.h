
#ifndef BIG_DECIMAL_H
#define BIG_DECIMAL_H

#include <string>
#include <vector>

#include "Common.h"

class BigDecimal
{
public:
	BigDecimal();
	BigDecimal(const std::string& number);
	BigDecimal(const BigDecimal& other);
	~BigDecimal() = default;

	int Digits() const;
	DIGIT_TYPE operator[](int i) const;

	BigDecimal& operator+=(const BigDecimal& n);
	BigDecimal& operator-=(const BigDecimal& n);
	BigDecimal& operator*=(const BigDecimal& n);
	BigDecimal& operator/=(const BigDecimal& n);


	void operator++();
	bool operator==(const BigDecimal& other);
	bool operator<(const BigDecimal& other);
	bool operator>(const BigDecimal& other);

	// multiply with a scalar and return a new BigDecimal as result
	BigDecimal operator*(const DIGIT_TYPE c);


private:
	void ShiftDigits(int i);

	void Normalize();
	void StripLeadingZeros();


private:
	std::vector<DIGIT_TYPE> m_Digits;


friend std::ostream& operator<<(std::ostream& stream, const BigDecimal& n);

friend BigDecimal operator+(const BigDecimal& n1, const BigDecimal& n2);
friend BigDecimal operator-(const BigDecimal& n1, const BigDecimal& n2);
friend BigDecimal operator*(const BigDecimal& n1, const BigDecimal& n2);
friend BigDecimal operator/(const BigDecimal& n1, const BigDecimal& n2);


};

// related, non-member functions
std::ostream& operator<<(std::ostream& stream, const BigDecimal& n);

BigDecimal operator+(const BigDecimal& n1, const BigDecimal& n2);
BigDecimal operator-(const BigDecimal& n1, const BigDecimal& n2);
BigDecimal operator*(const BigDecimal& n1, const BigDecimal& n2);
BigDecimal operator/(const BigDecimal& n1, const BigDecimal& n2);


#endif // BIG_DECIMAL_H
