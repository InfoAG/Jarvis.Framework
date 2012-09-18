#ifndef NATURAL_H
#define NATURAL_H

#include <vector>
#include "Number.h"
#include "Utility.h"

namespace CAS{
	class Integer;

	class Natural : public Number{
	private:
        std::vector<fbyte> digits;
		fbyte size;
	public:
		//Constructors
		Natural();
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
        Natural(Natural &&other) : digits(std::move(other.digits)), size(other.size) {}
		//Natural(const Integer&);

		//Getter Functions
        std::vector<fbyte> getDigits()const;
		fbyte getDigitsAt(unsigned int)const;
		fbyte getSize()const;
        std::string toString()const;

		//Properties
		bool isInteger();
		bool isEven();
		bool isOdd();
		bool isPrime();

		//Shift Operations
        Natural LeftShift(unsigned int)const;
        Natural RightShift(unsigned int)const;
        Natural MSB(unsigned int)const;
        Natural LSB(unsigned int)const;

		//Schoolbool Algorithms
		Natural Addition(const Natural&)const;
		Natural simpleAddition(const Natural& rhs)const;
		Natural Subtraction(const Natural&)const;
		Natural simpleSubtraction(const Natural& rhs)const;
		Natural Multiplication(const Natural&)const;
		Natural simpleMultiplication(const Natural& rhs)const;
		Natural shortDivision(const Natural& rhs)const;
		Natural longDivision(const Natural& rhs)const;
		fbyte longDivisionSubRoutine(fbyte,fbyte,fbyte,fbyte,fbyte)const;
		Natural shortRemainder(const Natural&)const;
		Natural longRemainder(const Natural&)const; 
		Natural min(const Natural&)const;
		Natural max(const Natural&)const;


		//Improved Algorithms
		Natural fusedMultiplyAdd(const Natural&, const Natural&)const;
		Natural Karatsuba(const Natural&)const;
		Natural Toom33(const Natural&)const;
		Natural Toom44(const Natural&)const;
		Natural longDivisionDaC2by1(const Natural&)const;
		Natural longDivisionDaC3by2(const Natural&)const;

		//Arbitrary Natural Operators
        const Natural operator+(const Natural&)const;
        const Natural operator-(const Natural&)const;
        const Natural operator*(const Natural&)const;
        const Natural operator/(const Natural&)const;
        const Natural operator%(const Natural&)const;
        Natural &operator=(const Natural&);
        Natural &operator+=(const Natural&);
        Natural &operator-=(const Natural&);
        Natural &operator*=(const Natural&);
        Natural &operator/=(const Natural&);

		//Integer Operators
        const Natural operator+(const unsigned int&)const;
        const Natural operator-(const unsigned int&)const;
        const Natural operator*(const unsigned int&)const;
        const Natural operator/(const unsigned int&)const;
        const Natural operator%(const unsigned int&)const;
        Natural &operator=(const unsigned int&);
		Natural &operator+=(const unsigned int&);
		Natural &operator-=(const unsigned int&);
		Natural &operator*=(const unsigned int&);
		Natural &operator/=(const unsigned int&);
        Natural &operator++();
        Natural &operator--();
        Natural operator++(int);
        Natural operator--(int);


		//Bool Operators
		bool operator<(const Natural&)const;
		bool operator<=(const Natural&)const;
		bool operator==(const Natural&)const;
        bool operator!=(const Natural&)const;
		bool operator>=(const Natural&)const;
		bool operator>(const Natural&)const;
	};
};
extern CAS::Natural nfaculty(unsigned int);

#endif
