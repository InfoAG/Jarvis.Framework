#ifndef INTEGER_H
#define INTEGER_H

#include <string>
#include "Number.h"
#include "Natural.h"

namespace CAS{
	class Natural;

	class Integer : public Number{
	private:
		Natural nat;
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
		Integer(Natural &&other) : nat(std::move(other)),sign(false){} 
		Integer(Integer &&other) : nat(std::move(other.nat)),sign(other.sign) {}
        Integer(const Integer &other) : nat(other.nat), sign(other.sign) {}


		//Getter Functions;
		Natural getNat()const;
		fbyte getNumberAt(unsigned int) const;
		fbyte getSize() const;
		bool getSign() const;
        std::string toString()const;

		//Properties
		bool isInteger();
		bool isEven();
		bool isOdd();
		bool isPrime();
		
		//Arbitrary Natural Operators
		const Integer operator+(const Natural&)const;
		const Integer operator-(const Natural&)const;
		const Integer operator*(const Natural&)const;
		const Integer operator/(const Natural&)const;
		const Integer operator%(const Natural&)const;
		Integer &operator=(const Natural&);
		Integer &operator+=(const Natural&);
		Integer &operator-=(const Natural&);
		Integer &operator*=(const Natural&);
		Integer &operator/=(const Natural&);

		//Arbitrary Integer Operators
		const Integer operator+(const Integer&)const;
		const Integer operator-(const Integer&)const;
		const Integer operator*(const Integer&)const;
		const Integer operator/(const Integer&)const;
		const Integer operator%(const Integer&)const;
		Integer &operator=(const Integer&);
		Integer &operator+=(const Integer&);
		Integer &operator-=(const Integer&);
		Integer &operator*=(const Integer&);
		Integer &operator/=(const Integer&);
        Integer &operator++() { *this += 1; return *this; }
        Integer &operator--() { *this -= 1; return *this; }
        Integer operator++(int) { Integer result(*this); *this += 1; return result; }
        Integer operator--(int) { Integer result(*this); *this -= 1; return result; }

		//Integer Operators
		const Integer operator+(const int&)const;
		const Integer operator-(const int&)const;
		const Integer operator*(const int&)const;
		const Integer operator/(const int&)const;
		const Integer operator%(const int&)const;
		Integer& operator=(const int&);
		Integer& operator+=(const int&);
		Integer& operator-=(const int&);
		Integer& operator*=(const int&);
		Integer& operator/=(const int&);

        bool operator<(const Integer&) const;
        bool operator<=(const Integer&) const;
        bool operator==(const Integer&) const;
        bool operator!=(const Integer &other) const { return ! (*this == other); }
        bool operator>=(const Integer&) const;
        bool operator>(const Integer&) const;
	};
};

#endif
