#ifndef INTEGER_H
#define INTEGER_H

#include <vector>
#include "Number.h"
#include "Utility.h"

namespace CAS{
	class Natural;

	class Integer : public Number{
	private:
		std::vector<fbyte> digits;
		fbyte size;
		bool sign;
	public:
		Integer();
		Integer(short);
		Integer(unsigned short);
		Integer(int);
		Integer(unsigned int);
		Integer(long);
		Integer(unsigned long);
		Integer(long long);
		Integer(unsigned long long);
		Integer(float);
		Integer(double);
        Integer(std::string);
		

		Integer(const Natural&);
		Integer(const Integer&);

		//Natural getNumber() const;
		fbyte getNumberAt(unsigned int) const;
		fbyte getSize() const;
		bool getSign() const;

        std::string toString();


		bool isInteger();
		bool isEven();
		bool isOdd();
		bool isPrime();

		Integer leftShift(unsigned int)const;
		Integer rightShift(unsigned int)const;
		Integer msb(unsigned int)const;
		Integer lsb(unsigned int)const;

		Integer addition(const Integer&,bool);
		Integer subtraction(const Integer&,bool);
		Integer multiplication(const Integer&,bool);
		Integer division(const Integer&,bool);
		Integer remainder(const Integer&,bool);

		Integer karatsuba(const Integer&);
		Integer toom33(const Integer&);
		Integer toom44(const Integer&);
		Integer FFT(const Integer&);

		Integer operator+(const Integer&);
		Integer operator-(const Integer&);
		Integer operator*(const Integer&);
		Integer operator/(const Integer&);
		Integer operator%(const Integer&);
        /*
		bool operator<(const Integer&);
		bool operator<=(const Integer&);
		bool operator==(const Integer&);
		bool operator>=(const Integer&);
		bool operator>(const Integer&);
        */
	};
};

#endif
