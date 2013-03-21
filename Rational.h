#ifndef RATIONAL_H
#define RATIONAL_H

#include <string>
#include "Number.h"
#include "Natural.h"
#include "Integer.h"

namespace CAS{
	class Rational
	{
	private:
		Natural numerator;
		Natural denominator;
		bool sign;
	public:
		Rational();
		Rational(short);
		Rational(unsigned short);
		Rational(int);
		Rational(unsigned int);
		Rational(long);
		Rational(unsigned long);
		Rational(long long);
		Rational(unsigned long long);
		Rational(int, int);
		Rational(float);
		Rational(double);
		Rational(std::string);

		Rational(Natural &&other) : numerator(std::move(other)),denominator(1),sign(false){}
		Rational(Integer &&other) : numerator(std::move(other.getNat())),denominator(1),sign(other.getSign()){}
		Rational(Rational &&other) : numerator(std::move(other.numerator)),denominator(std::move(other.denominator)),sign(std::move(other.sign)){}

		Rational(const Natural&);
		Rational(const Natural&,const Natural&);
		Rational(const Integer&);
		Rational(const Natural&,const Integer&);
		Rational(const Integer&,const Natural&);
		Rational(const Integer&,const Integer&);
		Rational(const Rational&);

		Natural getNumerator()const;
		Natural getDenominator()const;
		bool getSign()const;
		NUM_TYPE getType()const;
		std::string toString(int=10)const;
		std::string fracToString()const;
		std::string fracToString2()const;

		bool isInteger();
		bool isEven();
		bool isOdd();
		bool isPrime();

		static Rational round(const Rational&,ROUND_MODE=ROUND_TO_NEAREST);

		const Rational operator+(const Natural&)const;
		const Rational operator-(const Natural&)const;
		const Rational operator*(const Natural&)const;
		const Rational operator/(const Natural&)const;
		const Rational operator%(const Natural&)const;
		Rational& operator=(const Natural&);
		Rational& operator+=(const Natural&);
		Rational& operator-=(const Natural&);
		Rational& operator*=(const Natural&);
		Rational& operator/=(const Natural&);

		const Rational operator+(const Integer&)const;
		const Rational operator-(const Integer&)const;
		const Rational operator*(const Integer&)const;
		const Rational operator/(const Integer&)const;
		const Rational operator%(const Integer&)const;
		Rational& operator=(const Integer&);
		Rational& operator+=(const Integer&);
		Rational& operator-=(const Integer&);
		Rational& operator*=(const Integer&);
		Rational& operator/=(const Integer&);

		const Rational operator+(const Rational&)const;
		const Rational operator-(const Rational&)const;
		const Rational operator*(const Rational&)const;
		const Rational operator/(const Rational&)const;
		const Rational operator%(const Rational&)const;
		Rational& operator=(const Rational&);
		Rational& operator+=(const Rational&);
		Rational& operator-=(const Rational&);
		Rational& operator*=(const Rational&);
		Rational& operator/=(const Rational&);

		bool operator<(const int&)const;
		bool operator<=(const int&)const;
		bool operator==(const int&)const;
		bool operator!=(const int&)const;
		bool operator>=(const int&)const;
		bool operator>(const int&)const;

		bool operator<(const Natural&)const;
		bool operator<=(const Natural&)const;
		bool operator==(const Natural&)const;
		bool operator!=(const Natural&)const;
		bool operator>=(const Natural&)const;
		bool operator>(const Natural&)const;

		bool operator<(const Integer&)const;
		bool operator<=(const Integer&)const;
		bool operator==(const Integer&)const;
		bool operator!=(const Integer&)const;
		bool operator>=(const Integer&)const;
		bool operator>(const Integer&)const;

		bool operator<(const Rational&)const;
		bool operator<=(const Rational&)const;
		bool operator==(const Rational&)const;
		bool operator!=(const Rational&)const;
		bool operator>=(const Rational&)const;
		bool operator>(const Rational&)const;


	};
};

#endif //RATIONAL_H
