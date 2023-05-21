
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
	~BigDecimal() = default;

	int Digits() const;
	DIGIT_TYPE operator[](int i) const;

	BigDecimal& operator+=(const BigDecimal& n);

	void operator++();
	bool operator==(const BigDecimal& other);
	bool operator<(const BigDecimal& other);
	bool operator>(const BigDecimal& other);

private:
	void Normalize();
	void StripLeadingZeros();


private:
	std::vector<DIGIT_TYPE> m_Digits;


};

// related, non-member functions
std::ostream& operator<<(std::ostream& stream, const BigDecimal& n);



#endif // BIG_DECIMAL_H
