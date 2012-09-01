#ifndef NATURAL_H
#define NATURAL_H

#include <vector>
#include <limits>
#include "Number.h"
#include "Integer.h"
#include "Utility.h"

namespace CAS{
	class Integer;

	class Natural : public Number{
	private:
        std::vector<fbyte> digits;
		fbyte size;
	public:
		Natural();
		Natural(char);
		Natural(unsigned char);
		Natural(short);
		Natural(unsigned short);
		Natural(int);
		Natural(unsigned int);
		Natural(long);
		Natural(unsigned long);
		Natural(long long);
		Natural(unsigned long long);
		Natural(float);
		Natural(double);
        Natural(std::string);

		Natural(const Natural&);
		Natural(const Integer&);


        std::vector<fbyte> getDigits()const;
		fbyte getDigitsAt(unsigned int)const;
		fbyte getSize()const;
        std::string toString()const;


		void randomize(unsigned int, unsigned int);


		bool isInteger();
		bool isEven();
		bool isOdd();
		bool isPrime();

		Natural LeftShift(int)const;
		Natural RightShift(int)const;
		Natural MSB(unsigned int)const;
		Natural LSB(unsigned int)const;

		Natural Addition(const Natural&);
		Natural simpleAddition(const Natural& rhs);
		Natural Subtraction(const Natural&);
		Natural simpleSubtraction(const Natural& rhs);
		Natural Multiplication(const Natural&);
		Natural simpleMultiplication(const Natural& rhs)const;
		Natural shortDivision(const Natural& rhs);
		Natural longDivision(const Natural& rhs);
		fbyte longDivisionSubRoutine(fbyte,fbyte,fbyte,fbyte,fbyte);


		Natural fusedMultiplyAdd(const Natural&, const Natural&);

		Natural Karatsuba(const Natural&);
		Natural Toom33(const Natural&);
		Natural Toom44(const Natural&);

		Natural operator+(const Natural&);
		Natural operator+(const unsigned int&);
		Natural operator-(const Natural&);
		Natural operator-(const unsigned int&);
		Natural operator*(const Natural&);
		Natural operator*(const unsigned int&);
		Natural operator/(const Natural&);
		Natural operator/(const unsigned int&);
		Natural operator%(const Natural&);
		Natural operator%(const unsigned int&);
		Natural operator=(const Natural&);
		Natural operator=(const unsigned int&);
		
		bool operator<(const Natural&);
		bool operator<=(const Natural&);
		bool operator==(const Natural&) const;
		bool operator>=(const Natural&);
		bool operator>(const Natural&);
	};
};
extern CAS::Natural nfaculty(unsigned int);

#endif
